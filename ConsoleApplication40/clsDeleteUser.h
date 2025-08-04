#pragma once

#include <iostream>
#include <string>
#include "clsInputValidate.h"
#include "clsManageUsers.h"
#include "clsScreen.h"


using namespace std;

class clsDeleteUser : clsScreen
{
private:

	static void _Print(clsManageUsers User)
	{
		cout << "\nCard User";
		cout << "\n-----------------------------";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nUsername    : " << User.Username();
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nPhone       : " << User.Phone;
		cout << "\nEmail       : " << User.Email;
		cout << "\nPassword    : " << User.PinCode;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n-----------------------------\n";
	}
public:

	static void DeleteUserScreen()
	{
		_DrawScreenHeader("\t  Delete User Screen");

		string Username = "";

		cout << "\nPlease Enter Username : ";
		Username = clsInputValidate::ReadString();

		while (!clsManageUsers::IsUserExsist(Username))
		{
			cout << "\nUsername is not found , Please another one : ";
			Username = clsInputValidate::ReadString();
		}

		clsManageUsers User = clsManageUsers::Find(Username);
		_Print(User);

		char answer = 'n';

		cout << "\nAre you sure you want to delete this user? Y/N : ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			if (User.Delete())
			{
				cout << "\nUser deleted successfully\n";

				_Print(User);
			}
			else
			{
				cout << "\nThis user cannot be deleted because he is an admin.\n";
			}
		}
	}
};

