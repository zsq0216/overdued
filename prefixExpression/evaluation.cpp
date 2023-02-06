#include <iostream>
#include <stack>
#include<string>

using namespace std;

int calculate(string pfix)
{
    stack<int> stk;
    int res;
    for (int i = 0; i < pfix.length(); ++i)
    {
        if (pfix[i] >= '0' && pfix[i] <= '9')
            stk.push(pfix[i] - '0');
        else
        {
            int m, n;
            m = stk.top();
            stk.pop();
            n = stk.top();
            stk.pop();
            if (pfix[i] == '+')
                stk.push(m + n);
            else if (pfix[i] == '-')
                stk.push(n - m);
            else if (pfix[i] == '*')
                stk.push(m * n);
            else if (pfix[i] == '/')
                stk.push(n / m);
            else if (pfix[i] == 'm')
                stk.push(n % m);
        }
    }
    res=stk.top();
    return res;
}
int main()
{
    string str;
    cin>>str;
    cout<<calculate(str);
    return 0;
}

