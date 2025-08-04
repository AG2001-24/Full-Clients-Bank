#pragma once

#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDate.h"

using namespace std;
class clsTransferScreen : protected clsScreen
{
protected:

	static string _ReadAccountNumber() 
	{
		string AccountNumber;

		cout << "\nPlease Enter Account Number to Tranfer From : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExsit(AccountNumber))
		{
			cout << "\nAccount Number for Client From is Not Found ,Please enter another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static float _ReadAmount(clsBankClient Client) 
	{
		float Amount;


		cout << "\nEnter Transfer Amount ? ";
		Amount = clsInputValidate::ReadFloatNumber();

		while (Amount > Client.AccountBalance)
		{
			cout << "Amount Exceeds the aveilable Balance, Enter another Amount  ? ";
			Amount = clsInputValidate::ReadFloatNumber();
		}

		return Amount;
	}

	static void _PrintClient(clsBankClient Client) 
	{
		cout << "\nClient Card:";
		cout << "\n________________________\n\n";
		cout << "Full Name   : " << Client.FullName() << endl;
		cout << "Acc. Number : " << Client.AccountNumber() << endl;
		cout << "Balance     : " << Client.AccountBalance << endl;
		cout << "\n________________________\n";
	}


public:

	static void ShowTransferScreen() 
	{
		_DrawScreenHeader("\t Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

		_PrintClient(DestinationClient);

		float Amount = _ReadAmount(SourceClient);

		char answer;

		cout << "\nAre you sure you wnat to perfomr this operation? Y/N : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.Username()))
			{
				cout << "\nTransform done Successfully.\n";
				
			}
			else
			{
				cout << "\nTransform Faild\n";
			}
		}

		_PrintClient(SourceClient);

		_PrintClient(DestinationClient);
	}
};

