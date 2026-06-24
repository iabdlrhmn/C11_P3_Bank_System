#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsWithdrawScreen : protected clsScreen
{
private:

    // ── Logic ────────────────────────────────────────────────────

    static float _ReadWithdrawAmount(float CurrentBalance)
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";

        float Amount = 0;
        cout << "Enter Withdraw Amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        while (Amount <= 0 || Amount > CurrentBalance)
        {
            if (Amount <= 0)
                cout << RED << "Amount must be greater than 0, Enter again: " << RESET;
            else
                cout << RED << "Insufficient Balance! Max: $"
                << fixed << setprecision(2) << CurrentBalance
                << ", Enter again: " << RESET;

            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

    static bool _ConfirmWithdraw(string AccountNumber, float Amount)
    {
        string YELLOW = "\033[1;33m";
        string RESET = "\033[0m";
        char   Confirm;

        cout << YELLOW
            << "\n  Withdraw " << fixed << setprecision(2) << Amount
            << " from Account [" << AccountNumber << "]? (Y/N): "
            << RESET;
        cin >> Confirm;
        return (Confirm == 'Y' || Confirm == 'y');
    }

    // ── UI ───────────────────────────────────────────────────────

    static void _PrintSuccess(clsBankClient& Client, float Amount)
    {
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";

        cout << GREEN << "\n  Withdraw Successful!\n" << RESET;
        cout << GREEN << "  Withdrawn: $"
            << fixed << setprecision(2) << Amount << "\n" << RESET;
        cout << GREEN << "  New Balance: $"
            << fixed << setprecision(2) << Client.GetAccountBalance() << "\n" << RESET;
        Client.PrintClientInfo();
    }

    static void _PrintFail()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Withdraw Failed!\n" << RESET;
    }

    static void _PrintCancelled()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Withdraw Cancelled.\n" << RESET;
    }

public:

    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("Bank System", "Withdraw");

        string AccountNumber = clsBankClient::_ReadExistingAccountNumber();
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (Client.IsEmpty())
        {
            _PrintFail();
            return;
        }

        Client.PrintClientInfo();

        float Amount = _ReadWithdrawAmount(Client.GetAccountBalance());

        if (!_ConfirmWithdraw(AccountNumber, Amount))
        {
            _PrintCancelled();
            return;
        }

        if (Client.Withdraw(Amount))
            _PrintSuccess(Client, Amount);
        else
            _PrintFail();
    }
};