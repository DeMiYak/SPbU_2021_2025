#include"RPN.h"

using namespace std;

bool Formula::delimiter(char c){
    return c == ' ';
}

bool Formula::isOperator(char c){

    return  c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '~';
}

int Formula::priority(char operatorValue)
{
    return
        operatorValue == '+' || operatorValue == '-' ? 1:
        operatorValue == '*' || operatorValue == '/' ? 2:
        operatorValue == '^' ? 3:
        operatorValue == '~' ? 4:
        -1;
}

void Formula::ProcessOperator(stack<double> &valueStack, char operatorValue)
{
    double rightOperand = valueStack.top(); valueStack.pop();

    if(operatorValue == '~')
        valueStack.push(-rightOperand);

    else{
        double leftOperand = valueStack.top(); valueStack.pop();
        switch(operatorValue){
            case '+': valueStack.push(leftOperand + rightOperand); break;
            case '-': valueStack.push(leftOperand - rightOperand); break;
            case '*': valueStack.push(leftOperand * rightOperand); break;
            case '/': valueStack.push(leftOperand / rightOperand); break;
            case '^': valueStack.push(pow(leftOperand, rightOperand)); break;
        }
    }
}

string Formula::ReplaceVariableWithDouble(double x){
    string convertedVariable = to_string(x);
    string formulaCopy = _formula;
    for(size_t i = 0; i < formulaCopy.length(); i++){
        if(formulaCopy[i] == 'x') {
            formulaCopy.insert(i, convertedVariable);
            if(formulaCopy[i] == '-') formulaCopy[i] = '~';
            i += convertedVariable.length();
            formulaCopy.erase(i,1);
        }
    }
    return formulaCopy;
}

double Formula::CalculateFromString(const string &_string){
    stack<double> valueStack;
    stack<char> operatorStack;
    for(size_t i = 0; i < _string.length(); i++){

        if(!delimiter(_string[i])){

            if(_string[i]=='(') {
                operatorStack.push('(');
            }
            else if (_string[i] == ')') {

                while(operatorStack.top()!='(')
                    ProcessOperator(valueStack, operatorStack.top()),
                    operatorStack.pop();

                operatorStack.pop();
            }

            else if(isOperator(_string[i])){
                char currentOperator = _string[i];

                while(!operatorStack.empty() && priority(operatorStack.top()) >= priority(_string[i]))
                    ProcessOperator(valueStack, operatorStack.top()), operatorStack.pop();

                operatorStack.push(currentOperator);
            }

            else{
                string operandString;

                while(i < _string.length() && isalnum(_string[i]))
                    operandString += _string[i++];

                if(_string[i] == '.') operandString += _string[i++];

                while(i < _string.length() && isalnum(_string[i])) {
                    operandString += _string[i++];
                }

                i--;

                valueStack.push(atof(operandString.c_str()));
            }
        }
    }
    while(!operatorStack.empty())
        ProcessOperator(valueStack, operatorStack.top()), operatorStack.pop();
    return valueStack.top();
}

double Formula::Evaluate(double x){
    string stringModified = ReplaceVariableWithDouble(x);

    return CalculateFromString(stringModified);
}
