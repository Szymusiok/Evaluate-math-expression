# Evaluate-math-expression

The function is used to calculate mathematical expressions with consideration of the order of operations.
```
bool EvaluateMathExpression(std::string expression, double& result);
```
```
expression               - mathematical expression 
result                   - variable in which the result will be stored 
Function return: true    - if the expression is correct 
                 false   - if the expression is incorrect (wrong character, etc.)
```
If function returns false, variable `result` stays unchanged.
