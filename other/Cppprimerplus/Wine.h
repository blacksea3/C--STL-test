#pragma once
#include "global.h"

class Wine
{
private:
	string name;
	pair<valarray<int>, valarray<int>> numYearRelation;
	int numYear;  //�ܹ��洢������ݵ�����, ��numYearRelation�Ĵ�С
public:
	Wine();
	Wine(const char* l, int y, const int yr[], const int bot[]);
	Wine(const char* l, int y);
	void GetBottles();
	const string& Label() const;
	int sum();
	void Show() const;
	~Wine();
};

void WineClassTest();
