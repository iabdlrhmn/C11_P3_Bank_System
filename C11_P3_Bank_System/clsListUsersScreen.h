#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include <sstream>

class clsListUsersScreen : protected clsScreen
{
private:

    // ── UI ───────────────────────────────────────────────────────

    static void _PrintTableRow(clsUser& User, int Counter, string MARGIN)
    {
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";

        cout << MARGIN
            << WALL << "| " << RESET
            << WHITE << setw(5) << Counter << RESET
            << WALL << "| " << RESET
            << WHITE << setw(18) << User.UserName << RESET
            << WALL << "| " << RESET
            << WHITE << setw(20) << User.GetFirstName() + " " + User.GetLastName() << RESET
            << WALL << "| " << RESET
            << WHITE << setw(24) << User.GetEmail() << RESET
            << WALL << "| " << RESET
            << WHITE << setw(15) << User.GetPhone() << RESET
            << WALL << "| " << RESET
            << GREEN << setw(10) << User.GetPermissions() << RESET
            << WALL << "|" << RESET << "\n";
    }

public:

    static void ShowListUsersScreen()
    {
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string CYAN = "\033[1;36m";
        string GRAY = "\033[90m";
        string RESET = "\033[0m";

        int    TABLE_WIDTH = 100;
        string MARGIN = string((CONSOLE_WIDTH - TABLE_WIDTH) / 2, ' ');
        string DIVIDER = GRAY + string(TABLE_WIDTH, '-') + RESET + "\n";

        vector<clsUser> vUsers = clsUser::GetUsersList();

        _DrawScreenHeader("Bank System", "Users List");

        // ── Sub Header ──
        string Title = "Users List (" + to_string(vUsers.size()) + ")";
        string Border = "==============================";
        int    TitlePad = (TABLE_WIDTH - (int)Title.length()) / 2;
        int    BorderPad = (TABLE_WIDTH - (int)Border.length()) / 2;

        cout << CYAN;
        cout << MARGIN << string(BorderPad, ' ') << Border << "\n";
        cout << MARGIN << string(TitlePad, ' ') << Title << "\n";
        cout << MARGIN << string(BorderPad, ' ') << Border << "\n";
        cout << RESET;

        // ── Column Headers ──
        cout << MARGIN << DIVIDER;
        cout << MARGIN
            << WALL << "| " << RESET << left
            << WHITE << setw(5) << "#" << RESET << WALL << "| " << RESET
            << WHITE << setw(18) << "Username" << RESET << WALL << "| " << RESET
            << WHITE << setw(20) << "Full Name" << RESET << WALL << "| " << RESET
            << WHITE << setw(24) << "Email" << RESET << WALL << "| " << RESET
            << WHITE << setw(15) << "Phone" << RESET << WALL << "| " << RESET
            << WHITE << setw(10) << "Permissions" << RESET << WALL << "|" << RESET << "\n";
        cout << MARGIN << DIVIDER;

        // ── Rows ──
        int Counter = 1;
        for (clsUser& User : vUsers)
            _PrintTableRow(User, Counter++, MARGIN);

        cout << MARGIN << DIVIDER;
    }
};