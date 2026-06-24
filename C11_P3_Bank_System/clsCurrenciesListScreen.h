#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrencyListScreen : protected clsScreen
{
private:

    static void _PrintTableHeader()
    {
        string RESET = "\033[0m";
        string CYAN = "\033[1;36m";
        string GRAY = "\033[90m";

        cout << CYAN
            << left
            << setw(5) << "#"
            << setw(35) << "Country"
            << setw(10) << "Code"
            << setw(35) << "Currency Name"
            << setw(12) << "Rate (USD)"
            << RESET << "\n";

        cout << GRAY << string(95, '-') << RESET << "\n";
    }

    static void _PrintRecord(clsCurrency Currency, int Counter)
    {
        string RESET = "\033[0m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string CYAN = "\033[1;36m";
        string GRAY = "\033[90m";

        cout << GRAY << left << setw(5) << Counter
            << WHITE << setw(35) << Currency.Country()
            << CYAN << setw(10) << Currency.CurrencyCode()
            << WHITE << setw(35) << Currency.CurrencyName()
            << YELLOW << setw(12) << fixed << setprecision(4) << Currency.Rate()
            << RESET << "\n";
    }

public:

    static void ShowCurrencyListScreen()
    {
        system("cls");
        _DrawScreenHeader("Bank System", "Currencies List");

        vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

        if (vCurrencies.empty())
        {
            cout << "\n  \033[90mNo currency records found.\033[0m\n";
            return;
        }

        _PrintTableHeader();

        int Counter = 1;
        for (clsCurrency& Currency : vCurrencies)
            _PrintRecord(Currency, Counter++);

        string GRAY = "\033[90m";
        string RESET = "\033[0m";

        cout << GRAY << string(95, '-') << RESET << "\n";
        cout << "\033[1;37m  Total Currencies: \033[1;33m" << vCurrencies.size() << "\033[0m\n\n";
    }
};