// ConsoleApplication40.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsManageUsers.h"
#include "clsLoginScreen.h"
#include "Golbal.h"
#include "clsLoginRegister.h"
using namespace std;






int main()
{

	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}

	}
	


    return 0;
}

