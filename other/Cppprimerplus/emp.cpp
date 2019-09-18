#include "emp.h"



abstr_emp::abstr_emp()
{
	fname = "fn";
	lname = "ln";
	job = "job";
}

abstr_emp::abstr_emp(const string & fn, const string & ln, const string & j)
{
	fname = fn;
	lname = ln;
	job = j;
}

void abstr_emp::ShowAll() const
{
	cout << "firstname: " << fname << " lastname: " << lname << " job: " << job << endl;
}

void abstr_emp::SetAll()
{
	cout << "manual set properties:" << endl;
	cout << "Input firstname:";
	cin >> fname;
	cout << "\nInput lastname:";
	cin >> lname;
	cout << "\nInput job:";
	cin >> job;
	cout << endl;
	cout << "success load inputs of abstr_emp!";
}


abstr_emp::~abstr_emp()
{
}

ostream & operator<<(ostream & os, const abstr_emp & e)
{
	os << "firstname: " << e.fname << " lastname: " << e.lname << " job: " << e.job << endl;
	return os;
}

void empClassTest()
{
	employee em("Trip", "Harris", "Thumper");
	cout << em << endl;
	em.ShowAll();
	manager ma("Amorphia", "Spindragon", "Nuancer", 5);
	cout << ma << endl;
	ma.ShowAll();

	flink fi("Matt", "Oggs", "Oiler", "Juno Barr");
	cout << fi << endl;
	fi.ShowAll();

	highfink hf(ma, "Curly Kew");
	hf.ShowAll();

	cout << "Press a key for next phase:\n";
	cin.get();
	highfink hf2;
	hf2.SetAll();

	cout << "Using an abstr_emp* pointer:\n";
	abstr_emp* tri[4] = { &em, &fi, &hf, &hf2 };
	for (int i = 0; i < 4; ++i)
	{
		tri[i]->ShowAll();
	}
}

employee::employee() : abstr_emp()
{
}

employee::employee(const string & fn, const string & ln, const string & j) :
	abstr_emp(fn, ln, j)
{
}

void employee::ShowAll() const
{
	abstr_emp::ShowAll();
}

void employee::SetAll()
{
	abstr_emp::SetAll();
}

manager::manager() : abstr_emp()
{
	inchargeof = 0;
}

manager::manager(const string & fn, const string & ln, const string & j, int ico) :
	abstr_emp(fn, ln, j)
{
	inchargeof = ico;
}

manager::manager(const abstr_emp & e, int ico) :
	abstr_emp(e)
{
	inchargeof = ico;
}

manager::manager(const manager & m) :
	abstr_emp(m)
{
	inchargeof = m.inchargeof;
}

void manager::ShowAll() const
{
	abstr_emp::ShowAll();
	cout << "inchargeof: " << inchargeof << endl;
}

void manager::SetAll()
{
	abstr_emp::SetAll();
	cout << "\nInput inchargeof:";
	cin >> inchargeof;
	cout << endl;
	cout << "success load inputs of manager!";
}

flink::flink() : abstr_emp()
{
	reportsto = "default reportsto";
}

flink::flink(const string & fn, const string & ln, const string & j, const string & rpo) :
	abstr_emp(fn, ln, j)
{
	reportsto = rpo;
}

flink::flink(const abstr_emp & e, const string & rpo) :
	abstr_emp(e)
{
	reportsto = rpo;
}

flink::flink(const flink & e) : abstr_emp(e)
{
	reportsto = e.reportsto;
}

void flink::ShowAll() const
{
	;
}

void flink::SetAll()
{
	abstr_emp::SetAll();
	cout << "\nInput inchargeof:";
	cin >> reportsto;
	cout << endl;
	cout << "success load inputs of flink!";
}

highfink::highfink() : abstr_emp(), manager(), flink()
{
}

highfink::highfink(const string & fn, const string & ln, const string & j, const string & rpo, int ico) :
	abstr_emp(fn, ln, j), manager(fn, ln, j, ico), flink(fn, ln, j, rpo)
{
}

highfink::highfink(const abstr_emp & e, const string & rpo, int ico) :
	abstr_emp(e), manager(e, ico), flink(e, rpo)
{
}

highfink::highfink(const manager & m, const string & rpo) :
	abstr_emp(m), manager(m), flink(m, rpo)
{
}

highfink::highfink(const flink & f, int ico) :
	abstr_emp(f), manager(f, ico), flink(f)
{
}

highfink::highfink(const highfink & h) :
	abstr_emp(h), manager(h), flink(h)
{
}

void highfink::ShowAll() const
{
	abstr_emp::ShowAll();
	cout << "inchargeof: " << InChargeOf() << endl;
	cout << "reportsto: " << ReportsTo() << endl;
}

//有误, 晚上研究
void highfink::SetAll()
{
	abstr_emp::SetAll();
	cout << "Input inchargeof:";
	cin >> InChargeOf();
	cout << endl;
	cout << "Input reportsto:";
	cin >> ReportsTo();
	cout << endl;
	cout << "highfink set end" << endl;
}
