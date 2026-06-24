#pragma once
#include "clsScreen.h"
#include "clsUser.h"

class clsDeleteUserScreen : protected clsScreen
{
private:

    // ── Logic ────────────────────────────────────────────────────

    static string _ReadExistingUserName()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";

        string UserName = "";
        cout << "Enter Username: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::DoesUserExist(UserName))
        {
            cout << RED << "Username does not exist, Enter again: " << RESET;
            UserName = clsInputValidate::ReadString();
        }
        return UserName;
    }

    static bool _ConfirmDelete(string UserName)
    {
        string YELLOW = "\033[1;33m";
        string RESET = "\033[0m";
        char   Confirm;

        cout << YELLOW << "\n  Are you sure you want to delete [" << UserName << "]? (Y/N): " << RESET;
        cin >> Confirm;
        return (Confirm == 'Y' || Confirm == 'y');
    }

    // ── UI ───────────────────────────────────────────────────────

    static void _PrintSuccess()
    {
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";
        cout << GREEN << "\n  User Deleted Successfully!\n" << RESET;
    }

    static void _PrintFail()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Failed to Delete User!\n" << RESET;
    }

    static void _PrintCancelled()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Delete Cancelled.\n" << RESET;
    }

    static void _PrintUserCard(clsUser& User)
    {
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string CYAN = "\033[1;36m";
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

    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("Bank System", "Delete User");

        string   UserName = _ReadExistingUserName();
        clsUser  User = clsUser::Find(UserName);

        if (User.IsEmpty())
        {
            _PrintFail();
            return;
        }

        _PrintUserCard(User);

        if (!_ConfirmDelete(UserName))
        {
            _PrintCancelled();
            return;
        }

        if (User.Delete())
            _PrintSuccess();
        else
            _PrintFail();
    }
};