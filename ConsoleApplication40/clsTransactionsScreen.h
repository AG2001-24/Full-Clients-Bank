#pragma once

#include <iostream>
#include <string>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsDepositScreen.h"
#include "clsWithdraw.h"
#include "clsTotalBalancesScreen.h"

using namespace std;
class clsTransactionsScreen : protected clsScreen
{
private :
	enum enMainMenueTransactionOpetion {eDeposit=1,eWithdraw=2,eTotalBalance=3,eeMainMenue=4};

	static short _ReadMainMenuTransactionOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 4]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1,4,"Enter Number Between 1 to 4 : ");

		return Choice;
	}

	static void _ShowDepositScreen() 
	{

		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShoWithdrawcreen()
	{

		clsWithdraw::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancetScreen()
	{

		clsShowTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _GoBackMainMenueTransaction() 
	{
		cout << "\nPress any key to go main manue transaction...";
		system("pause>0");

		ShowTransactionsScreen();

		
	}

	static void _PerformMainMenueOption(enMainMenueTransactionOpetion Choice)
	{
		switch (Choice)
		{
		case enMainMenueTransactionOpetion::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackMainMenueTransaction();
			break;
		case enMainMenueTransactionOpetion::eWithdraw:
			system("cls");
			_ShoWithdrawcreen();
			_GoBackMainMenueTransaction();
			break;
		case enMainMenueTransactionOpetion::eTotalBalance:
			system("cls");
			_ShowTotalBalancetScreen();
			_GoBackMainMenueTransaction();
			break;
		case enMainMenueTransactionOpetion::eeMainMenue:	

			break;
		}
	}
public:

	static void ShowTransactionsScreen() 
	{
		system("cls");
		_DrawScreenHeader("\t   Transactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t   Trnasaction Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] List Total Balance.\n";
		cout << setw(37) << left << "" << "\t[4] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		_PerformMainMenueOption(enMainMenueTransactionOpetion(_ReadMainMenuTransactionOption()));
	}

};

