//Program includes extra credit

#include "stdafx.h"
#include <iostream> 
#include <ctime>
using namespace std;

class BankAccount
{
public:
	int day;
	int accountID;
	int accountTerm;
	int accountType;
	int openDay;
	int openMonth;
	int openYear;
	double interest = 0;
	double balance = 0;

	void display();
	virtual int balanceChecker(double amount);
	virtual int deposit(double amount);
	virtual int withdraw(double amount);
};

void BankAccount::display()
{
	const char *accName = new char[50];
	if (accountType == 1) {
		accName = "Checking";
	} else if (accountType == 2) {
		accName = "Savings";
	}
	else if (accountType == 3) {
		accName = "Certificate of Deposit";
	} else { 
		accName = "Unknown";
	}
		cout << "Account Opened: " << openMonth << "/" << openDay << "/" << openYear << endl;
		cout << "Account Number: " << accountID << endl;
		cout << "Account Type: " << accName << endl;
		if (interest > 0) { cout << "Interest Rate: " << interest << endl; }
		if (accountTerm > 0) { cout << "CD Term: " << accountTerm << endl; }
		cout << "Balance: " << balance << endl;
		cout << "-----------------------------------------------------" << endl;


}
//Keeps accounts from going negative
int BankAccount::balanceChecker(double amount)
{

	if (balance - amount < 0) {
		cout << "ERROR: Insufficient funds" << endl;
		return(-1);
	}
	else {
		return(0);
	}
}
int BankAccount::deposit(double amount)
{
	balance += amount;
	return (0);
}
int BankAccount::withdraw(double amount)
	{
		BankAccount::balanceChecker(amount);
		balance -= amount;
		return(0);	
	}
class saving : public BankAccount
{
public:
	
	saving()
	{
		//Checking = "1" Saving = "2" CD = "3"
		accountType = 2;
	}
	void updateAccount()
	{
		if (balance >= 10000)
		{
			interest = 2;
		}
		else
		{
			interest = 1;
		}
	}
	void interestpaid()
	{
		balance += (balance * (interest / 100));
		updateAccount();
	}
	int deposit(double amount)
	{
		BankAccount::deposit(amount);
		updateAccount();
		return (0);

	}
	int withdraw(double amount)
	{
		//Withdraw with $2 fee
		BankAccount::withdraw(w + 2);
		updateAccount();
		return (0);
	}
};


class checking : public BankAccount
{
public:
	checking()
	{
		//Checking = "1" Saving = "2" CD = "3"
		accountType = 1;
		interest = 0;
	}

	void updateAccount()
	{
		BankAccount::balanceChecker(5);
		if (balance < 500)
		{
			balance -=  5;
		}
	}
	void orderChecks()
	{
		BankAccount::balanceChecker(15);
		balance -= 15;
	}
	int deposit(double amount)
	{
		BankAccount::deposit(amount);
		updateAccount();
		return (0);

	}
	int withdraw(double amount)
	{
		BankAccount::withdraw(amount);
		updateAccount();
		return (0);
	}

};

class CD : public BankAccount
{
public:
	CD()
	{
		//Checking = "1" Saving = "2" CD = "3"
		accountType = 3;
	}
	void updateAccount(int term)
	{
		accountTerm = term;
		if (term >= 5) {
			interest = 10;
		}
		else {
			interest = 5;
		}
	}
	int deposit(double amount, int term)
	{
		BankAccount::deposit(amount);
		updateAccount(term);
		return (0);
	}
	void interestpaid()
	{
		balance += (balance * (interest / 100));
	}
	int withdraw(double amount)
	{
		//10% fee for withdraw early
		int penalty = 10;
		amount -= (balance * (penalty / 100));
		BankAccount::withdraw(amount);
		updateAccount(accountTerm);
		return (0);
	}
	
};



int main()
{
	//Extra credit Getting Local Time
	time_t t = time(NULL);
	tm *my_time = localtime(&t);
	struct tm tm = *localtime(&t);
	tm.tm_year = 1900 + my_time->tm_year;
	tm.tm_mon = 1 + my_time->tm_mon;
	tm.tm_mday = my_time->tm_mday;
	//Actual Program
	saving savings;
	checking check;
	CD cid;
	int rand_num = rand();
	//Saving Info
	savings.accountID = rand_num + 1000;
	savings.openDay = tm.tm_mday;
	savings.openMonth = tm.tm_mon;
	savings.openYear = tm.tm_year;
	savings.deposit(10000);
	//Checking Info
	check.accountID = rand_num + 1001;
	check.openDay = tm.tm_mday;
	check.openMonth = tm.tm_mon;
	check.openYear = tm.tm_year;
	check.deposit(600);
	//CD Info
	cid.accountID = rand_num + 1002;
	cid.openDay = tm.tm_mday;
	cid.openMonth = tm.tm_mon;
	cid.openYear = tm.tm_year;
	cid.deposit(10000,5);
	//Display information
	savings.display();
	check.display();
	cid.display();
	//Calculate Interest
	savings.interestpaid();
	cid.interestpaid();
	//Order Checks
	check.orderChecks();
	//Withdraw 200 from checking
	check.withdraw(200);
	//withdraw 1000 from savings
	savings.withdraw(1000);
	//Early Withdraw
	cid.withdraw(2000);
	//Display information
	savings.display();
	check.display();
	cid.display();


    return 0;
}

