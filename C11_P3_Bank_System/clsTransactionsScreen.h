#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsGetTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionsMenuOptions {
		enDeposit = 1, enWithdraw = 2, enShowTotalBalances = 3, enTransfer = 4, enTransferLog = 5, enShowMainMenu = 6
	};
	static short _ReadTransactionsMenuOption() {
		cout << setw(37) << left << "" << "Chose what do you want to perform: \n";
		short choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Invalid input, Please try again.\n");
		return choice;
	}
    // sub menus from transactions menu

    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }
    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _ShowTotalBalancesScreen()
    {
        clsGetTotalBalancesScreen::ShowTotalBalancesScreen();
    }
    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransactionLogScreen();
    }
    static void _GoBackToTransactionsScreen()
    {
        system("pause");
        system("cls");
        clsTransactionsScreen::ShowTransactionsMenu();
    }

    static void _PerformTransactionsMenuOption(enTransactionsMenuOptions Choice)
    {
        switch (Choice)
        {
        case enDeposit: {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsScreen();
            break;
        }
        case enWithdraw: {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsScreen();
            break;
        }
        case enShowTotalBalances: {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsScreen();
            break;
        }
        case enTransfer: {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsScreen();
            break;
        }
        case enTransferLog: {
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsScreen();
            system("pause");
            break;
        }
        case enShowMainMenu: {
           
        }
        }
    }


public:
    static void ShowTransactionsMenu()
    {

        if (!CheckAccessRights(clsUser::enPermissions::enTransactions))
            return;
        string RESET = "\033[0m";
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string GRAY = "\033[90m";
        string CYAN = "\033[1;36m";

        int    WIDTH = 40;
        string MARGIN = string((CONSOLE_WIDTH - WIDTH) / 2, ' ');

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

        _DrawScreenHeader("Bank System", "Transactions");

        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";

        PrintEmpty();
        PrintOption("1", "Deposit");
        PrintOption("2", "Withdraw");
        PrintOption("3", "Total Balances");
        PrintOption("4", "Transfer");
        PrintEmpty();
        cout << MARGIN << GRAY << "  |" << string(WIDTH - 2, '-') << "|" << RESET << "\n";
        PrintEmpty();
        PrintOption("5", "Tranfer Log");
        PrintOption("6", "Back to Main Menu");
        PrintEmpty();

        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";

        enTransactionsMenuOptions Choice = enTransactionsMenuOptions(_ReadTransactionsMenuOption());
        _PerformTransactionsMenuOption(Choice);
    }
};
