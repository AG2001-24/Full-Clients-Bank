// ConsoleApplication40.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <iomanip>
#include "clsMainScreen.h"

using namespace std;

void ReadClientInf(clsBankClient &Client)
{
	cout << "\nPlease Enter First Name : ";
	Client.FirstName = clsInputValidate::ReadString();

	cout << "\nPlease Enter Last Name : ";
	Client.LastName = clsInputValidate::ReadString();

	cout << "\nPlease Enter Email : ";
	Client.Email = clsInputValidate::ReadString();

	cout << "\nPlease Enter Phone : ";
	Client.Phone = clsInputValidate::ReadString();

	cout << "\nPlease Enter PinCode : ";
	Client.PinCode = clsInputValidate::ReadString();

	cout << "\nPlease Enter Account Balance : ";
	Client.AccountBalance = clsInputValidate::ReadFloatNumber();

}








void PrintClientRecordBalanceLine(clsBankClient Client)
{

	cout << "| " << setw(15) << left << Client.AccountNumber();
	cout << "| " << setw(40) << left << Client.FullName();
	cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowTotalBalances()
{

	vector <clsBankClient> vClients = clsBankClient::GetClientsList();

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalances = clsBankClient::GetTotalBalance();

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else

		for (clsBankClient Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
	cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")\n";
}

int main()
{

	clsMainScreen::ShowMainMenue();




    return 0;
}

