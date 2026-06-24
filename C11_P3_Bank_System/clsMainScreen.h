#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "GlobalVar.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"


using namespace std;

class clsMainScreen : protected clsScreen
{
private: 
    enum enMainMenuOptions {
    enListClients = 1, enAddNewClient = 2, 
    enDeleteClient = 3, enUpdateClient = 4, 
    enFindClient = 5, enShowTransactionsMenu = 6, 
    enManageUsers = 7, enLoginRegister = 8,enCurrencyExchange = 9, enExit = 10
    };

    static short _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Hi, Chose What You Want to Do: [1-10]\n";
        short choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter a Number Between 1 and 9");
        return choice;
    }
    static void _GoBackToMainMenu()
    {
        system("cls");
        clsMainScreen::ShowMainMenu();
    }
    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();
    }
    static void _ShowAddNewClientScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }
    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::DeleteClientUI();
    }
    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }
    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }
    static void _ShowTransactionMenuScreen()
    {
        clsTransactionsScreen::ShowTransactionsMenu();
    }
    static void _ShowManageUsersScreen()
    {
        clsManageUsersScreen::ShowManageUsersMenu();
    }
    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }
    static void _ShowCurrencyExchangeMainScreen()
    {
        clsCurrencyExchangeMainScreen::ShowCurrenciesMainMenu();
    }
    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerformMainMenuOptions(enMainMenuOptions enMainMenu)//switch options in main menu
    {
        switch (enMainMenu)
        {
        case enListClients:
            {
                system("cls");
                _ShowAllClientsScreen();
                system("pause");
                _GoBackToMainMenu();
                break;
            }
        case enAddNewClient:
            {
                system("cls");
                _ShowAddNewClientScreen();
                system("pause");
                _GoBackToMainMenu();
                break;
            }
        case enDeleteClient:
            {
                system("cls");
                _ShowDeleteClientScreen();
                system("pause");
                _GoBackToMainMenu();
                break;
            }
        case enUpdateClient:
            {
                system("cls");
                _ShowUpdateClientScreen();
                system("pause");
                _GoBackToMainMenu();
                break;
            }
        case enFindClient:
            {
                system("cls");
                _ShowFindClientScreen();
                system("pause");
                _GoBackToMainMenu();
                break;
            }
        case enShowTransactionsMenu:
            {
                system("cls");
                _ShowTransactionMenuScreen();
                _GoBackToMainMenu();
                break;
            }
        case enManageUsers:
            {
                system("cls");
                _ShowManageUsersScreen();
                _GoBackToMainMenu();
                break;
            }
        case enLoginRegister:
        {
            system("cls");
            _ShowLoginRegisterScreen();
            system("pause");
            _GoBackToMainMenu();
            break;
        }
        case enCurrencyExchange:
        {
            system("cls");
            _ShowCurrencyExchangeMainScreen();
            system("pause");
            _GoBackToMainMenu();
            break;
        }
        case enExit:
            {
                system("cls");
                _Logout();
                break;
            }
        } 
    }


public:
    static void ShowMainMenu()
    {
        system("cls");
        string RESET = "\033[0m";
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string GRAY = "\033[90m";
        string CYAN = "\033[1;36m";

        int    WIDTH = 40;
        int    CONSOLE = 120;
        string MARGIN = string((CONSOLE - WIDTH) / 2, ' ');
        string DIVIDER = GRAY + string(WIDTH, '-') + RESET + "\n";

        _DrawScreenHeader("Bank System", "Main Menu");

        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";

        auto PrintOption = [&](string Number, string Icon, string Label)
            {
                int Pad = WIDTH - 10
                    - (int)Number.length()
                    - (int)Icon.length()
                    - (int)Label.length();

                cout << MARGIN
                    << WALL << "  |  " << RESET
                    << CYAN << "[" << RESET
                    << YELLOW << Number << RESET
                    << CYAN << "]" << RESET
                    << WHITE << " " << Icon << " " << Label << RESET
                    << string(max(0, Pad), ' ')
                    << WALL << "  |" << RESET << "\n";
            };

        auto PrintEmpty = [&]()
            {
                cout << MARGIN << WALL << "  |" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
            };

        PrintEmpty();
        PrintOption("1", ">>", "Show Clients");
        PrintOption("2", ">>", "Add Client");
        PrintOption("3", ">>", "Delete Client");
        PrintOption("4", ">>", "Update Client");
        PrintOption("5", ">>", "Find Client");
        PrintEmpty();
        PrintOption("6", ">>", "Transactions");
        PrintOption("7", ">>", "Manage Users");
        PrintEmpty();
        PrintOption("8", ">>", "Login Register");
        PrintOption("9", ">>", "Currency Exchange");
        PrintOption("10", ">>", "Logout");
        PrintEmpty();

        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";

        enMainMenuOptions enMainMenu = enExit;
        enMainMenu = enMainMenuOptions(clsMainScreen::_ReadMainMenuOption());
        clsMainScreen::_PerformMainMenuOptions(enMainMenu);
    }


};

