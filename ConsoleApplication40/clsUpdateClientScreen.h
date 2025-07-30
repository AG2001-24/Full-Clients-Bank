#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{

	static void _ReadClientInf(clsBankClient &Client)
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


	static void ShowUpdateClient()
	{
		_DrawScreenHeader("\tUpdate Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExsit(AccountNumber))
		{
			cout << "\nAccount Number is Not Found Choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintObject(Client);

		cout << "\n\nUpdate Client\n";
		cout << "-----------------------\n";

		_ReadClientInf(Client);

		clsBankClient::enSaveResults SaveResult;

		SaveResult = Client.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "Account Succeeded Successfully.\n";
			_PrintObject(Client);
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		}
	}


};

