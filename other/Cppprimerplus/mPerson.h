#pragma once
#include "global.h"

//纯虚基类mPerson
class mPerson
{
private:
	string firstname;  //名
	string lastname;   //姓
public:
	mPerson(string f = "", string l = "");
	~mPerson();
	virtual void Show() = 0;
};

//枪手
class Gunslinger : public mPerson
{
private:
	double GunTime;  //拔枪时间
	int KeHen;       //刻痕数
public:
	Gunslinger(string f = "", string l = "", double guntime = 2.0, int kehen = 3);
	virtual void Show();
	double Draw();
};

class PokerPlayer : public mPerson
{
public:
	PokerPlayer(string f = "", string l = "");
	int Draw();
	virtual void Show();
};

class BadDude : public Gunslinger, public PokerPlayer
{
public:
	BadDude(string f = "", string l = "", double guntime = 2.0, int kehen = 3);
	double Gdraw();
	int Cdraw();
	void Show();
};

void mPersonClassTest();
