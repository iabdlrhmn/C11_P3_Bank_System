#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen
{
private:

    // ── Logic ────────────────────────────────────────────────────

    static string _ReadUniqueUserName()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";

        string UserName = "";
        cout << "Enter Username: ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::DoesUserExist(UserName))
        {
            cout << RED << "Username already exists, Enter again: " << RESET;
            UserName = clsInputValidate::ReadString();
        }
        return UserName;
    }

    static int _ReadPermissions()
    {
        string CYAN = "\033[1;36m";
        string YELLOW = "\033[1;33m";
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";

        char Choice;

        cout << CYAN << "\n  Grant All Permissions? (Y/N): " << RESET;
        cin >> Choice;
        if (Choice == 'Y' || Choice == 'y')
            return clsUser::enPermissions::enAllPermissions;

        cout << YELLOW << "\n  Select Permissions:\n" << RESET;

        auto AskPermission = [&](string Label) -> bool
            {
                char C;
                cout << "  " << left << setw(20) << Label << " (Y/N): ";
                cin >> C;
                return (C == 'Y' || C == 'y');
            };

        int Permissions = 0;

        if (AskPermission("List Clients"))   Permissions += clsUser::enPermissions::enListClients;
        if (AskPermission("Add New Client")) Permissions += clsUser::enPermissions::enAddNewClient;
        if (AskPermission("Delete Client"))  Permissions += clsUser::enPermissions::enDeleteClient;
        if (AskPermission("Update Client"))  Permissions += clsUser::enPermissions::enUpdateClient;
        if (AskPermission("Find Client"))    Permissions += clsUser::enPermissions::enFindClient;
        if (AskPermission("Transactions"))   Permissions += clsUser::enPermissions::enTransactions;
        if (AskPermission("Manage Users"))   Permissions += clsUser::enPermissions::enManageUsers;
        if (AskPermission("Access Login Register")) Permissions += clsUser::enPermissions::enLoginRegister;

        cout << GREEN << "\n  Total Permissions: " << Permissions << RESET << "\n";

        return Permissions;
    }

    static clsUser _ReadNewUserData(string UserName)
    {
        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        cout << "Enter First Name   : ";
        NewUser.FirstName = clsInputValidate::ReadString();

        cout << "Enter Last Name    : ";
        NewUser.LastName = clsInputValidate::ReadString();

        cout << "Enter Email        : ";
        NewUser.Email = clsInputValidate::ReadString();

        cout << "Enter Phone Number : ";
        NewUser.Phone = clsInputValidate::ReadString();

        cout << "Enter Password     : ";
        NewUser.Password = clsInputValidate::ReadString();

        NewUser.Permissions = _ReadPermissions();

        return NewUser;
    }

    // ── UI ───────────────────────────────────────────────────────

    static void _PrintSuccess(clsUser& User)
    {
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";
        cout << GREEN << "\n  User Added Successfully!\n" << RESET;
        _PrintUserCard(User);
    }

    static void _PrintFail()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Failed to Add User!\n" << RESET;
    }

    static void _PrintUserCard(clsUser& User)
    {
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string CYAN = "\033[1;36m";
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";

        int    WIDTH = 45;
        string MARGIN = string((CONSOLE_WIDTH - WIDTH) / 2, ' ');
        string BORDER = WALL + MARGIN + "+" + string(WIDTH - 2, '-') + "+" + RESET + "\n";

        auto PrintRow = [&](string Label, string Value)
            {
                int Pad = WIDTH - 4 - (int)Label.length() - (int)Value.length();
                cout << WALL << MARGIN << "|  " << RESET
                    << CYAN << Label << RESET
                    << WHITE << Value << RESET
                    << string(max(0, Pad), ' ')
                    << WALL << "  |" << RESET << "\n";
            };

        cout << BORDER;
        cout << WALL << MARGIN << "|" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
        PrintRow("Username    : ", User.UserName);
        PrintRow("First Name  : ", User.GetFirstName());
        PrintRow("Last Name   : ", User.GetLastName());
        PrintRow("Email       : ", User.GetEmail());
        PrintRow("Phone       : ", User.GetPhone());
        PrintRow("Permissions : ", to_string(User.Permissions));
        cout << WALL << MARGIN << "|" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
        cout << BORDER;
    }

public:

    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("Bank System", "Add New User");

        string   UserName = _ReadUniqueUserName();
        clsUser  NewUser = _ReadNewUserData(UserName);

        switch (NewUser.Save())
        {
        case clsUser::enSaveResults::svSucceeded:
            _PrintSuccess(NewUser);
            break;
        case clsUser::enSaveResults::svFailed_userExists:
            cout << "\033[1;31m\n  Username already exists!\n\033[0m";
            break;
        case clsUser::enSaveResults::svFailed_emptyObject:
            _PrintFail();
            break;
        }
    }
};