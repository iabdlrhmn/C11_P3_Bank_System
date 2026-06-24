#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsUpdateClientScreen : protected clsScreen
{
private:

    static void _UpdateClientData(clsBankClient& Client)
    {
        cout << "Enter First Name   : ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "Enter Last Name    : ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Enter Email        : ";
        Client.Email = clsInputValidate::ReadString();

        cout << "Enter Phone Number : ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Enter Pin Code     : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Enter Balance      : ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();
    }

    static bool _ConfirmUpdate()
    {
        string YELLOW = "\033[1;33m";
        string RESET = "\033[0m";
        char   Confirm;

        cout << YELLOW << "\n  Are you sure you want to update this client? (Y/N): " << RESET;
        cin >> Confirm;
        return (Confirm == 'Y' || Confirm == 'y');
    }

    // ── UI ───────────────────────────────────────────────────────

    static void _PrintUpdateHeader()
    {
        string CYAN = "\033[1;36m";
        string RESET = "\033[0m";
        int    WIDTH = 45;
        string MARGIN = string((CONSOLE_WIDTH - WIDTH) / 2, ' ');

        cout << "\n"
            << MARGIN << CYAN << "  *****************************************" << RESET << "\n"
            << MARGIN << CYAN << "  ******* Update Client Information *******" << RESET << "\n"
            << MARGIN << CYAN << "  *****************************************" << RESET << "\n\n";
    }

    static void _PrintSuccess(clsBankClient& Client)
    {
        string GREEN = "\033[1;32m";
        string RESET = "\033[0m";
        cout << GREEN << "\n  Client Updated Successfully!\n" << RESET;
        Client.PrintClientInfo();
    }

    static void _PrintFail()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Failed to Update Client!\n" << RESET;
    }

    static void _PrintCancelled()
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";
        cout << RED << "\n  Update Cancelled.\n" << RESET;
    }

public:

    static void ShowUpdateClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::enUpdateClient))
            return;
        _DrawScreenHeader("Bank System", "Update Client");

        string AccountNumber = clsBankClient::_ReadExistingAccountNumber();
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (Client.IsEmpty())
        {
            _PrintFail();
            return;
        }

        Client.PrintClientInfo();

        if (!_ConfirmUpdate())
        {
            _PrintCancelled();
            return;
        }

        _PrintUpdateHeader();
        _UpdateClientData(Client);

        if (Client.Save() == clsBankClient::enSaveResults::svSucceeded)
            _PrintSuccess(Client);
        else
            _PrintFail();
    }
};