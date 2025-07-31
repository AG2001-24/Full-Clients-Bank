#pragma once

#include <iostream>
#include <string>
#include "clsInputValidate.h"
#include <iomanip>
#include "clsManageUsers.h"
#include "clsScreen.h"

using namespace std;

class clsShowListUsersScreen : protected clsScreen
{
	static void _PrintUserRecord(clsManageUsers User)
	{
		cout << "| " << left << setw(40) << User.Username();
		cout << "| " << left << setw(20) << User.PinCode;
		cout << "| " << left << setw(20) << User.Permissions;
	}
public:



	static void ShowListLUsersScreen()
	{
		vector <clsManageUsers> vUser = clsManageUsers::GetUsersList();


		string Title = "\tUsers List Screen";
		string SubTitle = "\t   (" + to_string(vUser.size()) + ") Users.";

		_DrawScreenHeader(Title,SubTitle);

		cout << "\n____________________________________________________________________________________\n\n";
		cout << "| " << left << setw(40) << "Username";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(20) << "Permissions";
		cout << "\n____________________________________________________________________________________\n";

		for (clsManageUsers &User : vUser)
		{
			_PrintUserRecord(User);
			cout << endl;
		}

		cout << "____________________________________________________________________________________\n";
	}
	
};

