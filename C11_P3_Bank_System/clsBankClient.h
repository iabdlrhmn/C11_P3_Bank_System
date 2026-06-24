#pragma once
#include "clsPerson.h"
#include "clsMyString.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "GlobalVar.h"

using namespace std;

/**
 * @file clsBankClient.h
 * @brief Defines the BankClient class
 *
 * Inherits from clsPerson and extends it with bank account data
 * (account number, pin code, balance).
 * Also handles loading and saving client data to a text file.
 */
class clsBankClient : public clsPerson
{

    // ============================================================
    // Private Section
    // ============================================================

private:

    /**
     * @enum enMode
     * @brief Represents the current state of the object
     */
    enum enMode
    {
        EmptyMode = 0, ///< Empty object (does not exist in the system)
        UpdateMode = 1, ///< Existing object, ready to be modified
        AddNewMode = 2  ///< New object, not yet saved
    };

    string _AccountNumber = "";  ///< Account number (immutable after construction)
    string _PinCode = "";  ///< Pin code
    float  _AccountBalance = 0.0; ///< Account balance
    enMode _Mode;                 ///< Current state of the object

    // ── Private Helpers ─────────────────────────────────────────

    /**
     * @brief Converts a text line from the file into a clsBankClient object
     * @param Line Text line in the format: F#//#L#//#E#//#P#//#Acc#//#Pin#//#Bal
     * @return clsBankClient object in UpdateMode
     */
    static clsBankClient _ConvertLineToClient(string Line)
    {
        vector<string> vData = clsMyString::Split(Line, "#//#");
        if (vData.size() < 7)
            return clsBankClient(enMode::EmptyMode);

        return clsBankClient(
            enMode::UpdateMode,
            vData[0], vData[1], vData[2], vData[3],
            vData[4], vData[5], stof(vData[6])
        );
    }

    /**
     * @brief Converts a clsBankClient object into a text line to be written to the file
     * @param Client The object to convert
     * @return string The resulting text line
     */
    static string _ConvertClientToLine(clsBankClient Client)
    {
        return Client.GetFirstName() + "#//#" +
            Client.GetLastName() + "#//#" +
            Client.GetEmail() + "#//#" +
            Client.GetPhone() + "#//#" +
            Client.GetAccountNumber() + "#//#" +
            Client.GetPinCode() + "#//#" +
            to_string(Client.GetAccountBalance());
    }

    /**
     * @brief Loads all clients from the text file
     * @return vector<clsBankClient> List of all clients
     */
    static vector<clsBankClient> _LoadClientsFromFile()
    {
        vector<clsBankClient> vClients;
        fstream inFile("ClientsData.txt");

        if (inFile.is_open())
        {
            string Line;
            while (getline(inFile, Line))
            {
                if (!Line.empty() && Line.back() == '\r')
                    Line.pop_back();

                if (!Line.empty())
                vClients.push_back(_ConvertLineToClient(Line));
            }
            inFile.close();
        }
        return vClients;
    }

    /**
     * @brief Writes all clients to the text file (overwrites existing content)
     * @param vClients List of clients to write
     */
    static void _WriteClientsToFile(vector<clsBankClient> vClients)
    {
        fstream outFile("ClientsData.txt", ios::out);
        if (outFile.is_open())
        {
            for (int i = 0; i < vClients.size(); i++)
            {
                // ✅ لو مش آخر عنصر، حط سطر جديد
                if (i < vClients.size() - 1)
                    outFile << _ConvertClientToLine(vClients[i]) << endl;
                else
                    outFile << _ConvertClientToLine(vClients[i]); // آخر سطر بدون \n
            }
            outFile.close();
        }
    }

    /**
     * @brief Updates the current client's data in the file
     * @details Loads all clients, finds the matching AccountNumber,
     *          replaces it with the current object, then writes back to file.
     */
    void _Update()
    {
        vector<clsBankClient> vClients = _LoadClientsFromFile();

        for (clsBankClient& Client : vClients)
        {
            if (Client.GetAccountNumber() == _AccountNumber)
            {
                Client = *this;
                break;
            }
        }
        _WriteClientsToFile(vClients);
    }

    void _AddNew()
    {
        vector<clsBankClient> vClients = _LoadClientsFromFile();

        vClients.push_back(*this);

        _WriteClientsToFile(vClients);
        _Mode = UpdateMode;
    }

    /**
     * @brief Reads client data from the console and updates the given object
     * @param Client The object to be updated with the new data
     */
    static void _ReadClientDataFromScreen(clsBankClient& Client)
    {
        cout << "Enter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "Enter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Enter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "Enter Phone Number: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Enter Pin Code: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Enter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();
    }


    // ============================================================
    // Public Section
    // ============================================================

public:

    // ── Enum ────────────────────────────────────────────────────

    /**
     * @enum enSaveResults
     * @brief Result of a save operation
     */
    enum enSaveResults
    {
        svFailed_emptyObject = 0, ///< Failed because the object is empty
        svSucceeded = 1  ///< Saved successfully
    };

    // ── Constructor ─────────────────────────────────────────────

    /**
     * @brief Main constructor with default values
     * @param Mode           Object state (defaults to EmptyMode)
     * @param FirstName      First name
     * @param LastName       Last name
     * @param Email          Email address
     * @param PhoneNumber    Phone number
     * @param AccountNumber  Account number
     * @param PinCode        Pin code
     * @param AccountBalance Account balance
     */
    clsBankClient(
        enMode Mode = EmptyMode,
        string FirstName = "",
        string LastName = "",
        string Email = "",
        string PhoneNumber = "",
        string AccountNumber = "",
        string PinCode = "",
        float  AccountBalance = 0.0
    ) : clsPerson(FirstName, LastName, Email, PhoneNumber),
        _AccountNumber(AccountNumber),
        _PinCode(PinCode),
        _AccountBalance(AccountBalance),
        _Mode(Mode) {}

    // ── Getters & Setters ────────────────────────────────────────

    /**
     * @brief Returns the account number
     * @note No setter — account number is immutable after construction
     */
    string GetAccountNumber() const { return _AccountNumber; }
    _declspec(property(get = GetAccountNumber)) string AccountNumber;

    /** @brief Returns the pin code */
    string GetPinCode() const { return _PinCode; }

    /** @brief Sets the pin code */
    void SetPinCode(string PinCode) { _PinCode = PinCode; }
    _declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    /** @brief Returns the account balance */
    float GetAccountBalance() const { return _AccountBalance; }

    /** @brief Sets the account balance */
    void SetAccountBalance(float AccountBalance) { _AccountBalance = AccountBalance; }
    _declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    /** @brief Returns the current mode */
    enMode GetMode() const { return _Mode; }

    // ── Queries ──────────────────────────────────────────────────

    /**
     * @brief Checks whether the object is empty (not found in the system)
     * @return true if Mode is EmptyMode
     */
    bool IsEmpty() const { return _Mode == EmptyMode; }

    /**
     * @brief Checks whether a client with the given account number exists
     * @param AccountNumber The account number to search for
     * @return true if found
     */
    static bool DoesClientExist(string AccountNumber)
    {
        return !Find(AccountNumber).IsEmpty();
    }

    /**
     * @brief Searches for a client by account number (loads from file internally)
     * @param AccountNumber The account number to search for
     * @return clsBankClient The found object, or EmptyMode if not found
     */
    static clsBankClient Find(string AccountNumber)
    {
        vector<clsBankClient> vClients = _LoadClientsFromFile();
        return Find(AccountNumber, vClients);
    }

    /**
     * @brief Searches for a client by account number and pin code (loads from file internally)
     * @param AccountNumber The account number to search for
     * @param PinCode       The pin code to match
     * @return clsBankClient The found object, or EmptyMode if not found
     */
    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        vector<clsBankClient> vClients = _LoadClientsFromFile();
        return Find(AccountNumber, PinCode, vClients);
    }

    /**
     * @brief Searches for a client by account number within a given list
     * @param AccountNumber The account number to search for
     * @param vClients      The list to search in
     * @return clsBankClient The found object, or EmptyMode if not found
     */
    static clsBankClient Find(string AccountNumber, const vector<clsBankClient>& vClients)
    {
        for (const clsBankClient& Client : vClients)
        {
            if (Client.AccountNumber == AccountNumber)
                return Client;
        }
        return clsBankClient(enMode::EmptyMode);
    }

    /**
     * @brief Searches for a client by account number and pin code within a given list
     * @param AccountNumber The account number to search for
     * @param PinCode       The pin code to match
     * @param vClients      The list to search in
     * @return clsBankClient The found object, or EmptyMode if not found
     */
    static clsBankClient Find(string AccountNumber, string PinCode, const vector<clsBankClient>& vClients)
    {
        for (const clsBankClient& Client : vClients)
        {
            if (Client.AccountNumber == AccountNumber &&
                Client.GetPinCode() == PinCode)
                return Client;
        }
        return clsBankClient(enMode::EmptyMode);
    }

    // ── Display ──────────────────────────────────────────────────

    /**
     * @brief Prints client information to the console
     */
    void PrintClientInfo()
    {
        cout << "********** Client Information **********" << endl;
        cout << "First Name      : " << GetFirstName() << endl;
        cout << "Last Name       : " << GetLastName() << endl;
        cout << "Full Name       : " << GetFirstName() + " " + GetLastName() << endl;
        cout << "Email           : " << GetEmail() << endl;
        cout << "Phone           : " << GetPhone() << endl;
        cout << "Account Number  : " << GetAccountNumber() << endl;
        cout << "Account Balance : " << GetAccountBalance() << endl;
        cout << "****************************************" << endl;
    }

    // ── Actions ──────────────────────────────────────────────────

    /**
     * @brief Saves the object (Update or AddNew) based on the current Mode
     * @return enSaveResults Result of the save operation
     */
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case EmptyMode:
            return svFailed_emptyObject;
        case UpdateMode:
            _Update();
            return svSucceeded;
        case AddNewMode:
            _AddNew();
			return svSucceeded;
        default:
            return svFailed_emptyObject;
        }
    }

    /**
     * @brief Prompts the user to update an existing client and saves the changes
     * @details Validates the account number, prints current info,
     *          reads new data from the console, then saves.
     */
    static void UpdateClientData()
    {
        string AccountNumber = "";

        cout << "Please Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadAccountNumber();

        while (!DoesClientExist(AccountNumber))
        {
            cout << "Account Number does not exist, Enter again: ";
            AccountNumber = clsInputValidate::ReadAccountNumber();
        }

        clsBankClient Client = Find(AccountNumber);
        Client.PrintClientInfo();

        cout << "*****************************************\n";
        cout << "******* Update Client Information *******\n";

        _ReadClientDataFromScreen(Client);
        Client.Save();
    }


    bool _DeleteClient()
    {
        vector<clsBankClient> vClients = _LoadClientsFromFile();
        vector<clsBankClient> vUpdated;

        for (clsBankClient &client : vClients)
        {
            if (client.GetAccountNumber() != _AccountNumber)
                vUpdated.push_back(client);
        }
        _WriteClientsToFile(vUpdated);
        *this = clsBankClient();
        return true;
    }
    
    // these is for other files to inherit
    static vector<clsBankClient> GetClientDataAsVector()
    {
        return _LoadClientsFromFile();
    }
    
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber);
    }


    static string _ReadExistingAccountNumber(string Message = "Enter Account Number: ")
    {
        string RED = "\033[1;31m";
        string RESET = "\033[0m";

        string AccountNumber = "";
        cout << Message;
        AccountNumber = clsInputValidate::ReadAccountNumber();

        while (!clsBankClient::DoesClientExist(AccountNumber))
        {
            cout << RED << "Account Number does not exist, Enter again: " << RESET;
            AccountNumber = clsInputValidate::ReadAccountNumber();
        }
        return AccountNumber;
    }
    static clsBankClient _ReadNewClientData(string AccountNumber)
    {
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        cout << "Enter First Name: ";
        NewClient.FirstName = clsInputValidate::ReadString();

        cout << "Enter Last Name: ";
        NewClient.LastName = clsInputValidate::ReadString();

        cout << "Enter Email: ";
        NewClient.Email = clsInputValidate::ReadString();

        cout << "Enter Phone Number: ";
        NewClient.Phone = clsInputValidate::ReadString();

        cout << "Enter Pin Code: ";
        NewClient.PinCode = clsInputValidate::ReadString();

        cout << "Enter Account Balance: ";
        NewClient.AccountBalance = clsInputValidate::ReadDblNumber();

        return NewClient;
    }

    /**
 * @brief Deposits an amount into the account and saves
 * @param Amount The amount to deposit
 * @return true if successful
 */
    bool Deposit(float Amount)
    {
        if (Amount <= 0)
            return false;

        _AccountBalance += Amount;
        return Save();
    }

    /**
     * @brief Withdraws an amount from the account and saves
     * @param Amount The amount to withdraw
     * @return true if successful
     */
    bool Withdraw(float Amount)
    {
        if (Amount <= 0)
            return false;

        if (Amount > _AccountBalance)
            return false;

        _AccountBalance -= Amount;
        return Save();
    }

    string _PrepareTransferLogRecord(float Amount, clsBankClient Receiver, string Username, string Separator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Separator
            + AccountNumber + Separator + Receiver.AccountNumber + Separator
            + to_string(Amount) + Separator + to_string(AccountBalance) + Separator
            + to_string(Receiver.AccountBalance) + Separator + Username;
        return TransferLogRecord;
    }

    void RegisterTransferLog(float Amount, clsBankClient Receiver, string Username)
    {
        string DataLine = _PrepareTransferLogRecord(Amount, Receiver, Username);

        fstream MyFile;
        MyFile.open("TransferLogs.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }

    bool Transfer(float Amount, clsBankClient& Receiver)
    {
        if (Amount > AccountBalance)
            return false;
        Withdraw(Amount);
        Receiver.Deposit(Amount);
        RegisterTransferLog(Amount, Receiver, CurrentUser.UserName);
        return Save();
    }
};