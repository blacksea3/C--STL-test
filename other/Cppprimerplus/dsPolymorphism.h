#pragma once
#include "global.h"

class ABCbase
{
public:
	ABCbase();
	virtual void Print() const = 0;
	virtual ~ABCbase() {};
};

class cA : public ABCbase
{
public:
	cA() : ABCbase() {};
	virtual void Print() const;
	virtual ~cA() {};
};

class cB : public ABCbase
{
public:
	cB() : ABCbase() {};
	virtual void Print() const;
	virtual ~cB() {};
};

class cC : public ABCbase
{
public:
	cC() : ABCbase() {};
	virtual void Print() const;
	virtual ~cC() {};
};

class ABC
{
public:
	inline virtual void Print() = 0;
	ABC() {};
	virtual ~ABC() = 0;
};

class sA
{
public:
	void Print();
};

class sB
{
public:
	void Print();
};

class sC
{
public:
	void Print();
};

void dynamic_static_PolymorphismTest();
