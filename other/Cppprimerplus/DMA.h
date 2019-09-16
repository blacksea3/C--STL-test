#pragma once
#include "global.h"

//DMA类, 抽象基类
class DMA
{
public:
	DMA();
	virtual ~DMA();
	virtual void View() = 0;
};

//
class baseDMA : public DMA
{
private:
	string label;
	int rating;
public:
	baseDMA(string label = "", int rating = 0);
	virtual void View();
};

//
class lacksDMA : public DMA
{
private:
	string color;
public:
	lacksDMA(string color = "");
	virtual void View();
};

//
class hasDMA : public DMA
{
private:
	string style;
public:
	hasDMA(string style = "");
	virtual void View();
};

void DMAClassTest();
