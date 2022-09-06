#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class BigNum
{
	string str;
	friend class Operate;
public:
	BigNum()
	{
		str = "0";
	}
	BigNum(string Str)
	{
		str = Str;
	}
	friend istream &operator>>(istream &input, BigNum &c)
	{
		input >> c.str;
		return input;
	}
	friend ostream &operator<<(std::ostream &output, BigNum &c)
	{
		output << c.str;
		return output;
	}
	BigNum operator+(const BigNum &c)
	{
		BigNum B;
		string b = c.str;
		string a = this->str;
		while (a.size() > b.size())
		{
			b = '0' + b;
		}
		while (a.size() < b.size())
		{
			a = '0' + a;
		}
		a = '0' + a;
		b = '0' + b;
		for (int i = a.size() - 1; i >= 0; i--)
		{
			a[i] = a[i] + b[i] - '0';
			if (a[i] > '9')
			{
				a[i] -= 10;
				a[i - 1] += 1;
			}
		}
		if (a[0] == '0')
			a = a.replace(0, 1, "");
		B.str = a;
		return B;
	}
	BigNum operator-(const BigNum &c)
	{
		BigNum B;
		string b = c.str;
		string a = this->str;
		bool flag = true;
		if (b.size() > a.size()||b.size() == a.size() && b>a)
		{
			a.swap(b);
			flag = false;
		}
		while (a.size() > b.size())
		{
			b = '0' + b;
		}
		for (int i = a.size() - 1; i >= 0; i--)
		{
			a[i] = a[i] - b[i] + '0';
			if (a[i] < '0')
			{
				a[i] += 10;
				a[i - 1] -= 1;
			}
		}
		int i = 0;
		while (a[0] == '0')
		{
			a = a.replace(0, 1, "");
		}
		if (!flag)
			a = '-' + a;
		B.str = a;
		return B;
	}
};
class Operate
{
public:
	void in_stream(ofstream &output)
	{
		string Str;
		cin >> Str;
		if(Str.size()>100)
		{
			output << "out of range" << endl;
			return;
		}
		BigNum *bignum = new BigNum(Str);
		output << *bignum << endl;
		delete bignum;
	}
	void out_stream(string &s, ofstream &output)
	{
		if(s.size()>100)
		{
			output << "out of range" << endl;
			return;
		}
		BigNum *bignum = new BigNum(s);
		output << *bignum << endl;
		delete bignum;
	}
	void add_bn(string &a, string &b, ofstream &output)
	{
		if(a.size()>100||b.size()>100)
		{
			output << "out of range" << endl;
			return;
		}
		BigNum *bignum1 = new BigNum(a);
		BigNum *bignum2 = new BigNum(b);
		BigNum *bignum3 = new BigNum();
		*bignum3 = *bignum1 + *bignum2;
		if(bignum3->str.size()>100)
		{
			output << "out of range" << endl;
			return;
		}
		output << *bignum3 << endl;
		delete bignum1;
		delete bignum2;
		delete bignum3;
	}
	void substract_bn(string &a, string &b, ofstream &output)
	{
		if(a.size()>100||b.size()>100)
		{
			output << "out of range" << endl;
			return;
		}
		BigNum *bignum1 = new BigNum(a);
		BigNum *bignum2 = new BigNum(b);
		BigNum *bignum3 = new BigNum();
		*bignum3 = *bignum1 - *bignum2;
		output << *bignum3 << endl;
		delete bignum1;
		delete bignum2;
		delete bignum3;
	}
};
int main()
{
	ifstream input("test_in.txt", ios::in);
	ofstream output("test_out.txt", ios::out);

	int n;
	Operate ope;
	string s;
	input >> n;
	while (n--)
	{
		input >> s;
		if (s == ">>")
			ope.in_stream(output);
		else if (s == "<<")
		{
			input >> s;
			ope.out_stream(s, output);
		}
		else
		{
			string a = s;
			string b;
			char act;
			input >> act;
			input >> b;
			if (act == '+')
				ope.add_bn(a, b, output);
			else
				ope.substract_bn(a, b, output);
		}
	}
	return 0;
}
