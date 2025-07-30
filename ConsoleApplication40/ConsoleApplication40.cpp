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


void UpdateClient()
{
	
	string AccountNumber = "";

	cout << "\nPlease Enter Account Number : ";
	AccountNumber = clsInputValidate::ReadString();

	while (!clsBankClient::IsClientExsit(AccountNumber))
	{
		cout << "\nAccount Number is Not Found Choose another one : ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client = clsBankClient::Find(AccountNumber);
	Client.Print();

	cout << "\n\nUpdate Client\n";
	cout << "-----------------------\n";

	ReadClientInf(Client);

	clsBankClient::enSaveResults SaveResult;

	SaveResult = Client.Save();

	switch (SaveResult) 
	{
		case clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "Account Succeeded Successfully.\n";
			Client.Print();
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
	}
}

void AddNewClinet() 
{
	string AccountNumber = "";

	cout << "\nPlease Enter Account Number : ";
	AccountNumber = clsInputValidate::ReadString();

	while (clsBankClient::IsClientExsit(AccountNumber))
	{
		cout << "\nAccount Number is Exsit, Choose another one : ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client = clsBankClient::GetAddNewObject(AccountNumber);

	ReadClientInf(Client);

	clsBankClient::enSaveResults SaveResult = Client.Save();

	switch (SaveResult) 
	{
		case clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "Account Added Successfully.\n";
			Client.Print();
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;

		}
		case clsBankClient::enSaveResults::svFaildAccountNumberExists:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;

		}
	}
}

void Delete() 
{
	string AccountNumber = "";

	cout << "\nPlease Enter Account Number : ";
	AccountNumber = clsInputValidate::ReadString();

	while (!clsBankClient::IsClientExsit(AccountNumber))
	{
		cout << "\nAccount Number is Not Found Choose another one : ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client = clsBankClient::Find(AccountNumber);
	Client.Print();

	char answer = 'n';

	cout << "\nAre your sure you want to delete this client? Y/N : ";
	cin >> answer;

	if (tolower(answer) == 'y')
	{
		if (Client.Delete())
		{
			cout << "\nClient Deleted Successfully :-)\n";

			Client.Print();
		}
		else
		{
			cout << "\nError Client Was not Deleted\n";
		}
	}
	
}

void PrintCientRecord(clsBankClient Client)
{
	cout << " | " << left << setw(15) << Client.AccountNumber();
	cout << " | " << left << setw(20) << Client.FullName();
	cout << " | " << left << setw(12) << Client.Phone;
	cout << " | " << left << setw(20) << Client.Email;
	cout << " | " << left << setw(10) << Client.PinCode;
	cout << " | " << left << setw(12) << Client.AccountBalance;
}

void ShowClientsList()
{
	vector <clsBankClient> vClients = clsBankClient::GetClientsList();

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
	cout << " ----------------------------------------------------------------------------------------------------------------\n";
	cout << " | " << left << setw(15) << "Account Number";
	cout << " | " << left << setw(20) << "Client Name";
	cout << " | " << left << setw(12) << "Phone";
	cout << " | " << left << setw(20) << "Email";
	cout << " | " << left << setw(10) << "Pin Code";
	cout << " | " << left << setw(12) << "Balance";
	cout << "\n ----------------------------------------------------------------------------------------------------------------\n";

	if (vClients.size() == 0)
	{
		cout << "\t\t\tNo Clients Availabel In th System!\n";
	}
	else
	{
		for (clsBankClient &Client : vClients)
		{
			PrintCientRecord(Client);
			cout << endl;
		}
		cout << "\n ----------------------------------------------------------------------------------------------------------------\n";

	}

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
	ShowTotalBalances();

	clsMainScreen MainMenue;

	MainMenue.ShowMainMenue();
    return 0;
}

