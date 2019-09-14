#include "mString.h"

int mString::num_strings = 0;

mString::mString()
{
	len = 0;
	str = new char[1];
	str[0] = '\0';
	num_strings++;
}

mString::mString(const char * s)
{
	len = strnlen_s(s, 79);
	str = new char[len + 1];
	strcpy(str, s);
	if (len == 79) str[79] = '\0';
	num_strings++;
}

mString::mString(const mString & ms)
{
	len = ms.len;
	str = new char[len + 1];
	strcpy(str, ms.str);
	if (len == 79) str[79] = '\0';
	num_strings++;
}


mString::~mString()
{
	--num_strings;
	delete[] str;
}

mString & mString::operator=(const mString & ms)
{
	// TODO: 在此处插入 return 语句
	if (this == &ms)
	{
		return *this;
	}
	else
	{
		delete[] str;
		len = ms.len;
		str = new char[len + 1];
		strcpy(str, ms.str);
		if (len == 79) str[79] = '\0';
	}
	return *this;
}

mString & mString::operator=(const char * s)
{
	// TODO: 在此处插入 return 语句
	delete[] str;
	len = strnlen_s(s, 79);
	str = new char[len + 1];
	strcpy(str, s);
	if (len == 79) str[79] = '\0';
	return *this;
}

char & mString::operator[](size_t i)
{
	// TODO: 在此处插入 return 语句
	return str[i];
}

const char & mString::operator[](size_t i) const
{
	// TODO: 在此处插入 return 语句
	return str[i];
}

mString mString::operator+(const mString& m)
{
	char* total = new char[len + m.len + 1];
	strcpy(total, this->str);
	strcat(total, m.str);
	return mString(total);
}

mString mString::operator+(const char * s)
{
	char* total = new char[len + strlen(s) + 1];
	strcpy(total, this->str);
	strcat(total, s);
	return mString(total);
}

void mString::stringlow()
{
	str = _strlwr(str);
}

void mString::stringup()
{
	str = _strupr(str);
}

int mString::has(char c)
{
	int res = 0;
	size_t l = strlen(str);
	for (size_t i = 0; i < l; ++i)
	{
		if (str[i] == c) res++;
	}
	return res;
}

int mString::HowMany()
{
	return num_strings;
}

mString operator+(const char * s, const mString & m)
{
	char* total = new char[strlen(s) + m.len + 1];
	strcpy(total, s);
	strcat(total, m.str);
	return mString(total);
}

bool operator<(const mString & ms, const mString & ms2)
{
	return (strcmp(ms.str, ms2.str) < 0);
}

bool operator>(const mString & ms, const mString & ms2)
{
	return ms2 < ms;
}

bool operator==(const mString & ms, const mString & ms2)
{
	return (strcmp(ms.str, ms2.str) == 0);
}

ostream & operator<<(ostream & os, const mString & ms)
{
	// TODO: 在此处插入 return 语句
	os << ms.str;
	return os;
}

istream & operator>>(istream & is, mString & ms)
{
	// TODO: 在此处插入 return 语句
	char temp[mString::CINLIM];
	is.get(temp, mString::CINLIM);
	//const char* p = temp;

	if (is)
		ms = temp;
	while (is && is.get() != '\n')
	{
		continue;
	}
	return is;
}

void mStringClassTest()
{
	mString s1(" and I am a C++ student.");
	mString s2 = "Please enter your name: ";
	mString s3;
	cout << s2;
	cin >> s3;
	s2 = "My name is " + s3;
	cout << s2 << ".\n";
	s2 = s2 + s1;
	s2.stringup();
	cout << "The string\n" << s2 << "\ncontains " << s2.has('A') << " 'A' characters in it.\n";
	s1 = "red";
	mString rgb[3] = { mString(s1), mString("green"), mString("blue") };
	cout << "Enter the name of a primary color for mixing light: ";
	mString ans;
	bool success = false;
	while (cin >> ans)
	{
		ans.stringlow();
		for (int i = 0; i < 3; ++i)
		{
			if (ans == rgb[i])
			{
				cout << "That's right!\n";
				success = true;
				break;
			}
		}
		if (success) break;
		else cout << "Try again!\n";
	}
	cout << "Bye\n";
}
