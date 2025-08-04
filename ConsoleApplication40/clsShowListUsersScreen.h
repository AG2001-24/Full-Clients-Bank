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
		cout << "| " << left << setw(20) << User.Username();
		cout << "| " << left << setw(30) << User.FullName();
		cout << "| " << left << setw(15) << User.Phone;
		cout << "| " << left << setw(30) << User.Email;
		cout << "| " << left << setw(15) << User.PinCode;
		cout << "| " << left << setw(15) << User.Permissions;


	}
public:



	static void ShowListLUsersScreen()
	{
		vector <clsManageUsers> vUser = clsManageUsers::GetUsersList();


		string Title = "\tUsers List Screen";
		string SubTitle = "\t   (" + to_string(vUser.size()) + ") Users.";

		_DrawScreenHeader(Title,SubTitle);

		cout << "\n________________________________________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(20) << "Usrname";
		cout << "| " << left << setw(30) << "Full Name";
		cout << "| " << left << setw(15) << "Phone";
		cout << "| " << left << setw(30) << "Email";
		cout << "| " << left << setw(15) << "Password";
		cout << "| " << left << setw(15) << "Permissions";
		cout << "\n________________________________________________________________________________________________________________________________________\n";

		if (vUser.size() == 0)
		{
			cout << "\t\t\tNo Clients Availabel In th System!\n";
		}
		else
		{
			for (clsManageUsers &User : vUser)
			{
				_PrintUserRecord(User);
				cout << endl;
			}

			cout << "________________________________________________________________________________________________________________________________________\n";

		}
		

	}
	
};

