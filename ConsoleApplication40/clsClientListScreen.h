#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{
private:

	static void _PrintCientRecord(clsBankClient Client)
	{
		cout << " | " << left << setw(15) << Client.AccountNumber();
		cout << " | " << left << setw(20) << Client.FullName();
		cout << " | " << left << setw(12) << Client.Phone;
		cout << " | " << left << setw(20) << Client.Email;
		cout << " | " << left << setw(10) << Client.PinCode;
		cout << " | " << left << setw(12) << Client.AccountBalance;
	}
public:



	static void ShowClientsList()
	{
		if (!clsScreen::CheckAccessRights(clsManageUsers::enPermissions::pListClients))
		{
			return;
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t Client List Screen";
		string SubTitle = "\t     (" + to_string(vClients.size()) + ") Clients.";

		_DrawScreenHeader(Title, SubTitle);

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
				_PrintCientRecord(Client);
				cout << endl;
			}
			cout << "\n ----------------------------------------------------------------------------------------------------------------\n";

		}

	}

};

