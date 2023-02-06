#include <iostream>
#include <stack>
#include <string>
#include <cmath> 

using namespace std;

bool isUnit(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    else
        return false;
}

string divide(int num)
{
    string res;
    if(num/9<=9)
    {
        res+='(';
        res+=9+'0';
        res+='*';
        res+=num/9+'0';
        res+='+';
        res+=num%9+'0';
        res+=')';
    }
    else
    {
        res+='(';
        res+=9+'0';
        res+='*';
        res+=divide(num/9);
        res+='+';
        res+=num%9+'0';
        res+=')';
    }
    return res;
}
string transform(string input)
{
    string output;
    for (int i = 0; i < input.length(); ++i)
    {
        if (isUnit(input[i])&& isUnit(input[i+1]))
        {
            int num=0;
            int k=i+1;
            while(isUnit(input[++k]));
            int j=k-1;
            float n=0;
            for(j,n;j>=i;--j,++n)
            {
                num+=(input[j]-'0')*pow(10,n);
            }
            output+=divide(num);
            i=k-1;
        }
        else output+=input[i];
    }
    return output;
}

int main()
{
    cout<<transform("3+5*12*(14-8)");
    return 0;
}