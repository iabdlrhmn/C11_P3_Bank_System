#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsDepositScreen : protected clsScreen
{
private:

    // ── Logic ────────────────────────────────────────────────────

    static float _ReadDepositAmount()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";

        float Amount = 0;
        cout << "Enter Deposit Amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        while (Amount <= 0)
        {
            cout << RED << "Amount must be greater than 0, Enter again: " << RESET;
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

    static bool _ConfirmDeposit(string AccountNumber, float Amount)
    {
        string YELLOW = "\033[1;33m";
        string RESET = "\033[0m";
        char   Confirm;

        cout << YELLOW
            << "\n  Deposit " << Amount << " to Account [" << AccountNumber << "]? (Y/N): "
            << RESET;
        cin >> Confirm;
        return (Confirm == 'Y' || Confirm == 'y');
    }

    // ── UI ───────────────────────────────────────────────────────

    static void _PrintSuccess(clsBankClient& Client, float Amount)
    {
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";

        cout << GREEN << "\n  Deposit Successful!\n" << RESET;
        cout << GREEN << "  New Balance: $" << fixed << setprecision(2)
            << Client.GetAccountBalance() << "\n" << RESET;
        Client.PrintClientInfo();
    }

    static void _PrintFail()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Deposit Failed!\n" << RESET;
    }

    static void _PrintCancelled()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Deposit Cancelled.\n" << RESET;
    }

public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("Bank System", "Deposit");

        string AccountNumber = clsBankClient::_ReadExistingAccountNumber();
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (Client.IsEmpty())
        {
            _PrintFail();
            return;
        }

        Client.PrintClientInfo();

        float Amount = _ReadDepositAmount();

        if (!_ConfirmDeposit(AccountNumber, Amount))
        {
            _PrintCancelled();
            return;
        }

        Client.Deposit(Amount);

        if (Client.Save())
            _PrintSuccess(Client, Amount);
        else
            _PrintFail();
    }
};