#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include <sstream>
using namespace std;

class clsClientListScreen : protected clsScreen
{
private:

    static void _PrintTableRow(clsBankClient& Client, int Counter)
    {
        string RESET = "\033[0m";
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string GREEN = "\033[1;32m";

        ostringstream oss;
        oss << fixed << setprecision(2) << Client.GetAccountBalance();
        string BalanceNum = oss.str();
        string BalanceVisible = "$" + BalanceNum;
        int    Padding = 12 - (int)BalanceVisible.length();

        cout << WALL << "| " << RESET
            << WHITE << setw(5) << Counter << RESET
            << WALL << "| " << RESET
            << WHITE << setw(18) << Client.GetAccountNumber() << RESET
            << WALL << "| " << RESET
            << WHITE << setw(20) << Client.GetFirstName() + " " + Client.GetLastName() << RESET
            << WALL << "| " << RESET
            << WHITE << setw(24) << Client.GetEmail() << RESET
            << WALL << "| " << RESET
            << WHITE << setw(15) << Client.GetPhone() << RESET
            << WALL << "| " << RESET
            << GREEN << "$" << RESET
            << WHITE << BalanceNum << RESET
            << string(max(0, Padding), ' ')
            << WALL << "|" << RESET << "\n";
    }

public:

    static void ShowClientsList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::enListClients))
            return;
        string RESET = "\033[0m";
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string GRAY = "\033[90m";

        int    TABLE_WIDTH = 106;
        string DIVIDER = GRAY + string(TABLE_WIDTH, '-') + RESET + "\n";

        vector<clsBankClient> vClients = clsBankClient::GetClientDataAsVector();

        _DrawScreenHeader("Bank System", "Clients List");
        

        // ── Column Headers ──
        cout << DIVIDER;
        cout << WALL << "| " << RESET << left
            << WHITE << setw(5) << "#" << RESET << WALL << "| " << RESET
            << WHITE << setw(18) << "Account No." << RESET << WALL << "| " << RESET
            << WHITE << setw(20) << "Full Name" << RESET << WALL << "| " << RESET
            << WHITE << setw(24) << "Email" << RESET << WALL << "| " << RESET
            << WHITE << setw(15) << "Phone" << RESET << WALL << "| " << RESET
            << WHITE << setw(12) << "Balance" << RESET << WALL << "|" << RESET << "\n";
        cout << DIVIDER;

        // ── Rows ──
        int Counter = 1;
        for (clsBankClient& Client : vClients)
            _PrintTableRow(Client, Counter++);

        cout << DIVIDER;
    }
};