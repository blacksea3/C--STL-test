#include "dsPolymorphism.h"

void fool()
{
	int i = 1;
	i++;
}

template<typename fABC>
void sPrint(fABC* abc)
{
	abc->Print();
}


void dynamicPolymorphism(int count, int times)
{
	vector<ABCbase*> v(count * 3);
	for (int i = 0; i < count; ++i)
	{
		v[i] = new cA();
	}
	for (int i = count; i < 2 * count; ++i)
	{
		v[i] = new cB();
	}
	for (int i = 2 * count; i < 3 * count; ++i)
	{
		v[i] = new cC();
	}
	clock_t startTime, endTime;
	startTime = clock();
	for (int i = 0; i < times; ++i)
		for (auto& iterv : v)
			iterv->Print();
	endTime = clock();
	cout << "Elapsed time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}

void staticPolymorphism(int count, int times)
{
	vector<sA*> vA(count);
	for (int i = 0; i < count; ++i)
	{
		vA[i] = new sA();
	}

	vector<sB*> vB(count);
	for (int i = 0; i < count; ++i)
	{
		vB[i] = new sB();
	}

	vector<sC*> vC(count);
	for (int i = 0; i < count; ++i)
	{
		vC[i] = new sC();
	}

	clock_t startTime, endTime;
	startTime = clock();
	for (int i = 0; i < times; ++i)
	{
		for (auto& iterv : vA)
			sPrint(iterv);
		for (auto& iterv : vB)
			sPrint(iterv);
		for (auto& iterv : vC)
			sPrint(iterv);
	}
	endTime = clock();
	cout << "Elapsed time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}

void dynamic_static_PolymorphismTest()
{
	dynamicPolymorphism(1000000, 1);
	staticPolymorphism(1000000, 1);
}

ABCbase::ABCbase()
{
	;
}

void cA::Print() const
{
	fool();
}

void cB::Print() const
{
	fool();
}

void cC::Print() const
{
	fool();
}

void sA::Print()
{
	fool();
}

void sB::Print()
{
	fool();
}

void sC::Print()
{
	fool();
}
