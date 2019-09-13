#include "Cow.h"

Cow::Cow()
{
}

Cow::Cow(const char * nm, const char * ho, double wt)
{
	size_t maxCount = 19;
	size_t numLen = strnlen_s(nm, 19);
	strncpy_s(this->name, nm, numLen);
	if (numLen == 19)
	{
		this->name[20] = '\0';
	}

	size_t hoLen = strlen(ho);
	this->hobby = new char[hoLen + 1];
	strcpy(this->hobby, ho);

	this->weight = wt;
}

Cow::Cow(const Cow & c)
{
	int nmLen = strnlen_s(c.name, 19);
	strncpy_s(this->name, c.name, nmLen);

	int hoLen = strlen(c.hobby);
	this->hobby = new char[hoLen + 1];
	strcpy(this->hobby, c.hobby);

	this->weight = c.weight;
}


Cow::~Cow()
{
	cout << "will delete: name:" << this->name << endl;
	delete[] hobby;
}

Cow & Cow::operator=(const Cow & c)
{
	// TODO: 在此处插入 return 语句
	if (this == &c)
	{
		return *this;
	}
	else
	{
		int nmLen = strnlen_s(c.name, 19);
		strncpy_s(this->name, c.name, nmLen);

		delete this->hobby;

		int hoLen = strlen(c.hobby);
		this->hobby = new char[hoLen + 1];
		strcpy(this->hobby, c.hobby);

		this->weight = c.weight;
		
		return *this;
	}
}

void Cow::ShowCow() const
{
	cout << "name: " << this->name << " hobby: " << this->hobby << " weight: " << this->weight << endl;
}



void callme1(Cow & c)
{
	cout << "pass by reference: ";
	c.ShowCow();
}

void callme2(Cow c)
{
	cout << "pass by value: ";
	c.ShowCow();
}

void CowClassTest()
{
	cout << "Start" << endl;
	Cow c1("name1", "hobby1", 1.0);
	Cow c2("name2", "hobby2", 2.0);
	Cow cc1("namename3", "hobbyhobby3", 3.0);
	c1.ShowCow();
	c2.ShowCow();
	cc1.ShowCow();
	callme1(c1);
	callme2(c2);

	cout << "Initialize one object to another:" << endl;
	Cow cc2 = cc1;
	cc2.ShowCow();

	cout << "Assign one object to another:" << endl;
	Cow cc3;
	cc3 = cc1;
	cc3.ShowCow();
	cout << "Exit" << endl;
}
