#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsMyString.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:

    struct stLoginRegisterRecord
    {
        string DateTime;
        string Username;
        int    Permission;
    };

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line)
    {
        stLoginRegisterRecord Record;

        vector<string> DataLine = clsMyString::Split(Line, "#//#");

        if (DataLine.size() < 3)
            return Record;

        Record.DateTime = DataLine[0];
        Record.Username = DataLine[1];
        Record.Permission = stoi(DataLine[2]);

        return Record;
    }

    static vector<stLoginRegisterRecord> _GetLoginRegisterList()
    {
        vector<stLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("Logs.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                if (!Line.empty())
                    vLoginRegisterRecord.push_back(_ConvertLoginRegisterLineToRecord(Line));
            }
            MyFile.close();
        }

        return vLoginRegisterRecord;
    }

    static void _PrintTableHeader()
    {
        string RESET = "\033[0m";
        string CYAN = "\033[1;36m";
        string GRAY = "\033[90m";

        cout << CYAN
            << left
            << setw(25) << "Date & Time"
            << setw(20) << "Username"
            << setw(15) << "Permissions"
            << RESET << "\n";

        cout << GRAY << string(55, '-') << RESET << "\n";
    }

    static void _PrintRecord(stLoginRegisterRecord Record)
    {
        string RESET = "\033[0m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";

        cout << WHITE
            << left
            << setw(25) << Record.DateTime
            << setw(20) << Record.Username
            << RESET
            << YELLOW << setw(15) << Record.Permission
            << RESET << "\n";
    }

public:

    static void ShowLoginRegisterScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::enLoginRegister))
            return;
        system("cls");
        _DrawScreenHeader("Bank System", "Login Records");

        vector<stLoginRegisterRecord> vRecords = _GetLoginRegisterList();

        if (vRecords.empty())
        {
            cout << "\n  No login records found.\n";
            return;
        }

        _PrintTableHeader();

        for (stLoginRegisterRecord& Record : vRecords)
            _PrintRecord(Record);

        cout << "\n";
        string GRAY = "\033[90m";
        string RESET = "\033[0m";
        cout << GRAY << string(55, '-') << RESET << "\n";
        cout << "\033[1;37m  Total Records: \033[1;33m" << vRecords.size() << "\033[0m\n\n";
    }
};