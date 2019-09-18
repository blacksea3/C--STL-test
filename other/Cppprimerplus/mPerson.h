#pragma once
#include "global.h"

//�������mPerson
class mPerson
{
private:
	string firstname;  //��
	string lastname;   //��
public:
	mPerson(string f = "", string l = "");
	~mPerson();
	virtual void Show() = 0;
};

//ǹ��
class Gunslinger : public mPerson
{
private:
	double GunTime;  //��ǹʱ��
	int KeHen;       //�̺���
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
