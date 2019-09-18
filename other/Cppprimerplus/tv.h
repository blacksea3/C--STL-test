#pragma once
#include "global.h"
 
//前向声明, 因为tv中有friend class Remote, 
//删掉也可以正确编译运行, 但是IDE编辑会报错:( ??
//所以我保留了
class Remote;

class tv
{
private:
	friend class Remote;
public:
	enum {Off, On};
	enum {MinVal, MaxVal = 20};
	enum {Antenna, Cable};
	enum {TV, DVD};
	tv(int s = Off, int mc = 125) :state(s), volumn(5),
		maxchannel(mc), channel(2), mode(Cable), input(TV) {};
	void onoff() { state = (state == On) ? Off : On; };
	bool ison() const { return state == On; };
	bool volup();
	bool voldown();
	void chanup();
	void chandown();
	void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; };
	void set_input() { input = (input == TV) ? DVD : TV; };
	void settings() const; //显示所有设置
	void changeRemoteState(Remote& r);
private:
	int state;
	int volumn;
	int maxchannel;  //应当>=1
	int channel;     //合法值[1, maxchannel]
	int mode;
	int input;
};

class Remote
{
private:
	friend class tv;
	int mode;   //controls TV or DVD
	int state;
	enum { Regular, Interactive };  //状态模式, 常规或互动
public:
	Remote(int m = tv::TV) : mode(m) { state = Regular;  };
	bool volup(tv& t) { return t.volup(); };
	bool voldown(tv& t) { return t.voldown(); };
	void onoff(tv& t) { t.onoff(); };
	void chanup(tv& t) { t.chanup(); };
	void chandown(tv& t) { t.chandown(); };
	void set_chan(tv& t, int c) { t.channel = c; };
	void set_mode(tv& t) { t.set_mode(); };
	void set_input(tv& t) { t.set_input(); };
	void showstate() const 
	{ 
		cout << "state: " << (state == Regular ? "regular" : "interactive") << endl; 
	};
};

inline void tv::changeRemoteState(Remote& r)
{
	if (ison())
	{
		r.state = (r.state == r.Regular) ? r.Interactive : r.Regular;
	}
}

void tvClassTest();
