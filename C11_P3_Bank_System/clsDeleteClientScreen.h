#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:

    static void _PrintDeletedMessage()
    {
        cout << "\n\033[1;32m  ✔ Client Deleted Successfully.\033[0m\n";
    }

    static void _PrintCancelledMessage()
    {
        cout << "\n\033[90m  Deletion Cancelled.\033[0m\n";
    }

    static void _PrintNotFoundMessage()
    {
        cout << "\n\033[1;31m  ✖ Account Number does not exist, Enter again.\033[0m\n";
    }

public:

    static void DeleteClientUI()
    {
        system("cls");
        _DrawScreenHeader("Bank System", "Delete Client");

        if (!CheckAccessRights(clsUser::enPermissions::enDeleteClient))
            return;

        string AccountNumber = "";

        cout << "\n\033[1;37m  Enter Account Number: \033[0m";
        AccountNumber = clsInputValidate::ReadAccountNumber();

        while (!clsBankClient::DoesClientExist(AccountNumber))
        {
            _PrintNotFoundMessage();
            cout << "\n\033[1;37m  Enter Account Number: \033[0m";
            AccountNumber = clsInputValidate::ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        cout << "\n";
        Client.PrintClientInfo();

        cout << "\n\033[1;33m  Are you sure you want to delete this client? (Y/N): \033[0m";
        char Confirm;
        cin >> Confirm;

        if (Confirm == 'Y' || Confirm == 'y')
        {
            if (Client._DeleteClient())
                _PrintDeletedMessage();
        }
        else
        {
            _PrintCancelledMessage();
        }

        cout << "\n";
    }
};