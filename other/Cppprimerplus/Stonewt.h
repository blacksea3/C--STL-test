#pragma once
#include "global.h"

class Stonewt
{
private:
	enum { Lbs_pet_stn = 14 };  //pounds per stone
	int stone;
	double pds_left;
	double pounds;  //stone = (int)pounds/Lbs_pet_stn, pds_left = (int)pounds%Lbs_pet_stn + pounds - (int)pounds
public:
	Stonewt(double lbs);   //单个总磅为输入参数
	Stonewt(int stone, double pds); //stone + pds
	Stonewt();
	Stonewt operator+(const Stonewt& s) const;
	Stonewt operator-(const Stonewt& s) const;
	Stonewt operator*(double n) const;
	inline bool operator==(const Stonewt& s) const { return pounds == s.pounds; };
	inline bool operator>=(const Stonewt& s) const { return pounds >= s.pounds; };
	inline bool operator<=(const Stonewt& s) const { return pounds <= s.pounds; };
	inline bool operator>(const Stonewt& s) const { return pounds > s.pounds; };
	inline bool operator<(const Stonewt& s) const { return pounds < s.pounds; };
	inline bool operator!=(const Stonewt& s) const { return pounds != s.pounds; };
	inline friend Stonewt operator*(double n, const Stonewt& s) { return s * n; };
	friend std::ostream& operator<<(std::ostream& os, const Stonewt& s);
	~Stonewt();
};

void StonewtClassTest();
