#include "Cpp11ptr.h"

void Cpp11ptrTest()
{
	unique_ptr<string> pu1(new string("ss"));
	unique_ptr<string> pu2; //nullptr
	cout << "*pu1: " << *pu1 << endl;
	//cout << "*pu2: " << *pu2 << endl;   //nullptr
	pu2 = move(pu1);
	//cout << "*pu1: " << *pu1 << endl;   //nullptr
	cout << "*pu2: " << *pu2 << endl;

	shared_ptr<string> ps1(new string("sss"));
	shared_ptr<string> ps2;
	ps2 = ps1;
	cout << "*ps1: " << *ps1 << endl;
	cout << "*ps2: " << *ps2 << endl;
}
