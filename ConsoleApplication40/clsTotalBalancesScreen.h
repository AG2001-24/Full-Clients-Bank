#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsScreen.h"
#include <iomanip>

using namespace std;

class clsShowTotalBalancesScreen : protected clsScreen
{

	static void _PrintClientRecordBalanceLine(clsBankClient Client)
	{

		cout << "\t\t\t\t| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(40) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;

	}
public:
	

	static void ShowTotalBalancesScreen()
	{


		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\tBalances List Screen";
		string SubTitle = "\t   (" + to_string(vClients.size()) + ") Clients.";

		_DrawScreenHeader(Title ,SubTitle);

		cout << "\n\t\t\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t\t\t\t| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n\t\t\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		double TotalBalances = clsBankClient::GetTotalBalance();

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else

			for (clsBankClient Client : vClients)
			{
				_PrintClientRecordBalanceLine(Client);
				cout << endl;
			}

		cout << "\n\t\t\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
		cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")\n";
	}
};

