#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "GlobalVar.h"

using namespace std;

class clsRegisterLogin
{
private:
	static string _GetSystemDateTime()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;
		return (to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
	}
	static string _PrepareLogInRecord(string Separator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += _GetSystemDateTime() + Separator + CurrentUser.UserName + Separator + to_string(CurrentUser.Permissions);
		return LoginRecord;
	}

public:
	static void RegisterLogin()
	{
		string stDataLine = _PrepareLogInRecord(); // date and time strings

		fstream MyFile;
		MyFile.open("Logs.txt", ios::out | ios::app);

		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}
};
