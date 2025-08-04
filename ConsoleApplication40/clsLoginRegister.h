#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include "clsString.h"
#include <iostream>
#include <vector>
#include "Golbal.h"

using namespace std;

class clsLoginRegister :protected clsScreen
{

private:
	string _DateTime = "";
	string _UserName = "";
	string _Password = "";
	int _Permissions = 0;


	static clsLoginRegister _ConvertLineToObjectRegister(string Line,string Sapartor="#//#") 
	{
		clsLoginRegister Register;

		vector<string> vRegisters = clsString::Split(Line,Sapartor);

		Register._DateTime = vRegisters[0];
		Register._UserName = vRegisters[1];
		Register._Password = clsUtil::DecryptText(vRegisters[2], 5);
		Register._Permissions = stoi(vRegisters[3]);

		return Register;

	}

	static vector <clsLoginRegister> _GetDateFromRegisterFile()
	{
		vector <clsLoginRegister> vRegister;

		fstream MyFile;

		MyFile.open("RegisterLogin.txt",ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile,Line))
			{
				vRegister.push_back(_ConvertLineToObjectRegister(Line));
			}

			MyFile.close();
		}

		return vRegister;
	}

	static void _PrintRecordRegisters(clsLoginRegister Register) 
	{
		cout << "| " << left << setw(40) << Register._DateTime;
		cout << "| " << left << setw(20) << Register._UserName;
		cout << "| " << left << setw(20) << Register._Password;
		cout << "| " << left << setw(20) << Register._Permissions;
	}
public:

	static void ShowLoginListScreen() 
	{
		if (!clsScreen::CheckAccessRights(clsManageUsers::enPermissions::pLoginRegister))
		{
			return;
		}
		vector <clsLoginRegister> vRegisters = _GetDateFromRegisterFile();

		string Title = "\t Login Register Screen";
		string SubTitle = "\t (" + to_string(vRegisters.size())+") Record(s).";

		_DrawScreenHeader(Title,SubTitle);

		cout << "\n____________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(40) << "Date/Time";
		cout << "| " << left << setw(20) << "Username";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(20) << "Permmisions";
		cout << "\n____________________________________________________________________________________________________________\n";

		if (vRegisters.size() == 0)
		{
			cout << "\n\n\t\t\tNo Clients Availabel In th System!\n";
		}
		else
		{
			for (clsLoginRegister &Register : vRegisters)
			{
				_PrintRecordRegisters(Register);

				cout << endl;
			}
			cout << "____________________________________________________________________________________________________________\n";

		}


		
	}

};

