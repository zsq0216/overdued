#include <iostream>
#include <stack>
#include <string>

using namespace std;

int priority(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 1;
        break;
    case '*':
    case '/':
    case 'm':
        return 2;
        break;
    case '(':
        return 0;
        break;
    default:
        return 0;
        break;
    }
}
string converExpression(string input)
{
    string output;
    stack<char> ops;
    for (int i = 0; i < input.length(); ++i)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            output += input[i];
        }
        else if (input[i] == '(')
        {
            ops.push(input[i]);
        }
        else if (input[i] == ')')
        {
            while (ops.top() != '(')
            {
                output += ops.top();
                ops.pop();
            }
            if (ops.top() == '(')
                ops.pop();
        }
        else
        {
            while (!ops.empty() && priority(input[i]) <= priority(ops.top())) // judge empty first
            {
                output += ops.top();
                ops.pop();
            }
            ops.push(input[i]);
        }
    }
    while (!ops.empty())
    {
        output += ops.top();
        ops.pop();
    }
    return output;
}
int main()
{
    string str;
    cin >> str;
    cout << converExpression(str);
    return 0;
}