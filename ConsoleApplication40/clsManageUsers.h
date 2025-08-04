#pragma once

#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsPerson.h"
#include <vector>
#include "clsString.h"
#include <fstream>
#include "clsUtil.h"

using namespace std;

class clsManageUsers : public clsPerson {

private:

	enum enMode { eEmptyMode = 0, eUpdateMode = 1, eAddNewMode = 2 };
	enMode _Mode;

	string _Username;
	string _PinCode;
	short _Permissions = -1;

	bool _MarkForDelete = false;

	string _PreparelLogInRecord(string Saparator="#//#") 
	{
		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Saparator;
		LoginRecord += _Username + Saparator;
		LoginRecord += clsUtil::EncryptText( _PinCode,5) + Saparator;
		LoginRecord += to_string(_Permissions);

		return LoginRecord;
	}

	static string _ConvertUserObjectToLine(clsManageUsers UserObject, string Saparator = "#//#")
	{

		string Line = "";
		Line += UserObject.FirstName + Saparator;
		Line += UserObject.LastName + Saparator;
		Line += UserObject.Email + Saparator;
		Line += UserObject.Phone + Saparator;
		Line += UserObject.Username() + Saparator;
		Line += clsUtil::EncryptText( UserObject.PinCode , 5) + Saparator;
		Line += to_string(UserObject.Permissions);

		return Line;
	}

	static clsManageUsers _ConvertLineToUserObject(string Line, string Saparator = "#//#")
	{


		vector <string> vUsers = clsString::Split(Line, Saparator);

		return clsManageUsers(enMode::eUpdateMode, vUsers[0], vUsers[1], vUsers[2],  vUsers[3], vUsers[4],clsUtil::DecryptText( vUsers[5],5), stoi(vUsers[6]));

	}

	static clsManageUsers _GetEmptyObjectUser()
	{
		return clsManageUsers(enMode::eEmptyMode, "", "", "", "", "", "", 0);
	}

	static void _AddNewUserToFile(string UserObject)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << UserObject << endl;

			MyFile.close();
		}
	}

	static vector <clsManageUsers> _LoadDateUsersFromFile()
	{
		vector <clsManageUsers> vUsers;

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vUsers.push_back(_ConvertLineToUserObject(Line));
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveDataUsersToFile(vector <clsManageUsers> vUsers)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsManageUsers &User : vUsers)
			{
				if (User._MarkForDelete == false)
				{
					MyFile << _ConvertUserObjectToLine(User) << endl;
				}


			}

			MyFile.close();
		}
	}

	
	void _AddNewUser()
	{
		_AddNewUserToFile(_ConvertUserObjectToLine(*this));
	}

	void _UpdateUser()
	{
		vector <clsManageUsers> vUsers = _LoadDateUsersFromFile();

		for (clsManageUsers &User : vUsers)
		{
			if (User.Username() == Username())
			{
				User = *this;
				break;
			}
		}

		_SaveDataUsersToFile(vUsers);
	}



public:

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128
	};


	clsManageUsers(enMode Mode, string FirstName, string LastName, string Email, string Phone, string Username, string PinCode, short Permissions)
		: clsPerson(FirstName,LastName,Email,Phone)
	{
		_Mode = Mode;
		_PinCode = PinCode;
		_Username = Username;
		_Permissions = Permissions;
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;

	}

	bool IsEmpty()
	{
		return _Mode == enMode::eEmptyMode;
	}

	string Username()
	{
		return _Username;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetPermissions(short Permissions)
	{
		_Permissions = Permissions;
	}

	short GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property (get = GetPermissions, put = SetPermissions)) short Permissions;


	bool Delete()
	{
		vector <clsManageUsers> vUsers = _LoadDateUsersFromFile();

		for (clsManageUsers &User : vUsers)
		{
			if (User.Username() == Username())
			{
				if (Username() == "admin")
				{
					return false;
				}
				else
				{
					User._MarkForDelete = true;
					break;
				}

			}
		}

		_SaveDataUsersToFile(vUsers);

		*this = _GetEmptyObjectUser();

		return true;
	}

	static clsManageUsers Find(string Username)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsManageUsers User = _ConvertLineToUserObject(Line);

				if (User.Username() == Username)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();
		}

		return _GetEmptyObjectUser();
	}

	static clsManageUsers Find(string Username, string PinCode)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsManageUsers User = _ConvertLineToUserObject(Line);

				if (User.Username() == Username && User.PinCode == PinCode)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();
		}

		return _GetEmptyObjectUser();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUsernameExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::eUpdateMode:
		{
			_UpdateUser();
			return enSaveResults::svSucceeded;
		}

		case enMode::eEmptyMode:
		{
			return enSaveResults::svFaildEmptyObject;

		}

		case enMode::eAddNewMode:
		{
			if (clsManageUsers::IsUserExsist(Username()))
			{
				return enSaveResults::svFaildUsernameExists;
			}
			else
			{
				_AddNewUser();
				_Mode = enMode::eUpdateMode;
				return enSaveResults::svSucceeded;
			}
		}


		}
	}

	static bool IsUserExsist(string Username)
	{
		clsManageUsers User = clsManageUsers::Find(Username);

		return !User.IsEmpty();
	}

	static clsManageUsers GetAddNewUser(string Username)
	{
		return clsManageUsers(enMode::eAddNewMode, "", "", "", "", Username, "", 0);
	}

	static vector <clsManageUsers> GetUsersList()
	{
		return _LoadDateUsersFromFile();
	}

	void RegisterLogin() 
	{
		string stDateLine = _PreparelLogInRecord();

		fstream MyFile;

		MyFile.open("RegisterLogin.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDateLine << endl;
			MyFile.close();
		}
	}

	
};

