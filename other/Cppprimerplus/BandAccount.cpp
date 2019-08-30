#include "BandAccount.h"

BandAccount::BandAccount(string name, string account, int saving)
{
	this->name = name;
	this->account = account;
	this->saving = saving;
}

BandAccount::~BandAccount()
{

}

void BandAccount::displayAll()
{
	cout << "Name:" << this->name.c_str() << endl;
	cout << "Account:" << this->account.c_str() << endl;
	cout << "Saving:" << this->saving << endl;
}

/*
 * 输入存款, 输出实际存储金额
 */
int BandAccount::depositMoney(int money)
{
	if (money <= 0) return 0;

	if (this->saving > INT_MAX - money)
	{
		int addMoney = INT_MAX - this->saving;
		this->saving = INT_MAX;
		return addMoney;
	}
	else
	{
		this->saving += money;
		return money;
	}
}

/*
 * 输入取款, 输出实际取出金额
 */
int BandAccount::drawMoney(int money)
{
	if (money <= 0) return 0;

	if (this->saving >= money)
	{
		this->saving -= money;
		return money;
	}
	else
	{
		int minusMoney = this->saving;
		this->saving = 0;
		return minusMoney;
	}
}

void BandAccountClassTest()
{
	cout << "BandAccount* bAccount = new BandAccount(\"name1\", \"acc1\", 10)" << endl;
	BandAccount* bAccount = new BandAccount("name1", "acc1", 10);
	cout << "bAccount->displayAll()" << endl;
	bAccount->displayAll();
	cout << "bAccount->depositMoney(-20)" << bAccount->depositMoney(-20) << endl;
	cout << "bAccount->displayAll()" << endl;
	bAccount->displayAll();
	cout << "bAccount->depositMoney(20)" << bAccount->depositMoney(20) << endl;
	cout << "bAccount->displayAll()" << endl;
	bAccount->displayAll();

	cout << "bAccount->depositMoney(INT_MAX)" << bAccount->depositMoney(INT_MAX) << endl;
	cout << "bAccount->displayAll()" << endl;
	bAccount->displayAll();

	cout << "bAccount->drawMoney(INT_MAX - 10)" << bAccount->drawMoney(INT_MAX - 10) << endl;
	cout << "bAccount->displayAll()" << endl;
	bAccount->displayAll();

	cout << "bAccount->drawMoney(-15)" << bAccount->drawMoney(-15) << endl;
	cout << "bAccount->displayAll()" << endl;
	bAccount->displayAll();

	cout << "bAccount->drawMoney(5)" << bAccount->drawMoney(5) << endl;
	cout << "bAccount->displayAll()" << endl;
	bAccount->displayAll();

	cout << "bAccount->drawMoney(15)" << bAccount->drawMoney(15) << endl;
	cout << "bAccount->displayAll()" << endl;
	bAccount->displayAll();
}
