#pragma once

#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsDepositScreen : protected clsScreen
{

private:

	static void _PrintObject(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}
public:

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t   Deposit Screen");

		string AccountNumber = "";

		cout << "Please Enter Account Nnumber : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExsit(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintObject(Client);

		float Amount;

		cout << "\nPlease Enter Diposit Amount : ";
		Amount = clsInputValidate::ReadFloatNumber();

		char answer = 'n';

		cout << "\nAre you sure you wnat perform this transaction? Y/N : ";
		cin >> answer;

		if (toupper(answer) == 'Y')
		{
			Client.Deposit(Amount);

			cout << "\nThe deposit operation was successful.\n\nNew Balance is " << Client.AccountBalance << endl;
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}

	}

};

