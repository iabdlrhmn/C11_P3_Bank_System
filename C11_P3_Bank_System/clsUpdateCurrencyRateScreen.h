#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

    static void _PrintCurrencyCard(clsCurrency Currency)
    {
        string RESET = "\033[0m";
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string GRAY = "\033[90m";

        int    WIDTH = 44;
        int    CONSOLE = 120;
        string MARGIN = string((CONSOLE - WIDTH) / 2, ' ');

        auto PrintField = [&](string Label, string Value)
            {
                int Pad = WIDTH - 7
                    - (int)Label.length()
                    - (int)Value.length();

                cout << MARGIN
                    << WALL << "  |  " << RESET
                    << GRAY << Label << ": " << RESET
                    << WHITE << Value << RESET
                    << string(max(0, Pad), ' ')
                    << WALL << "  |" << RESET << "\n";
            };

        auto PrintEmpty = [&]()
            {
                cout << MARGIN << WALL << "  |" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
            };

        cout << "\n";
        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        PrintEmpty();
        PrintField("Country     ", Currency.Country());
        PrintField("Code        ", Currency.CurrencyCode());
        PrintField("Currency    ", Currency.CurrencyName());
        PrintField("Current Rate", to_string(Currency.Rate()).substr(0, 6));
        PrintEmpty();
        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        cout << "\n";
    }

    static void _PrintUpdatedMessage(clsCurrency Currency)
    {
        string RESET = "\033[0m";
        string WALL = "\033[1;32m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string GRAY = "\033[90m";

        int    WIDTH = 44;
        int    CONSOLE = 120;
        string MARGIN = string((CONSOLE - WIDTH) / 2, ' ');

        auto PrintField = [&](string Label, string Value)
            {
                int Pad = WIDTH - 7
                    - (int)Label.length()
                    - (int)Value.length();

                cout << MARGIN
                    << WALL << "  |  " << RESET
                    << GRAY << Label << ": " << RESET
                    << WHITE << Value << RESET
                    << string(max(0, Pad), ' ')
                    << WALL << "  |" << RESET << "\n";
            };

        auto PrintEmpty = [&]()
            {
                cout << MARGIN << WALL << "  |" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
            };

        cout << "\n";
        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        PrintEmpty();
        PrintField("  ✔ Updated  ", Currency.CurrencyCode());
        PrintField("New Rate    ", to_string(Currency.Rate()).substr(0, 6));
        PrintEmpty();
        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        cout << "\n";
    }

public:

    static void ShowUpdateCurrencyRateScreen()
    {
        system("cls");
        _DrawScreenHeader("Bank System", "Update Currency Rate");

        cout << "\n\033[1;37m  Enter Currency Code (e.g. USD, EUR, EGP): \033[0m";
        string Code;
        cin >> Code;

        clsCurrency Currency = clsCurrency::FindByCode(Code);

        if (Currency.IsEmpty())
        {
            cout << "\n\033[1;31m  X Currency Not Found.\033[0m\n\n";
            return;
        }

        _PrintCurrencyCard(Currency);

        cout << "\033[1;37m  Enter New Rate: \033[0m";
        float NewRate = clsInputValidate::ReadDblNumber();

        cout << "\n\033[1;33m  Are you sure you want to update the rate? (Y/N): \033[0m";
        char Confirm;
        cin >> Confirm;

        if (Confirm == 'Y' || Confirm == 'y')
        {
            Currency.UpdateRate(NewRate);
            _PrintUpdatedMessage(Currency);
        }
        else
        {
            cout << "\n\033[90m  Update Cancelled.\033[0m\n\n";
        }
    }
};