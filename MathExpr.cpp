#include <iostream>
#include <string>
#include <stack>

bool EvaluateMathExpression(std::string expression, double& result)
{
   auto applyOperator = [] (std::stack<double>& operandStack, std::stack<char>& operatorStack)
   {
      if (operandStack.size() < 2 || operatorStack.empty())
      {
         return false;
      }

      double operand2 = operandStack.top();
      operandStack.pop();
      double operand1 = operandStack.top();
      operandStack.pop();
      char op = operatorStack.top();
      operatorStack.pop();

      if ('+' == op)
      {
         operandStack.push(operand1 + operand2);
      }
      else if ('-' == op)
      {
         operandStack.push(operand1 - operand2);
      }
      else if ('*' == op)
      {
         operandStack.push(operand1 * operand2);
      }
      else if ('/' == op)
      {
         if (0 == operand2)
         {
            return false; // Division by zero
         }
         operandStack.push(operand1 / operand2);
      }
      return true;
   };

   auto isOperator = [] (char c)
   {
      return ('+' == c || '-' == c || '*' == c || '/' == c);
   };

   auto getPrecedence = [] (char op)
   {
      if ('*' == op || '/' == op)
      {
         return 2;
      }
      else if ('+' == op || '-' == op)
      {
         return 1;
      }
      return 0;
   };

   expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());

   std::stack<double> operandStack;
   std::stack<char> operatorStack;

   bool isPositive = true;

   for (size_t i = 0; i < expression.length(); i++)
   {
      if (isdigit(expression[i]) || ('+' == expression[i] && 0 == i) || ('-' == expression[i] && 0 == i))
      {
         std::string operandStr;
         if ('+' == expression[i] || '-' == expression[i])
         {
            if (1 == expression.size() || !isdigit(expression[i + 1]))
            {
               return false;
            }
            if ('-' == expression[i])
            {
               isPositive = !isPositive;
            }
            i++;
         }
         operandStr += expression[i];
         while (i + 1 < expression.length() && (isdigit(expression[i + 1]) || '.' == expression[i + 1]))
         {
            operandStr += expression[i + 1];
            i++;
         }
         double operand = std::stod(operandStr);
         if (!isPositive)
         {
            operand = -operand;
            isPositive = true;
         }
         operandStack.push(operand);
      }
      else if ('(' == expression[i])
      {
         operatorStack.push(expression[i]);
      }
      else if (')' == expression[i])
      {
         while (!operatorStack.empty() && '(' != operatorStack.top())
         {
            if (!applyOperator(operandStack, operatorStack))
            {
               return false;
            }
         }
         if (!operatorStack.empty() && '(' == operatorStack.top())
         {
            operatorStack.pop();
         }
         else
         {
            return false; // Mismatched parentheses
         }
      }
      else if (isOperator(expression[i]))
      {
         while (!operatorStack.empty() && getPrecedence(expression[i]) <= getPrecedence(operatorStack.top()))
         {
            if (!applyOperator(operandStack, operatorStack))
            {
               return false;
            }
         }
         operatorStack.push(expression[i]);
      }
      else
      {
         return false; // Invalid character in the expression
      }
   }

   while (!operatorStack.empty())
   {
      if ('(' == operatorStack.top() || ')' == operatorStack.top())
      {
         return false; // Mismatched parentheses
      }
      if (!applyOperator(operandStack, operatorStack))
      {
         return false;
      }
   }

   if (operandStack.size() == 1 && operatorStack.empty())
   {
      result = operandStack.top();
      return true;
   }
   else
   {
      return false; // Malformed expression
   }
}