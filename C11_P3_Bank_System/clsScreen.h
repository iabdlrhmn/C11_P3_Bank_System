#pragma once
#include <iostream>
#include "GlobalVar.h"
#include "clsMyDateFunctions.h"

using namespace std;

class clsScreen
{
protected:

    static const int CONSOLE_WIDTH = 120;

    static void _DrawUserInfoBar()
    {
        string RESET = "\033[0m";
        string GRAY = "\033[90m";
        string CYAN = "\033[1;36m";

        int    WIDTH = 60;
        string MARGIN = string((CONSOLE_WIDTH - WIDTH) / 2, ' ');

        string DateText = clsDate::DateToString(clsDate());

        string Info = "User: " + CurrentUser.UserName + "    |    Date: " + DateText;

        int Space = (WIDTH - (int)Info.length()) / 2;
        string Padding = (Space > 0) ? string(Space, ' ') : "";

        cout << MARGIN << Padding
            << GRAY << "User: " << RESET << CYAN << CurrentUser.UserName << RESET
            << GRAY << "    |    Date: " << RESET << CYAN << DateText << RESET
            << "\n\n";
    }

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        string RESET = "\033[0m";
        string HEADER = "\033[1;36m";
        string GRAY = "\033[90m";
        string WHITE = "\033[1;37m";

        int    CONSOLE = 120;
        int    WIDTH = 60;
        string MARGIN = string((CONSOLE - WIDTH) / 2, ' ');
        string BORDER = string(WIDTH, '=');

        auto GetPadding = [&](string Text)
            {
                int Space = (WIDTH - (int)Text.length()) / 2;
                return (Space > 0) ? string(Space, ' ') : "";
            };

        cout << MARGIN << GRAY << BORDER << RESET << "\n";
        cout << MARGIN << HEADER << GetPadding(Title) << Title << RESET << "\n";

        if (!SubTitle.empty())
            cout << MARGIN << WHITE << GetPadding(SubTitle) << SubTitle << RESET << "\n";

        cout << MARGIN << GRAY << BORDER << RESET << "\n";

        _DrawUserInfoBar();
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (CurrentUser.CheckAccessPermission(Permission))
            return true;

        string RESET = "\033[0m";
        string RED = "\033[1;31m";
        string WHITE = "\033[1;37m";

        int WIDTH = 40;
        int CONSOLE = 120;
        string MARGIN = string((CONSOLE - WIDTH) / 2, ' ');

        auto PrintLine = [&](string Text)
            {
                int Pad = WIDTH - 5 - (int)Text.length();
                cout << MARGIN << RED << "  |  " << RESET
                    << WHITE << Text << RESET
                    << string(max(0, Pad), ' ')
                    << RED << " |" << RESET << "\n";
            };

        cout << "\n";
        cout << MARGIN << RED << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        cout << MARGIN << RED << "  |" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
        PrintLine("X ACCESS DENIED");
        PrintLine("Contact your Admin.");
        cout << MARGIN << RED << "  |" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
        cout << MARGIN << RED << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        cout << "\n";

        return false;
    }
};