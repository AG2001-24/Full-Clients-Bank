#pragma once

#include <iostream>
#include <string>
#include "clsInputValidate.h"
#include "clsManageUsers.h"
#include "clsScreen.h"

using namespace std;

class clsAddNewUser : clsScreen
{
private:

	static short _ReadPermissions()
	{
		short arrNum[] = { 1,2,4,8,16,32,64 };

		short Permissions = 0;

		char answer = 'n';

		cout << "\nShow Client List ? Y/N :  ";
		cin >> answer;

		Permissions += tolower(answer) == 'y' ? 1 : 0;

		cout << "\nAdd New Client ? Y/N :  ";
		cin >> answer;

		Permissions += tolower(answer) == 'y' ? 2 : 0;

		cout << "\nDelete Client ? Y/N :  ";
		cin >> answer;

		Permissions += tolower(answer) == 'y' ? 4 : 0;

		cout << "\nUpdate Client Info ? Y/N :  ";
		cin >> answer;

		Permissions += tolower(answer) == 'y' ? 8 : 0;

		cout << "\nFind Client ? Y/N :  ";
		cin >> answer;

		Permissions += tolower(answer) == 'y' ? 16 : 0;

		cout << "\nTransaction ? Y/N :  ";
		cin >> answer;

		Permissions += tolower(answer) == 'y' ? 32 : 0;

		cout << "\nManage Users ? Y/N :  ";
		cin >> answer;

		Permissions += tolower(answer) == 'y' ? 64 : 0;


		return Permissions;
	}

	static void _ReadUser(clsManageUsers &User)
	{
		cout << "\nPlease Enter Pincode : ";
		User.PinCode = clsInputValidate::ReadString();

		char answer = 'n';


		if (User.Username() == "admin")
		{
			return;
		}

		cout << "\nDo you want to give all permissions? Y/N : ";
		cin >> answer;
		cout << endl;



		if (tolower(answer) == 'y')
		{
			User.Permissions = -1;
		}
		else
		{
			User.Permissions = _ReadPermissions();
		}
	}
	
	static void _Print(clsManageUsers User)
	{
		cout << "\nCard User";
		cout << "\n-----------------------------";
		cout << "\nUsername    : " << User.Username();
		cout << "\nPassword    : " << User.PinCode;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n-----------------------------\n";
	}
public:


	static void AddNewUserScreen()
	{

		_DrawScreenHeader("Add New User Screen");

		string Username = "";

		cout << "\nPlease Enter Username : ";
		Username = clsInputValidate::ReadString();

		while (clsManageUsers::IsUserExsist(Username))
		{
			cout << "\nThis user exists. Please enter another username : ";
			Username = clsInputValidate::ReadString();
		}

		clsManageUsers User = clsManageUsers::GetAddNewUser(Username);

		_ReadUser(User);

		clsManageUsers::enSaveResults SaveResult;

		SaveResult = User.Save();

		switch (SaveResult)
		{
		case clsManageUsers::enSaveResults::svSucceeded:
		{
			cout << "\nThe new user has been added successfully.\n";
			_Print(User);
			break;
		}
		case clsManageUsers::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nThe user was not added because the data is empty.\n";
		}
		case clsManageUsers::enSaveResults::svFaildUsernameExists:
		{
			cout << "\nThe user was not added because he already exists.\n";
		}

		}

	}
};

