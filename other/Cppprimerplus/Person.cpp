#include "Person.h"

Person::Person(const string & ln, const char * fn)
{
	this->lname = ln;
	size_t firstNameLength = strnlen_s(fn, 25);
	if (firstNameLength == 25) //ǿ�ƽض�
	{
		this->fname[24] = '\n';
		strncpy_s(this->fname, fn, 24);
	}
	else
	{
		strncpy_s(this->fname, fn, 24);
	}
}

//firstname, lastname format
void Person::Show() const
{
	cout << this->fname << " " << this->lname.c_str() << endl;
}

//lastname, firstname format
void Person::FormalShow() const
{
	cout << this->lname.c_str() << this->fname << " " << endl;
}

Person::~Person()
{
}

void PersonClassTest()
{
	Person one;
	Person two("Smythecraft");
	Person three("Dimwiddy", "Sam");
	Person four("Dimwiddy", "abcdefghijklmnopqrstuvwxyz");
	Person five("Dimwiddy", "abcdefghijklmnopqrstuvwxy");
	Person six("Dimwiddy", "abcdefghijklmnopqrstuvwx");
	Person seven("Dimwiddy", "abcdefghijklmnopqrstuvw");

	vector<Person> vP = { one, two, three, four, five, six, seven };

	for (auto& iter_vP : vP)
	{
		cout << endl;
		iter_vP.Show();
		cout << endl;
		iter_vP.FormalShow();
	}
}
