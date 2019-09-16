#include "DMA.h"



DMA::DMA()
{
}


DMA::~DMA()
{
}

void DMA::View()
{
	cout << "This is DMA" << endl;
}

baseDMA::baseDMA(string label, int rating)
{
	this->label = label;
	this->rating = rating;
}

void baseDMA::View()
{
	cout << "label: " << label << ". rating: " << rating << endl;
}

lacksDMA::lacksDMA(string color)
{
	this->color = color;
}

void lacksDMA::View()
{
	cout << "color: " << color << endl;
}

hasDMA::hasDMA(string style)
{
	this->style = style;
}

void hasDMA::View()
{
	cout << "style: " << style << endl;
}

void DMAClassTest()
{
	vector<DMA*> vd(20);
	for (int index = 0; index < 20; ++index)
	{
		switch (index%3)
		{
		case 0:
		{
			vd[index] = new baseDMA(to_string(index + 100), index);
			break;
		}
		case 1:
		{
			vd[index] = new lacksDMA(to_string(index + 100));
			break;
		}
		case 2:
		{
			vd[index] = new hasDMA(to_string(index + 100));
			break;
		}
		default:
			break;
		}
	}
	for (auto& pd : vd)
	{
		pd->View();
		delete pd;
	}
}
