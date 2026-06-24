#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsMyString.h"
#include "clsUtil.h"

using namespace std;

/**
 * @file clsUser.h
 * @brief Defines the User class for system access management
 *
 * Inherits from clsPerson and extends it with user credentials
 * (username, password, permissions).
 * Handles loading and saving user data to a text file.
 */
class clsUser : public clsPerson
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

    string _UserName = ""; ///< Username (unique identifier)
    string _Password = ""; ///< Password
    int    _Permissions = 0;  ///< Permissions bitmask
    enMode _Mode;             ///< Current state of the object
    bool   _MarkedForDelete = false; ///< Soft delete flag

    // ── Private Helpers ─────────────────────────────────────────

    /**
     * @brief Converts a text line from the file into a clsUser object
     * @param Line      Text line in the format: F#//#L#//#E#//#P#//#U#//#Pass#//#Perms
     * @param Separator Delimiter used in the file (default: #//#)
     * @return clsUser object in UpdateMode
     */
    static clsUser _ConvertLineToUser(string Line, string Separator = "#//#")
    {
        vector<string> vData = clsMyString::Split(Line, Separator);

        if (vData.size() < 7)
            return _GetEmptyUserObject();

        return clsUser(
            enMode::UpdateMode,
            vData[0], vData[1], vData[2], vData[3],
            vData[4], clsUtil::DecryptText(vData[5]), stoi(vData[6])
        );
    }

    /**
     * @brief Converts a clsUser object into a text line to be written to the file
     * @param User      The object to convert
     * @param Separator Delimiter used in the file (default: #//#)
     * @return string The resulting text line
     */
    static string _ConvertUserToLine(clsUser User, string Separator = "#//#")
    {
        return User.FirstName + Separator +
            User.LastName + Separator +
            User.Email + Separator +
            User.Phone + Separator +
            User.UserName + Separator +
            clsUtil::EncryptText(User.Password) + Separator +
            to_string(User.Permissions);
    }

    /**
     * @brief Loads all users from the text file
     * @return vector<clsUser> List of all users
     */
    static vector<clsUser> _LoadUsersFromFile()
    {
        vector<clsUser> vUsers;
        fstream inFile("Users.txt", ios::in);

        if (inFile.is_open())
        {
            string Line;
            while (getline(inFile, Line))
            {
                if (!Line.empty() && Line.back() == '\r')
                    Line.pop_back();

                if (!Line.empty())
                {
                    clsUser User = _ConvertLineToUser(Line);
                    if (!User.IsEmpty())
                        vUsers.push_back(User);
                }
            }
            inFile.close();
        }
        return vUsers;
    }

    /**
     * @brief Writes all users to the text file (skips soft-deleted records)
     * @param vUsers List of users to write
     */
    static void _WriteUsersToFile(vector<clsUser> vUsers)
    {
        fstream outFile("Users.txt", ios::out);

        if (outFile.is_open())
        {
            for (clsUser& User : vUsers)
            {
                if (!User.MarkedForDelete())
                    outFile << _ConvertUserToLine(User) << endl;
            }
            outFile.close();
        }
    }

    /**
     * @brief Updates the current user's data in the file
     * @details Loads all users, finds the matching username,
     *          replaces it with the current object, then writes back to file.
     */
    void _Update()
    {
        vector<clsUser> vUsers = _LoadUsersFromFile();

        for (clsUser& User : vUsers)
        {
            if (User.UserName == _UserName)
            {
                User = *this;
                break;
            }
        }
        _WriteUsersToFile(vUsers);
    }

    /**
     * @brief Adds the current user to the file
     * @details After saving, switches the mode to UpdateMode
     */
    void _AddNew()
    {
        vector<clsUser> vUsers = _LoadUsersFromFile();
        vUsers.push_back(*this);
        _WriteUsersToFile(vUsers);
        _Mode = enMode::UpdateMode;
    }

    /**
     * @brief Returns an empty user object in EmptyMode
     */
    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
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
        svFailed_userExists = 2, ///< Failed because the username already exists
        svSucceeded = 1  ///< Saved successfully
    };
	/** @enum enPermissions
    * @brief Permissions bitmask values
	*/
    enum enPermissions {
		enAllPermissions = -1, // كل البتات = 1 (كل الصلاحيات لليوزر) ظ
        enListClients = 1,     // 0000 0001
        enAddNewClient = 2,    // 0000 0010
        enDeleteClient = 4,    // 0000 0100
        enUpdateClient = 8,    // 0000 1000
        enFindClient = 16,     // 0001 0000
        enTransactions = 32,   // 0010 0000
        enManageUsers = 64,    // 0100 0000
        enLoginRegister = 128  // 1000 0000
    };
    // ── Constructor ─────────────────────────────────────────────

    /**
     * @brief Main constructor
     * @param Mode        Object state
     * @param FirstName   First name
     * @param LastName    Last name
     * @param Email       Email address
     * @param Phone       Phone number
     * @param UserName    Username (unique)
     * @param Password    Password
     * @param Permissions Permissions bitmask
     */
    clsUser(
        enMode Mode,
        string FirstName,
        string LastName,
        string Email,
        string Phone,
        string UserName,
        string Password,
        int    Permissions
    ) : clsPerson(FirstName, LastName, Email, Phone),
        _Mode(Mode),
        _UserName(UserName),
        _Password(Password),
        _Permissions(Permissions) {}

    // ── Getters & Setters ────────────────────────────────────────

    /** @brief Returns the username */
    string GetUserName() const { return _UserName; }

    /** @brief Sets the username */
    void SetUserName(string UserName) { _UserName = UserName; }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    /** @brief Returns the password */
    string GetPassword() const { return _Password; }

    /** @brief Sets the password */
    void SetPassword(string Password) { _Password = Password; }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    /** @brief Returns the permissions bitmask */
    int GetPermissions() const { return _Permissions; }

    /** @brief Sets the permissions bitmask */
    void SetPermissions(int Permissions) { _Permissions = Permissions; }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    // ── Queries ──────────────────────────────────────────────────

    /**
     * @brief Checks whether the object is empty (not found in the system)
     * @return true if Mode is EmptyMode
     */
    bool IsEmpty() const { return _Mode == enMode::EmptyMode; }

    /**
     * @brief Checks whether the user is marked for deletion
     * @return true if marked for delete
     */
    bool MarkedForDelete() const { return _MarkedForDelete; }

    /**
     * @brief Checks whether a user with the given username exists
     * @param UserName The username to search for
     * @return true if found
     */
    static bool DoesUserExist(string UserName)
    {
        return !Find(UserName).IsEmpty();
    }

    /**
     * @brief Searches for a user by username (loads from file internally)
     * @param UserName The username to search for
     * @return clsUser The found object, or EmptyMode if not found
     */
    static clsUser Find(string UserName)
    {
        fstream inFile("Users.txt", ios::in);

        if (inFile.is_open())
        {
            string Line;
            while (getline(inFile, Line))
            {
                if (!Line.empty() && Line.back() == '\r')
                    Line.pop_back();

                clsUser User = _ConvertLineToUser(Line);
                if (User.UserName == UserName)
                {
                    inFile.close();
                    return User;
                }
            }
            inFile.close();
        }
        return _GetEmptyUserObject();
    }

    /**
     * @brief Searches for a user by username and password (loads from file internally)
     * @param UserName The username to search for
     * @param Password The password to match
     * @return clsUser The found object, or EmptyMode if not found
     */
    static clsUser Find(string UserName, string Password)
    {
        fstream inFile("Users.txt", ios::in);

        if (inFile.is_open())
        {
            string Line;
            while (getline(inFile, Line))
            {
                if (!Line.empty() && Line.back() == '\r')
                    Line.pop_back();

                clsUser User = _ConvertLineToUser(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    inFile.close();
                    return User;
                }
            }
            inFile.close();
        }
        return _GetEmptyUserObject();
    }

    /**
     * @brief Returns a new user object ready for insertion (AddNewMode)
     * @param UserName The username for the new user
     * @return clsUser object in AddNewMode
     */
    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    /**
     * @brief Returns all users as a vector
     * @return vector<clsUser> List of all users
     */
    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersFromFile();
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
        case enMode::EmptyMode:
            return enSaveResults::svFailed_emptyObject;

        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSucceeded;

        case enMode::AddNewMode:
            if (DoesUserExist(_UserName))
                return enSaveResults::svFailed_userExists;
            _AddNew();
            return enSaveResults::svSucceeded;

        default:
            return enSaveResults::svFailed_emptyObject;
        }
    }

    /**
     * @brief Soft-deletes the user (marks for deletion and saves)
     * @details The record is kept in file until next write, then removed.
     * The current object is reset to EmptyMode after deletion.
     * @return true always
     */
    bool Delete()
    {
        vector<clsUser> vUsers = _LoadUsersFromFile();

        for (clsUser& User : vUsers)
        {
            if (User.UserName == _UserName)
            {
                User._MarkedForDelete = true;
                break;
            }
        }

        _WriteUsersToFile(vUsers);
        *this = _GetEmptyUserObject();
        return true;
    }

    /**
     * @brief Checks whether the user has a specific permission.
     *
     * Uses Bitwise AND to check if the requested bit(s) are set in
     * this->Permissions (a bit is set only if present in both values).
     * If this->Permissions is enAllPermissions (-1), all bits are 1,
     * so the check always returns true.
     *
     * @param Permission The permission to check for.
     * @return true if the user has the permission, false otherwise.
     */
    bool CheckAccessPermission(enPermissions Permission)
    {
        return (this->Permissions & Permission) == Permission;
    }
};