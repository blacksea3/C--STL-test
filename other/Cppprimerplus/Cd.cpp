#include "Cd.h"



Cd::Cd(const char * s1, const char * s2, int n, double x)
{
	int s1Size = strlen(s1);
	if (s1Size > 49)
	{
		strncpy_s(performers, 49, s1, 49);
		performers[49] = '\0';
	}
	else
	{
		strcpy(performers, s1);
	}

	int s2Size = strlen(s2);
	if (s2Size > 19)
	{
		strncpy_s(label, 19, s2, 19);
		label[19] = '\0';
	}
	else
	{
		strcpy(label, s2);
	}
	selections = n;
	playtime = x;
}

Cd::Cd()
{
	performers[0] = '\0';
	label[0] = '\0';
	selections = 0;
	playtime = 0.0;
}


Cd::~Cd()
{
}

void Cd::Report() const
{
	cout << "performers: " << performers << endl;
	cout << "label: " << label << endl;
	cout << "selections: " << selections << endl;
	cout << "playtime: " << playtime << endl;
}

Classic::Classic() : Cd()
{
	mainWork[0] = '\0';
}

Classic::Classic(const char* mainwork, const char * s1, const char * s2, int n, double x) : Cd(s1, s2, n, x)
{
	int s3Size = strlen(mainwork);
	if (s3Size > 39)
	{
		strncpy_s(mainWork, 39, mainwork, 39);
		mainWork[39] = '\0';
	}
	else
	{
		strcpy(mainWork, mainwork);
	}
}

void Classic::Report() const
{
	Cd::Report();
	cout << "mainWork: " << mainWork << endl;
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
