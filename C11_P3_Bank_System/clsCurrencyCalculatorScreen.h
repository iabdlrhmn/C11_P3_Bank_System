#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

    static float _ConvertCurrency(float Amount, clsCurrency From, clsCurrency To)
    {
        // كل الـ Rates بالنسبة لـ USD
        // خطوتين: Amount -> USD -> Target Currency
        float AmountInUSD = Amount / From.Rate();
        return AmountInUSD * To.Rate();
    }

    static void _PrintResultCard(clsCurrency From, clsCurrency To, float Amount, float Result)
    {
        string RESET = "\033[0m";
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string GREEN = "\033[1;32m";
        string GRAY = "\033[90m";

        int    WIDTH = 50;
        int    CONSOLE = 120;
        string MARGIN = string((CONSOLE - WIDTH) / 2, ' ');

        auto PrintField = [&](string Label, string Value, string ValueColor)
            {
                int Pad = WIDTH - 7
                    - (int)Label.length()
                    - (int)Value.length();

                cout << MARGIN
                    << WALL << "  |  " << RESET
                    << GRAY << Label << ": " << RESET
                    << ValueColor << Value << RESET
                    << string(max(0, Pad), ' ')
                    << WALL << "  |" << RESET << "\n";
            };

        auto PrintEmpty = [&]()
            {
                cout << MARGIN << WALL << "  |" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
            };

        auto PrintDivider = [&]()
            {
                cout << MARGIN << WALL << "  |" << string(WIDTH - 2, '-') << "|" << RESET << "\n";
            };

        cout << "\n";
        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        PrintEmpty();
        PrintField("From          ", From.CurrencyCode() + " - " + From.CurrencyName(), WHITE);
        PrintField("To            ", To.CurrencyCode() + " - " + To.CurrencyName(), WHITE);
        PrintDivider();
        PrintField("Amount        ", to_string(Amount).substr(0, to_string(Amount).find('.') + 3) + " " + From.CurrencyCode(), YELLOW);
        PrintField("Converted     ", to_string(Result).substr(0, to_string(Result).find('.') + 5) + " " + To.CurrencyCode(), GREEN);
        PrintField("Exchange Rate ", "1 " + From.CurrencyCode() + " = " + to_string(To.Rate() / From.Rate()).substr(0, 6) + " " + To.CurrencyCode(), GRAY);
        PrintEmpty();
        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        cout << "\n";
    }

    static clsCurrency _ReadCurrency(string Prompt)
    {
        string Code;
        clsCurrency Currency = clsCurrency::FindByCode("");

        do
        {
            cout << Prompt;
            cin >> Code;
            Currency = clsCurrency::FindByCode(Code);

            if (Currency.IsEmpty())
                cout << "\n\033[1;31m  X Currency Code Not Found, Try Again.\033[0m\n\n";

        } while (Currency.IsEmpty());

        return Currency;
    }

public:

    static void ShowCurrencyCalculatorScreen()
    {
        char Again = 'Y';

        while (Again == 'Y' || Again == 'y')
        {
            system("cls");
            _DrawScreenHeader("Bank System", "Currency Calculator");

            clsCurrency FromCurrency = _ReadCurrency("\n\033[1;37m  From Currency Code: \033[0m");
            clsCurrency ToCurrency = _ReadCurrency("\033[1;37m  To   Currency Code: \033[0m");

            cout << "\033[1;37m  Amount: \033[0m";
            float Amount = clsInputValidate::ReadDblNumber();

            float Result = _ConvertCurrency(Amount, FromCurrency, ToCurrency);

            _PrintResultCard(FromCurrency, ToCurrency, Amount, Result);

            cout << "\033[1;33m  Do you want to perform another conversion? (Y/N): \033[0m";
            cin >> Again;
        }
    }
};