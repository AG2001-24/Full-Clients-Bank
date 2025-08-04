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
		

		short Permissions = 0;

		char answer = 'n';

		cout << "\nDo you want to giv full access? Y/N : ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			return (short)clsManageUsers::enPermissions::eAll;
		}

		cout << "\nDo you want to giv access to |\n";

		cout << "\nShow Client List ? Y/N :  ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
		  Permissions += clsManageUsers::enPermissions::pListClients;
		}


		cout << "\nAdd New Client ? Y/N :  ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			Permissions += clsManageUsers::enPermissions::pAddNewClient;
		}


		cout << "\nDelete Client ? Y/N :  ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			Permissions += clsManageUsers::enPermissions::pDeleteClient;
		}


		cout << "\nUpdate Client Info ? Y/N :  ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			Permissions += clsManageUsers::enPermissions::pUpdateClients;
		}


		cout << "\nFind Client ? Y/N :  ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			Permissions += clsManageUsers::enPermissions::pFindClient;
		}


		cout << "\nTransaction ? Y/N :  ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			Permissions += clsManageUsers::enPermissions::pTranactions;
		}


		cout << "\nManage Users  ? Y/N :  ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			Permissions += clsManageUsers::enPermissions::pManageUsers;
		}

		cout << "\nLogin Register  ? Y/N :  ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			Permissions += clsManageUsers::enPermissions::pLoginRegister;
		}


		return Permissions;
	}

	static void _ReadUser(clsManageUsers &User)
	{


		char answer = 'n';


		cout << "\nPlease Enter First Name : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nPlease Enter Last Name : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nPlease Enter Email : ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nPlease Enter Phone  : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nPlease Enter Password : ";
		User.PinCode =clsInputValidate::ReadString();

		User.Permissions = _ReadPermissions();
		
	}
	
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


	static void AddNewUserScreen()
	{

		_DrawScreenHeader("\t Add New User Screen");

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

