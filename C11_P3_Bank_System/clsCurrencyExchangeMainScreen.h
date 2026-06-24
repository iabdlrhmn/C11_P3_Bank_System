#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:

    enum enCurrenciesMainMenuOptions {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrencyRate = 3,
        eCurrencyCalculator = 4, eMainMenu = 5
    };

    static short _ReadCurrenciesMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose What You Want To Do: [1-5]\n";
        return clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number Between 1 and 5");
    }

    static void _GoBackToCurrenciesMenu()
    {
        cout << "\n\nPress any key to go back to Currencies Menu...";
        system("pause>0");
        ShowCurrenciesMainMenu();
    }
    static void _ShowCurrenciesListScreen()
    {
        clsCurrencyListScreen::ShowCurrencyListScreen();
    }
    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _ShowUpdateCurrencyRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }
    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrenciesMainMenuOptions(enCurrenciesMainMenuOptions Option)
    {
        switch (Option)
        {
        case eListCurrencies:
        {
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenu();
            break;
        }
        case eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenu();
            break;
        }
        case eUpdateCurrencyRate:
        {
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMenu();
            break;
        }
        case eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenu();
            break;
        }
        case eMainMenu:
            break;
        }
    }

public:

    static void ShowCurrenciesMainMenu()
    {
        system("cls");

        string RESET = "\033[0m";
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string CYAN = "\033[1;36m";

        int    WIDTH = 40;
        int    CONSOLE = 120;
        string MARGIN = string((CONSOLE - WIDTH) / 2, ' ');

        _DrawScreenHeader("Bank System", "Currency Exchange");

        auto PrintOption = [&](string Number, string Label)
            {
                int Pad = WIDTH - 10
                    - (int)Number.length()
                    - (int)Label.length();

                cout << MARGIN
                    << WALL << "  |  " << RESET
                    << CYAN << "[" << RESET
                    << YELLOW << Number << RESET
                    << CYAN << "]" << RESET
                    << WHITE << " >> " << Label << RESET
                    << string(max(0, Pad), ' ')
                    << WALL << "  |" << RESET << "\n";
            };

        auto PrintEmpty = [&]()
            {
                cout << MARGIN << WALL << "  |" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
            };

        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";
        PrintEmpty();
        PrintOption("1", "List Currencies");
        PrintOption("2", "Find Currency");
        PrintOption("3", "Update Rate");
        PrintOption("4", "Currency Calculator");
        PrintEmpty();
        PrintOption("5", "Main Menu");
        PrintEmpty();
        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";

        _PerformCurrenciesMainMenuOptions((enCurrenciesMainMenuOptions)_ReadCurrenciesMainMenuOption());
    }
};