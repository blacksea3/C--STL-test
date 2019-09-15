#include "Cd.h"



Cd::Cd(const char * s1, const char * s2, int n, double x)
{
	performers = new char[strlen(s1) + 1];
	strcpy(performers, s1);
	label = new char[strlen(s2) + 1];
	strcpy(label, s2);
	selections = n;
	playtime = x;
}

Cd::Cd(const Cd & d)
{
	performers = new char[strlen(d.performers) + 1];
	strcpy(performers, d.performers);
	label = new char[strlen(d.label) + 1];
	strcpy(label, d.label);
	selections = d.selections;
	playtime = d.playtime;
}

Cd::Cd()
{
	performers = new char[1];
	label = new char[1];
	performers[0] = '\0';
	label[0] = '\0';
	selections = 0;
	playtime = 0.0;
}


Cd::~Cd()
{
	delete[] performers;
	delete[] label;
}

void Cd::Report() const
{
	cout << "performers: " << performers << endl;
	cout << "label: " << label << endl;
	cout << "selections: " << selections << endl;
	cout << "playtime: " << playtime << endl;
}

Cd & Cd::operator=(const Cd & d)
{
	if (&d == this)
	{
		return *this;
	}
	else
	{
		delete[] performers;
		delete[] label;
		performers = new char[strlen(d.performers) + 1];
		strcpy(performers, d.performers);
		label = new char[strlen(d.label) + 1];
		strcpy(label, d.label);
		selections = d.selections;
		playtime = d.playtime;
		return *this;
	}
}

Classic::Classic() : Cd()
{
	mainWork = new char[1];
	mainWork[0] = '\0';
}

Classic::Classic(const char* mainwork, const char * s1, const char * s2, int n, double x) : Cd(s1, s2, n, x)
{
	mainWork = new char[strlen(mainwork) + 1];
	strcpy(mainWork, mainwork);
}

Classic::Classic(const Classic & d) : Cd(d)
{
	mainWork = new char[strlen(d.mainWork) + 1];
	strcpy(mainWork, d.mainWork);
}

void Classic::Report() const
{
	Cd::Report();
	cout << "mainWork: " << mainWork << endl;
}

Classic::~Classic()
{
	delete[] mainWork;
}

Classic & Classic::operator=(const Classic & d)
{
	if (&d == this)
	{
		return *this;
	}
	else
	{
		Cd::operator=(d);
		delete[] mainWork;
		mainWork = new char[strlen(d.mainWork) + 1];
		strcpy(mainWork, d.mainWork);
		return *this;
	}
}

void Bravo(const Cd& disk)
{
	disk.Report();
}

void CdClassTest()
{
	Cd c1("Beatles", "Capitol", 14, 35.5);
	Classic c2 = Classic("Piano Sonata in B flat, Fantasia in C", "Alfred Brendel", "Philips", 2, 57.17);

	Cd *pcd = &c1;
	cout << "Using object diredtedly:" << endl;
	c1.Report();
	c2.Report();

	cout << "Using type cd* pointer to objects:" << endl;
	pcd->Report();
	pcd = &c2;
	pcd->Report();

	cout << "Calling a function with a Cd reference argument:" << endl;
	Bravo(c1);
	Bravo(c2);

	cout << "Testing assignment: " << endl;
	Classic copy;
	copy = c2;
	copy.Report();
}
