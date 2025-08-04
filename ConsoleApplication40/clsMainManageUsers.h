#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsShowListUsersScreen.h"
#include "clsAddNewUser.h"
#include "clsDeleteUser.h"
#include "clsUpdateUser.h"
#include "clsFindUser.h"
using namespace std;

class clsMainManageUsers : protected clsScreen
{
private:

	enum enOptionManageUser { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eeeMainMenue = 6 };

	static short _ReadChoiceOptionMenueManageUsers() 
	{
		cout << left << setw(37) << "" << "Choose What do you want to do ? [1 to 6] ? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1,6,"Please Enter Number Between 1 to 6 : ");

		return Choice;
	}

	static void _ShowListUsers()
	{
		clsShowListUsersScreen::ShowListLUsersScreen();
	}

	static void _ShowAddNewUser()
	{
		clsAddNewUser::AddNewUserScreen();
	}

	static void _ShowDeleteUsers()
	{
		clsDeleteUser::DeleteUserScreen();
	}

	static void _ShowUpdateUsers()
	{
		clsUpdateUser::UpdateUserScreen();
	}

	static void _ShowFindUsers()
	{
		clsFindUser::FindUserScreen();
	}




	static void _GoBackMainMenue() 
	{
		cout << "Press enter any key to go back main menue Manage Users...";
		system("pause>0");

		ShowMainMenueUserScreen();
	
	}

	static void _PerformMainMenueOption(enOptionManageUser Choice) 
	{
		switch (Choice) 
		{
		case enOptionManageUser::eListUsers:
			{
				system("cls");
				_ShowListUsers();
				_GoBackMainMenue();
				break;
			}

		case enOptionManageUser::eAddNewUser:
		{
			system("cls");
			_ShowAddNewUser();
			_GoBackMainMenue();
			break;
		}
		case enOptionManageUser::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUsers();
			_GoBackMainMenue();
			break;
		}
		case enOptionManageUser::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUsers();
			_GoBackMainMenue();
			break;
		}
		case enOptionManageUser::eFindUser:
		{
			system("cls");
			_ShowFindUsers();
			_GoBackMainMenue();
			break;
		}
		case enOptionManageUser::eeeMainMenue:
		{
			break;
		}
		
		}
	}

public:

	
	static void ShowMainMenueUserScreen() 
	{
		if (!clsScreen::CheckAccessRights(clsManageUsers::enPermissions::pManageUsers))
		{
			cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

			system("pause>0");
			return;
		}

		system("cls");
		_DrawScreenHeader("\tManage Users Screen");
		
		cout << left << setw(37) << "" << "=========================================\n";
		cout << left << setw(37) << "" << "             Manage Users Menue\n";
		cout << left << setw(37) << "" << "=========================================\n";
		cout << left << setw(37) << "" << "       [1] List Users.\n";
		cout << left << setw(37) << "" << "       [2] Add New User.\n";
		cout << left << setw(37) << "" << "       [3] Delete User.\n";
		cout << left << setw(37) << "" << "       [4] Update User.\n";
		cout << left << setw(37) << "" << "       [5] Find User.\n";
		cout << left << setw(37) << "" << "       [6] Min Menue.\n";
		cout << left << setw(37) << "" << "=========================================\n";
		_PerformMainMenueOption(enOptionManageUser(_ReadChoiceOptionMenueManageUsers()));
	}
};

