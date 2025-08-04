#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsManageUsers.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsUtil.h"
#include "Golbal.h"

using namespace std;


class clsLoginScreen : protected clsScreen
{

	static bool _Login()
	{
		bool LoginFiald = false;
		short FaildLoginCount = 0;

		string Username = "", Password = "";

		do
		{
	

			if (LoginFiald)
			{
				FaildLoginCount++;
				
				cout << "\nInvalied Usernane/Password\n";
				cout << "You have " << (3 -FaildLoginCount) << " Trialsto login\n";
			}

			if (FaildLoginCount == 3)
			{
				cout << "\nYou are locked after 3 faild trials\n\n";

				return false;
			}

			cout << "\nEnter Username : ";
			Username = clsInputValidate::ReadString();

			cout << "\nEnter Password : ";
			Password = clsInputValidate::ReadString();


			CurrentUser = clsManageUsers::Find(Username, Password);

			LoginFiald = CurrentUser.IsEmpty();


		} while (LoginFiald);
		
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		
		return true;


		
	}
public:

	static bool ShowLoginScreen() 
	{
		system("cls");

		_DrawScreenHeader("\t  Login Screen");

		return _Login();
		
		
	}
	
};

