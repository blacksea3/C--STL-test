#include "Stonewt.h"



Stonewt::Stonewt(double lbs)
{	
	pounds = lbs;
	stone = (int)pounds / Lbs_pet_stn;
	pds_left = (int)pounds%Lbs_pet_stn + pounds - (int)pounds;
}

Stonewt::Stonewt(int inputstone, double pds)
{
	pounds = Lbs_pet_stn * inputstone + pds;
	stone = (int)pounds / Lbs_pet_stn;
	pds_left = (int)pounds%Lbs_pet_stn + pounds - (int)pounds;
}

Stonewt::Stonewt()
{
	stone = 0;
	pds_left = 0.0;
	pounds = 0.0;
}

Stonewt Stonewt::operator+(const Stonewt & s) const
{
	return Stonewt(pounds + s.pounds);
}

Stonewt Stonewt::operator-(const Stonewt & s) const
{
	return Stonewt(pounds - s.pounds);
}

Stonewt Stonewt::operator*(double n) const
{
	return Stonewt(n * pounds);
}


Stonewt::~Stonewt()
{
}

std::ostream& operator<<(std::ostream & os, const Stonewt & s)
{
	os << s.stone << " stone, " << s.pds_left << " pounds\n";
	os << s.pounds << " pounds\n";
	return os;
}

void StonewtClassTest()
{
	vector<Stonewt> vst(20);

	for (int index = 0; index < 20; ++index)
	{
		Stonewt temp(index, (double)index/5.0);
		vst[index] = temp;
	}

	cout << "vst[1] = " << vst[1] << endl;
	cout << "vst[2] = " << vst[2] << endl;
	cout << "vst[2] + vst[1] = " << vst[2] + vst[1] << endl;
	cout << "vst[2] - vst[1] = " << vst[2] - vst[1] << endl;
	cout << "10 * vst[1] = " << 10 * vst[1] << endl;

	cout << "max st in vst: " << *max_element(vst.begin(), vst.end()) << endl;
	cout << "min st in vst: " << *min_element(vst.begin(), vst.end()) << endl;
	cout << "total st in vst: " << accumulate(vst.begin(), vst.end(), Stonewt()) << endl;

	Stonewt wt_stone_11_pds_0(11, 0.0);
	int greaterThan11Stone = 0;
	for (auto& st : vst)
	{
		if (st > wt_stone_11_pds_0)
			greaterThan11Stone++;
	}
	cout << "the number of st which greater than 11 stones in vst: " << greaterThan11Stone << endl;
}
