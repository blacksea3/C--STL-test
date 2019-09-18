#include "mPerson.h"



mPerson::mPerson(string f, string l)
{
	firstname = f;
	lastname = l;
}

mPerson::~mPerson()
{
}

void mPerson::Show()
{
	cout << "firstname: " << firstname << endl;
	cout << "lastname: " << lastname << endl;
}

Gunslinger::Gunslinger(string f, string l, double guntime, int inputkehen) : mPerson(f, l)
{
	GunTime = guntime;
	KeHen = inputkehen;
}

void Gunslinger::Show()
{
	mPerson::Show();
	cout << "Guntime: " << GunTime << endl;
	cout << "KeHen: " << KeHen << endl;
}

double Gunslinger::Draw()
{
	return GunTime;
}

PokerPlayer::PokerPlayer(string f, string l) : mPerson(f, l)
{

}

int PokerPlayer::Draw()
{
	srand(time(0));
	return rand() % 52;
}

void PokerPlayer::Show()
{
	mPerson::Show();
}

BadDude::BadDude(string f, string l, double guntime, int kehen) : Gunslinger(f, l, guntime, kehen)
{

}

double BadDude::Gdraw()
{
	return Gunslinger::Draw();
}

int BadDude::Cdraw()
{
	return PokerPlayer::Draw();
}

void BadDude::Show()
{
	Gunslinger::Show();
}

void mPersonClassTest()
{
	Gunslinger g("guns", "linger");
	cout << "g.Draw():" << g.Draw() << endl;
	g.Show();

	PokerPlayer p("pok", "pla");
	cout << "p.Draw()" << p.Draw() << endl;
	p.Show();

	BadDude b("bad", "dud", 15.6, 33);
	cout << "b.Cdraw()" << b.Cdraw() << endl;
	cout << "b.Gdraw()" << b.Gdraw() << endl;
	b.Show();
}
