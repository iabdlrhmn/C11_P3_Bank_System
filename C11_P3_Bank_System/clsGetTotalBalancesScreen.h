#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsGetTotalBalancesScreen : protected clsScreen
{
private:

    // ── Logic ────────────────────────────────────────────────────

    static float _CalculateTotal(vector<clsBankClient>& vClients)
    {
        float Total = 0.0;
        for (clsBankClient& Client : vClients)
            Total += Client.GetAccountBalance();
        return Total;
    }

    // ── UI ───────────────────────────────────────────────────────

    static void _PrintTableRow(clsBankClient& Client, string MARGIN)
    {
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";

        ostringstream oss;
        oss << fixed << setprecision(2) << Client.GetAccountBalance();
        string BalanceNum = oss.str();
        string BalanceVisible = "$" + BalanceNum;
        int    Padding = 18 - (int)BalanceVisible.length();

        cout << MARGIN
            << WALL << "| " << RESET
            << WHITE << setw(16) << Client.GetAccountNumber() << RESET
            << WALL << "| " << RESET
            << GREEN << "$" << RESET
            << WHITE << BalanceNum << RESET
            << string(max(0, Padding), ' ')
            << WALL << "|" << RESET << "\n";
    }

    static void _PrintTotalRow(float Total, string MARGIN, string DIVIDER)
    {
        string WALL = "\033[1;34m";
        string YELLOW = "\033[1;33m";
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";

        ostringstream oss;
        oss << fixed << setprecision(2) << Total;
        string TotalStr = oss.str();
        string TotalVisible = "$" + TotalStr;
        int    TotalPadding = 18 - (int)TotalVisible.length();

        cout << MARGIN << DIVIDER;
        cout << MARGIN
            << WALL << "| " << RESET
            << YELLOW << setw(16) << "Total" << RESET
            << WALL << "| " << RESET
            << GREEN << "$" << RESET
            << YELLOW << TotalStr << RESET
            << string(max(0, TotalPadding), ' ')
            << WALL << "|" << RESET << "\n";

        cout << YELLOW << MARGIN << "  "
            << clsUtil::_FloatToWords(Total) << RESET << "\n";

        cout << MARGIN << DIVIDER;
    }

public:

    static void ShowTotalBalancesScreen()
    {
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string GRAY = "\033[90m";
        string RESET = "\033[0m";

        int    TABLE_WIDTH = 40;
        string MARGIN = string((CONSOLE_WIDTH - TABLE_WIDTH) / 2, ' ');
        string DIVIDER = GRAY + string(TABLE_WIDTH, '-') + RESET + "\n";

        vector<clsBankClient> vClients = clsBankClient::GetClientDataAsVector();
        float Total = _CalculateTotal(vClients);

        _DrawScreenHeader("Bank System", "Total Balances");

        // ── Column Headers ──
        cout << MARGIN << DIVIDER;
        cout << MARGIN
            << WALL << "| " << RESET << left
            << WHITE << setw(16) << "Account No." << RESET
            << WALL << "| " << RESET
            << WHITE << setw(18) << "Balance" << RESET
            << WALL << "|" << RESET << "\n";
        cout << MARGIN << DIVIDER;

        // ── Rows ──
        for (clsBankClient& Client : vClients)
            _PrintTableRow(Client, MARGIN);

        // ── Total ──
        _PrintTotalRow(Total, MARGIN, DIVIDER);
    }
};