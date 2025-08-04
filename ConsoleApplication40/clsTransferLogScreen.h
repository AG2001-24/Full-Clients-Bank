#pragma once

#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>
#include <vector>

using namespace std;
class clsTransferLogScreen : protected clsScreen
{

	static void _PrintRecordTrasferLog(clsBankClient::stTransferLog TransferLog) 
	{
		cout << "| " << setw(30) <<TransferLog.DateTime;
		cout << "| " << setw(12) << TransferLog.AccountNumberSource;
		cout << "| " << setw(12) << TransferLog.AccountNumberDestination;
		cout << "| " << setw(12) << TransferLog.Amount;
		cout << "| " << setw(12) << TransferLog.AccountBalanceSource;
		cout << "| " << setw(12) << TransferLog.AccountBalanceDestination;
		cout << "| " << setw(20) << TransferLog.Username;
	}
public:
	
	static void ShowListTransferLog() 
	{
			
		vector <clsBankClient::stTransferLog> vTransferLog = clsBankClient::GetTransferLog();

		string Title = "\t Transfer Log Screen";
		string SubTitle = "\t(" + to_string(vTransferLog.size()) + ") Transfer(s).";

		_DrawScreenHeader(Title,SubTitle);
		
		cout << "\n______________________________________________________________________________________________________________________\n\n";
		cout << "| " << setw(30) << "Date/Time";
		cout << "| " << setw(12) << "s.Acct";
		cout << "| " << setw(12) << "d.Acct";
		cout << "| " << setw(12) << "Amout";
		cout << "| " << setw(12) << "s.Balance";
		cout << "| " << setw(12) << "d.Balance";
		cout << "| " << setw(20) << "User";
		cout << "\n______________________________________________________________________________________________________________________\n";

		if (vTransferLog.size() == 0)
		{
			cout << "\t\t\tNo Clients Availabel In th System!\n";
		}
		else
		{
			for (clsBankClient::stTransferLog &TransferLog : vTransferLog)
			{
				_PrintRecordTrasferLog(TransferLog);
				
				cout << endl;
			}

			cout << "______________________________________________________________________________________________________________________\n";

		}
	}
};

