#include "tv.h"

bool tv::volup()
{
	if (volumn < MaxVal)
	{
		volumn++;
		return true;
	}
	else return false;
}

bool tv::voldown()
{
	if (volumn > MinVal)
	{
		volumn--;
		return true;
	}
	else return false;
}

void tv::chanup()
{
	if (channel < maxchannel)
	{
		channel++;
	}
	else
	{
		channel = 1;
	}
}

void tv::chandown()
{
	if (channel > 1)
	{
		channel--;
	}
	else
	{
		channel = maxchannel;
	}
}

void tv::settings() const
{
	cout << "Tv is " << ((state == Off) ? "Off" : "On") << endl;
	if (state == On)
	{
		cout << "Volumn setting = " << volumn << endl;
		cout << "Channel setting = " << channel << endl;
		cout << "Mode = "
			<< (mode == Antenna ? "antenna" : "cable") << endl;
		cout << "Input = "
			<< (input == TV ? "TV" : "DVD") << endl;
	}
}

void tvClassTest()
{
	tv s42;
	cout << "Initial setting for 42\" TV : \n";
	s42.settings();
	s42.onoff();
	s42.chanup();
	cout << "\nAdjusted settings for 42\" TV:\n";
	s42.settings();
		
	Remote grey;
	grey.set_chan(s42, 10);
	grey.volup(s42);
	grey.volup(s42);
	cout << "\n42\" settings after using remote:\n";
	s42.settings();

	tv s58(tv::On);
	s58.set_mode();
	grey.set_chan(s58, 28);
	cout << "\n58\" settings:\n";
	s58.settings();

	cout << "remote state is: ";
	grey.showstate();
	s58.changeRemoteState(grey);
	cout << "after s58.changeRemoteState(grey), remote state is: ";
	grey.showstate();
}
