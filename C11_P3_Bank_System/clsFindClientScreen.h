#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsFindClientScreen : protected clsScreen
{
private:
    // ── UI ───────────────────────────────────────────────────────

    static void _PrintClientCard(clsBankClient& Client)
    {
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string GREEN = "\033[1;32m";
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

        PrintRow("First Name      : ", Client.GetFirstName());
        PrintRow("Last Name       : ", Client.GetLastName());
        PrintRow("Full Name       : ", Client.GetFirstName() + " " + Client.GetLastName());
        PrintRow("Email           : ", Client.GetEmail());
        PrintRow("Phone           : ", Client.GetPhone());
        PrintRow("Account Number  : ", Client.GetAccountNumber());

        // Balance بـ $ خضرا
        ostringstream oss;
        oss << fixed << setprecision(2) << Client.GetAccountBalance();
        int BalPad = WIDTH - 4 - (int)string("Balance         : ").length() - 1 - (int)oss.str().length();
        cout << WALL << MARGIN << "|  " << RESET
            << CYAN << "Balance         : " << RESET
            << GREEN << "$" << RESET
            << WHITE << oss.str() << RESET
            << string(max(0, BalPad), ' ')
            << WALL << "  |" << RESET << "\n";

        cout << WALL << MARGIN << "|" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
        cout << BORDER;
    }

    static void _PrintNotFound()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Client Not Found!\n" << RESET;
    }

public:

    static void ShowFindClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::enFindClient))
            return;
        _DrawScreenHeader("Bank System", "Find Client");

        string AccountNumber = clsBankClient::_ReadExistingAccountNumber();
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (Client.IsEmpty())
        {
            _PrintNotFound();
            return;
        }

        _PrintClientCard(Client);
    }
};