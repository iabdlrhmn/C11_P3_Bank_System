#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:

    static void _PrintCurrencyCard(clsCurrency Currency)
    {
        string RESET = "\033[0m";
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string CYAN = "\033[1;36m";
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

        string RateStr = to_string(Currency.Rate()).substr(0, to_string(Currency.Rate()).find('.') + 5);

        cout << "\n";
        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        PrintEmpty();
        PrintField("Country     ", Currency.Country());
        PrintField("Code        ", Currency.CurrencyCode());
        PrintField("Currency    ", Currency.CurrencyName());
        PrintField("Rate (USD)  ", RateStr);
        PrintEmpty();
        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        cout << "\n";
    }

    static void _PrintNotFoundMessage()
    {
        cout << "\n\033[1;31m  X Currency Not Found.\033[0m\n\n";
    }

    enum enSearchOption { eByCode = 1, eByCountry = 2 };

    static enSearchOption _ReadSearchOption()
    {
        string CYAN = "\033[1;36m";
        string YELLOW = "\033[1;33m";
        string RESET = "\033[0m";

        cout << "\n"
            << CYAN << "  [" << RESET << YELLOW << "1" << RESET << CYAN << "]" << RESET << " Search by Currency Code\n"
            << CYAN << "  [" << RESET << YELLOW << "2" << RESET << CYAN << "]" << RESET << " Search by Country Name\n\n"
            << "\033[1;37m  Choose [1-2]: \033[0m";

        return (enSearchOption)clsInputValidate::ReadShortNumberBetween(1, 2, "Enter 1 or 2: ");
    }

public:

    static void ShowFindCurrencyScreen()
    {
        system("cls");
        _DrawScreenHeader("Bank System", "Find Currency");

        enSearchOption Option = _ReadSearchOption();

        string Input;
        clsCurrency Result = clsCurrency::_GetEmptyCurrencyObject();

        if (Option == eByCode)
        {
            cout << "\n\033[1;37m  Enter Currency Code (e.g. USD, EUR, EGP): \033[0m";
            cin >> Input;
            Result = clsCurrency::FindByCode(Input);
        }
        else
        {
            cout << "\n\033[1;37m  Enter Country Name (e.g. Egypt, France): \033[0m";
            cin.ignore();
            getline(cin, Input);
            Result = clsCurrency::FindByCountry(Input);
        }

        if (Result.IsEmpty())
            _PrintNotFoundMessage();
        else
            _PrintCurrencyCard(Result);
    }
};