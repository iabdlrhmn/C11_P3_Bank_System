#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsAddNewClientScreen : protected clsScreen
{
private:

public:

    static void ShowAddNewClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::enAddNewClient))
            return;
        string GREEN = "\033[1;32m";
        string RED = "\033[1;31m";
        string RESET = "\033[0m";

        _DrawScreenHeader("Bank System", "Add New Client");

        string AccountNumber = "";
        cout << "Enter Account Number: \n";
        AccountNumber = clsInputValidate::ReadAccountNumber("\033[1;31mThe Account Number length must be 4\033[0m");

        while (clsBankClient::DoesClientExist(AccountNumber))
        {
            cout << RED << "Account Number already exists, Enter again: " << RESET;
            AccountNumber = clsInputValidate::ReadAccountNumber();
        }

        clsBankClient NewClient = clsBankClient::_ReadNewClientData(AccountNumber);

        if (NewClient.Save() == clsBankClient::enSaveResults::svSucceeded)
        {
            cout << GREEN << "\nClient Added Successfully!\n" << RESET;
            NewClient.PrintClientInfo();
        }
        else
        {
            cout << RED << "\nFailed to Add Client!\n" << RESET;
        }
    }
};