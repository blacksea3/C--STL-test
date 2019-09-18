#pragma once
#include "global.h"

//
class abstr_emp
{
private:
	string fname;
	string lname;
	string job;
public:
	abstr_emp();
	abstr_emp(const string& fn, const string& ln, const string& j);
	virtual void ShowAll() const;
	virtual void SetAll();
	friend ostream& operator<<(ostream& os, const abstr_emp& e);
	virtual ~abstr_emp() = 0;
};

class employee : public abstr_emp
{
public:
	employee();
	employee(const string& fn, const string& ln, const string& j);
	virtual void ShowAll() const;
	virtual void SetAll();
};

class manager : virtual public abstr_emp
{
private:
	int inchargeof;
protected:
	int InChargeOf() const { return inchargeof; };
	int& InChargeOf() { return inchargeof; };
public:
	manager();
	manager(const string& fn, const string& ln, const string& j, int ico = 0);
	manager(const abstr_emp& e, int ico);
	manager(const manager& m);
	virtual void ShowAll() const;
	virtual void SetAll();
};

class flink : virtual public abstr_emp
{
private:
	string reportsto;
protected:
	const string ReportsTo() const { return reportsto; };
	string& ReportsTo() { return reportsto; };
public:
	flink();
	flink(const string& fn, const string& ln, const string& j,
		const string& rpo);
	flink(const abstr_emp& e, const string& rpo);
	flink(const flink& e);
	virtual void ShowAll() const;
	virtual void SetAll();
};

class highfink : public manager, public flink
{
public:
	highfink();
	highfink(const string& fn, const string& ln, const string& j,
		const string& rpo, int ico = 0);
	highfink(const abstr_emp& e, const string& rpo, int ico);
	highfink(const manager& m, const string& rpo);
	highfink(const flink& f, int ico);
	highfink(const highfink& h);
	virtual void ShowAll() const;
	virtual void SetAll();
};

void empClassTest();
