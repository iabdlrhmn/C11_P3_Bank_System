#pragma once
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsMainScreen;
class clsManageUsersScreen : protected clsScreen
{
private:

    enum enManageUsersMenuOptions
    {
        enListUsers = 1,
        enAddNewUser = 2,
        enDeleteUser = 3,
        enUpdateUser = 4,
        enFindUser = 5,
        enMainMenu = 6
    };

    // ── Logic ────────────────────────────────────────────────────

    static short _ReadMenuOption()
    {
        return clsInputValidate::ReadShortNumberBetween(1, 6, "Invalid input, Enter again [1-6]: ");
    }

    static void _ShowListUsers() {
        clsListUsersScreen::ShowListUsersScreen();
    }
	static void _ShowAddNewUser() {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
	static void _ShowDeleteUser() {
        clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	static void _ShowUpdateUser() {
        clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	static void _ShowFindUser() {
        clsFindUserScreen::ShowFindUserScreen();
	}
	static void _GoBackToUserMenu()
	{
		system("pause");
		system("cls");
		ShowManageUsersMenu();
	}

    static void _PerformMenuOption(enManageUsersMenuOptions Choice)
    {
        switch (Choice)
        {
        case enListUsers:
            system("cls");
			_ShowListUsers();
            _GoBackToUserMenu();
            break;

        case enAddNewUser:
            system("cls");
			_ShowAddNewUser();			
            _GoBackToUserMenu();
            break;

        case enDeleteUser:
            system("cls");
			_ShowDeleteUser();
            _GoBackToUserMenu();
            break;

        case enUpdateUser:
            system("cls");
			_ShowUpdateUser();
            _GoBackToUserMenu();
            break;

        case enFindUser:
            system("cls");
			_ShowFindUser();
            _GoBackToUserMenu();
            break;

        case enMainMenu:
        {}

        }
    }

    // ── UI ───────────────────────────────────────────────────────

    static void _PrintMenuOption(string Number, string Label, string MARGIN, int WIDTH)
    {
        string WALL = "\033[1;34m";
        string WHITE = "\033[1;37m";
        string YELLOW = "\033[1;33m";
        string CYAN = "\033[1;36m";
        string RESET = "\033[0m";

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
    }

public:

    static void ShowManageUsersMenu()
    {

        if (!CheckAccessRights(clsUser::enPermissions::enManageUsers))
            return;
        string WALL = "\033[1;34m";
        string GRAY = "\033[90m";
        string RESET = "\033[0m";

        int    WIDTH = 40;
        string MARGIN = string((CONSOLE_WIDTH - WIDTH) / 2, ' ');

        auto PrintEmpty = [&]()
            {
                cout << MARGIN << WALL << "  |" << string(WIDTH - 2, ' ') << "|" << RESET << "\n";
            };

        _DrawScreenHeader("Bank System", "Manage Users");

        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";

        PrintEmpty();
        _PrintMenuOption("1", "List Users", MARGIN, WIDTH);
        _PrintMenuOption("2", "Add New User", MARGIN, WIDTH);
        _PrintMenuOption("3", "Delete User", MARGIN, WIDTH);
        _PrintMenuOption("4", "Update User", MARGIN, WIDTH);
        _PrintMenuOption("5", "Find User", MARGIN, WIDTH);
        PrintEmpty();
        cout << MARGIN << GRAY << "  |" << string(WIDTH - 2, '-') << "|" << RESET << "\n";
        PrintEmpty();
        _PrintMenuOption("6", "Back to Main Menu", MARGIN, WIDTH);
        PrintEmpty();

        cout << MARGIN << WALL << "  +" << string(WIDTH - 2, '-') << "+" << RESET << "\n";

        enManageUsersMenuOptions Choice = enManageUsersMenuOptions(_ReadMenuOption());
        _PerformMenuOption(Choice);
    }
};