#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsPerson.h"
#include <vector>
#include <fstream>
using namespace std;
class clsBankClient : public clsPerson
{

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1,AddNewMode=3 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line,string Saparator ="#//#") 
	{
		vector <string> vClientsObject = clsString::Split(Line,Saparator);

		return clsBankClient(enMode::UpdateMode, vClientsObject[0], vClientsObject[1], vClientsObject[2], vClientsObject[3], vClientsObject[4], vClientsObject[5],stof( vClientsObject[6]));
	}

	static vector <clsBankClient> _LoadClientsDateFromFile() 
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vClients.push_back(_ConvertLineToClientObject(Line));
			}

			MyFile.close();
		}

		return vClients;
	}

	static clsBankClient _GetEmptyClientObject() 
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertObjectClientToLine(clsBankClient Client, string Saparator ="#//#") 
	{
		string Line = "";

		Line += Client.FirstName + Saparator;
		Line += Client.LastName + Saparator;
		Line += Client.Email + Saparator;
		Line += Client.Phone + Saparator;
		Line += Client.AccountNumber()+ Saparator;
		Line += Client.PinCode + Saparator;
		Line += to_string(Client.AccountBalance);

		return Line;
	}

	static void _SaveClientsDateToFile(vector <clsBankClient> vClients)
	{
		fstream MyFile;

		MyFile.open("Clients.txt",ios::out);
		
		if (MyFile.is_open())
		{
			for (clsBankClient &Client : vClients)
			{
				if (Client._MarkForDelete == false)
				{
					MyFile << _ConvertObjectClientToLine(Client) << endl;
				}
				
			}

			MyFile.close();
		}

	}

	static void _AddNewLineToFile(string Line) 
	{
		fstream MyFile;
		
		MyFile.open("Clients.txt",ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;

			MyFile.close();
		}
	}



	void _Update() 
	{
		vector <clsBankClient> vClients = _LoadClientsDateFromFile();

		for (clsBankClient &Client : vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client = *this;
				break;
			}
		}

		_SaveClientsDateToFile(vClients);
	}
	
	void _AddNew() 
	{
		_AddNewLineToFile(_ConvertObjectClientToLine(*this));
	}


public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string Pincode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone) 
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = Pincode;
		_AccountBalance = AccountBalance;

	}
	
	bool IsEmpty() 
	{
		return 	_Mode == enMode::EmptyMode;
	}

	string AccountNumber() 
	{
	
		return _AccountNumber;
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

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	
	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}
	
	

	bool Delete() 
	{
		vector <clsBankClient> vClients = _LoadClientsDateFromFile();

		for (clsBankClient & Client : vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDateToFile(vClients);

		*this = GetEmptyClientObject();

		return true;
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save() 
	{
		switch (_Mode)
		{
			case enMode::EmptyMode:
			{
				return svFaildEmptyObject;
			}
			case enMode::UpdateMode:
			{
				_Update();

				return enSaveResults::svSucceeded;
			}
			case enMode::AddNewMode:
			{
				if (IsClientExsit(AccountNumber()))
				{
					return enSaveResults::svFaildAccountNumberExists;
				}
				else
				{
					_AddNew();
					_Mode = enMode::UpdateMode;

					return enSaveResults::svSucceeded;
				}
			}
		}
	}

	static clsBankClient Find(string AccountNumber ) 
	{
		fstream MyFile;

		MyFile.open("Clients.txt",ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();

					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();

	}

	static clsBankClient Find(string AccountNumber,string PinCode)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode ==  PinCode)
				{
					MyFile.close();

					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();

	}

	static bool IsClientExsit(string AccountNumber) 
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return !Client.IsEmpty();
	}

	static clsBankClient GetAddNewObject(string AccountNumber) 
	{
		return clsBankClient(enMode::AddNewMode,"","","","",AccountNumber,"",0);
	}

	static clsBankClient GetEmptyClientObject() 
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> GetClientsList() 
	{
		return _LoadClientsDateFromFile();
	}

	static double GetTotalBalance() 
	{
		vector <clsBankClient> vClients = _LoadClientsDateFromFile();

		double TotalBalance = 0;

		for (clsBankClient &Client : vClients)
		{
			TotalBalance += Client.AccountBalance;
		}

		return TotalBalance;
	}

	 void Deposit(float Amount) 
	{
		AccountBalance += Amount;

		Save();
	}

	 bool Withdraw(float Amount)
	 {
		 if (AccountBalance < Amount)
		 {
			 return false;
		 }
		 else
		 {
			 AccountBalance -= Amount;

			 Save();

			 return true;
		 }

	 }

};

