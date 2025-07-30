#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"


using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
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

	static void ShowDeleteClient()
	{
		
		_DrawScreenHeader("\t Delete ClientScreen");

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

		char answer = 'n';

		cout << "\nAre your sure you want to delete this client? Y/N : ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";

				_PrintObject(Client);
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}
		}

	}
};

