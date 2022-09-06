#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//class BigNum was designed to solve the problem of large number calculation
class BigNum
{
	//use string to store numbers
	string str;
	//class Operate was designed to perform a specified operation with BigNum on the input file
	friend class Operate;
public:
	//no parameter, but it would not happen in current test
	BigNum();
	//use string to store numbers
	BigNum(string Str);
	//override four operators
	friend istream &operator>>(istream &input, BigNum &c);
	friend ostream &operator<<(std::ostream &output, BigNum &c);
	BigNum operator+(const BigNum &c);
	BigNum operator-(const BigNum &c);
};

//class Operate was designed to perform a specified operation with BigNum on the input file
class Operate
{
public:
	//perform four kinds of specified operation
	void in_stream(ofstream &output);
	void out_stream(string &s, ofstream &output);
	void add_bn(string &a, string &b, ofstream &output);
	void substract_bn(string &a, string &b, ofstream &output);
};

int main()
{
	ifstream input("test_in.txt", ios::in);
	ofstream output("test_out.txt", ios::out);

	int n;						//the number of lines of the expression
	Operate ope;				//instantiate an object of class Operate
	string s;
	input >> n;
	while (n--)
	{
		input >> s;
		if (s == ">>")			//perform ">>" operation
			ope.in_stream(output);
		else if (s == "<<")		//perform "<<" operation
		{
			input >> s;
			ope.out_stream(s, output);
		}
		else					//"s" could be nothing but a large number
		{
			string a = s;
			string b;
			char act;
			input >> act;		//"act" could be nothing but "+" or "-"
			input >> b;
			if (act == '+')		//perform "+" or "-" operation
				ope.add_bn(a, b, output);
			else
				ope.substract_bn(a, b, output);
		}
	}
	return 0;
}

//no parameter, but it would not happen in current test
BigNum::BigNum()
{
	str = "0";
}

//use string to store numbers
BigNum::BigNum(string Str)
{
	str = Str;
}

//override ">>" operator
istream &operator>>(istream &input, BigNum &c)
{
	input >> c.str;
	return input;
}

//override "<<" operator
ostream &operator<<(std::ostream &output, BigNum &c)
{
	output << c.str;
	return output;
}

//override "+" operator
BigNum BigNum::operator+(const BigNum &c)
{
	BigNum B;
	string b = c.str;
	string a = this->str;

	//add '0' in front of the shorter one to make a and b equal in size
	while (a.size() > b.size())
	{
		b = '0' + b;				
	}
	while (a.size() < b.size())
	{
		a = '0' + a;
	}
	//addition may enlarge the size of the string
	a = '0' + a;
	b = '0' + b;

	//the idea is the same as addition vertical calculation
	for (int i = a.size() - 1; i >= 0; i--)
	{
		a[i] = a[i] + b[i] - '0';
		if (a[i] > '9')	
		{
			a[i] -= 10;
			a[i - 1] += 1;
		}
	}

	//if the size of string keep the same, delete the extra digits
	if (a[0] == '0')
		a = a.replace(0, 1, "");
	B.str = a;
	return B;
}

//override "-" operator
BigNum BigNum::operator-(const BigNum &c)
{
	BigNum B;
	string b = c.str;
	string a = this->str;
	bool flag = true;		//the outcome is positive
	if (b.size() > a.size() || b.size() == a.size() && b > a)
	{
		a.swap(b);
		flag = false;		//the outcome is negative
	}
	//add '0' in front of the shorter one to make a and b equal in size
	while (a.size() > b.size())
	{
		b = '0' + b;
	}

	//the idea is the same as substraction vertical calculation
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

	//delete the extra digits
	while (a[0] == '0')
	{
		a = a.replace(0, 1, "");
	}
	if (!flag)
		a = '-' + a;
	B.str = a;
	return B;
}

//read the string from cmd, and perform ">>" operation
void Operate::in_stream(ofstream &output)
{
	string Str;
	cin >> Str;
	if (Str.size() > 100)					//oversized
	{
		output << "out of range" << endl;
		return;
	}
	BigNum *bignum = new BigNum(Str);		//new and initialize an BigNum object
	output << *bignum << endl;				//the "<<" here has been overrided
	delete bignum;
}

//read the string from input file, and perform "<<" operation
void Operate::out_stream(string &s, ofstream &output)
{
	if (s.size() > 100)						//oversized
	{
		output << "out of range" << endl;
		return;
	}
	BigNum *bignum = new BigNum(s);			//new and initialize an BigNum object
	output << *bignum << endl;				//the "<<" here has been overrided
	delete bignum;
}

//read the string from input file, and perform "+" operation
void Operate::add_bn(string &a, string &b, ofstream &output)
{
	if (a.size() > 100 || b.size() > 100)	//oversized
	{
		output << "out of range" << endl;
		return;
	}
	BigNum *bignum1 = new BigNum(a);		//new and initialize an BigNum object with string a
	BigNum *bignum2 = new BigNum(b);		//new and initialize an BigNum object with string b
	BigNum *bignum3 = new BigNum();			
	*bignum3 = *bignum1 + *bignum2;			//the "+" here has been overrided
	if (bignum3->str.size() > 100)			//oversized
	{
		output << "out of range" << endl;
		return;
	}
	output << *bignum3 << endl;				//the "<<" here has been overrided
	delete bignum1;
	delete bignum2;
	delete bignum3;
}

//read the string from input file, and perform "-" operation
void Operate::substract_bn(string &a, string &b, ofstream &output)
{
	if (a.size() > 100 || b.size() > 100)	//oversized
	{
		output << "out of range" << endl;
		return;
	}
	BigNum *bignum1 = new BigNum(a);		//new and initialize an BigNum object with string a
	BigNum *bignum2 = new BigNum(b);		//new and initialize an BigNum object with string b
	BigNum *bignum3 = new BigNum();
	*bignum3 = *bignum1 - *bignum2;			//the "-" here has been overrided
	output << *bignum3 << endl;				//the "<<" here has been overrided
	delete bignum1;
	delete bignum2;
	delete bignum3;
}