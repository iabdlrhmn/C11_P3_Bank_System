#pragma once
#include <iomanip>
#include "clsMainScreen.h"
#include "GlobalVar.h"
#include "clsRegisterLogin.h"

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		bool LoginFaild = false;
		string Username, Password;
		short FaildLogincounter = 0;
		do
		{
			if (LoginFaild) {
				FaildLogincounter++;
				cout << "\033[31m\nInvalid Username/Password, Please try again!\n\033[0m";
				cout << "You have " << 3 - FaildLogincounter << "attempts left.";
			}
			if (FaildLogincounter == 3)
			{
				cout << "your account is locked, please contact customer support\n";
				return false;
			}
			cout << "Enter Username: \n";
			cin >> Username;
			cout << "Enter Password: \n";
			cin >> Password;
			CurrentUser = clsUser::Find(Username, Password);
			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild);
		clsRegisterLogin::RegisterLogin();
		clsMainScreen::ShowMainMenu();
		return true;
	}
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Login Screen");
		return _Login();
	}
};
