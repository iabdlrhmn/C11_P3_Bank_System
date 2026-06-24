#pragma once
#include "clsBankClient.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintFail()
	{
		string RED = "\033[1;31m";
		string RESET = "\033[0m";
		cout << RED << "\n  Transfer Failed!\n" << RESET;
	}

    static float _ReadTransferAmount()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";

        float Amount = 0;
        cout << "Enter Transfer Amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        while (Amount <= 0)
        {
            cout << RED << "Amount must be greater than 0, Enter again: " << RESET;
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

    static bool _ConfirmTransfer(string AccountNumber, float Amount)
    {
        string YELLOW = "\033[1;33m";
        string RESET = "\033[0m";
        char   Confirm;

        cout << YELLOW
            << "\n  Transfer " << fixed << setprecision(2) << Amount
            << " from Account [" << AccountNumber << "]? (Y/N): "
            << RESET;
        cin >> Confirm;
        return (Confirm == 'Y' || Confirm == 'y');
    }

    static void _PrintBalance(clsBankClient Client)
    {
        cout << "\n******* Client Available Balance *******" << endl;
        cout << "Sender Name       : " << Client.GetFirstName() + " " + Client.GetLastName() << endl;
        cout << "Account Number  : " << Client.GetAccountNumber() << " | ";
        cout << "Available Balance : " << Client.GetAccountBalance() << endl;
        cout << "****************************************" << endl;
    }

    static void _PrintCancelled()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Deposit Cancelled.\n" << RESET;
    }

    static void _PrintSuccess(clsBankClient& Sender, clsBankClient& Receiver, float Amount)
    {
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";

        cout << GREEN << "\n  Transaction Success!\n" << RESET;
        cout << GREEN << Sender.AccountNumber <<"  New Balance: $" << fixed << setprecision(2)
            << Sender.GetAccountBalance() << "\n" << RESET;
        cout << GREEN << Receiver.AccountNumber << "  New Balance: $" << fixed << setprecision(2)
            << Receiver.GetAccountBalance() << "\n" << RESET;
    }

public:
	static void ShowTransferScreen()
	{
        _DrawScreenHeader("Bank System", "Transfer");

		string SenderAccountNumber = clsBankClient::_ReadExistingAccountNumber("Enter Sender's Account Number: ");
		clsBankClient Sender = clsBankClient::Find(SenderAccountNumber);
		if (Sender.IsEmpty()) {
			_PrintFail();
			return;
		}
        _PrintBalance(Sender);
		string ReceiverAccountNumber = clsBankClient::_ReadExistingAccountNumber("Enter Receiver's Account Number: ");
		clsBankClient Receiver = clsBankClient::Find(ReceiverAccountNumber);
		if (Receiver.IsEmpty()) {
			_PrintFail();
			return;
		}
        _PrintBalance(Receiver);

        float Amount = _ReadTransferAmount();
        if (!_ConfirmTransfer(SenderAccountNumber, Amount))
        {
            _PrintCancelled();
            return;
        }

        if (Sender.Transfer(Amount,Receiver))
            _PrintSuccess(Sender, Receiver, Amount);
        else
            _PrintFail();
	}

};
