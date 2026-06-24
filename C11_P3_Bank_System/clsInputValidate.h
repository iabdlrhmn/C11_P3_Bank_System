#pragma once
/**
 * @file clsInputValidate.h
 * @brief Input validation utility library for range checks and safe console input.
 *
 * Provides static methods for:
 *  - Validating that numbers or dates fall within a given range.
 *  - Safely reading integers and doubles from stdin, retrying on bad input.
 *  - Validating calendar dates via clsDate.
 *
 * Dependencies: clsString.h, clsDate.h
 */

#include <iostream>
#include <string>
#include "clsMyString.h"
#include "clsMyDateFunctions.h"

using namespace std;

class clsInputValidate
{
public:

    // -------------------------------------------------------------------------
    //  Range Checks
    // -------------------------------------------------------------------------

    /**
     * @brief Checks whether a short integer lies within [From, To] (inclusive).
     * @param Number  The value to test.
     * @param From    Lower bound (inclusive).
     * @param To      Upper bound (inclusive).
     * @return true if From <= Number <= To, false otherwise.
     */
    static bool IsNumberBetween(short Number, short From, short To)
    {
        return (Number >= From && Number <= To);
    }

    /**
     * @brief Checks whether an integer lies within [From, To] (inclusive).
     * @param Number  The value to test.
     * @param From    Lower bound (inclusive).
     * @param To      Upper bound (inclusive).
     * @return true if From <= Number <= To, false otherwise.
     */
    static bool IsNumberBetween(int Number, int From, int To)
    {
        return (Number >= From && Number <= To);
    }

    /**
     * @brief Checks whether a float lies within [From, To] (inclusive).
     * @param Number  The value to test.
     * @param From    Lower bound (inclusive).
     * @param To      Upper bound (inclusive).
     * @return true if From <= Number <= To, false otherwise.
     */
    static bool IsNumberBetween(float Number, float From, float To)
    {
        return (Number >= From && Number <= To);
    }

    /**
     * @brief Checks whether a double lies within [From, To] (inclusive).
     * @param Number  The value to test.
     * @param From    Lower bound (inclusive).
     * @param To      Upper bound (inclusive).
     * @return true if From <= Number <= To, false otherwise.
     */
    static bool IsNumberBetween(double Number, double From, double To)
    {
        return (Number >= From && Number <= To);
    }

    /**
     * @brief Checks whether a date falls between two boundary dates (inclusive).
     *
     * The check is order-independent: it accepts Date if it lies between
     * From and To regardless of which boundary is earlier on the calendar.
     *
     *   Valid if:  (Date >= From && Date <= To)
     *           OR (Date >= To   && Date <= From)
     *
     * @param Date  The date to test.
     * @param From  One boundary date (inclusive).
     * @param To    The other boundary date (inclusive).
     * @return true if Date is within the range, false otherwise.
     */
    static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
    {
        // Case 1: From <= Date <= To
        if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)) &&
            (clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)))
            return true;

        // Case 2: To <= Date <= From  (reversed range)
        if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)) &&
            (clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)))
            return true;

        return false;
    }

    // -------------------------------------------------------------------------
    //  Safe Console Input
    // -------------------------------------------------------------------------

    /**
     * @brief Reads a valid integer from stdin, retrying on non-integer input.
     *
     * Clears the error state and discards the bad input line before prompting
     * again, so the stream is always left in a usable state.
     *
     * @param ErrorMessage  Message printed when the input is not a valid integer.
     *                      Defaults to "Invalid Number, Enter again\n".
     * @return The first valid integer entered by the user.
     */
    static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        int Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    /**
     * @brief Reads an integer that is guaranteed to lie within [From, To].
     *
     * First reads a valid integer via ReadIntNumber(), then keeps prompting
     * until the value satisfies IsNumberBetween(Number, From, To).
     *
     * @param From          Lower bound (inclusive).
     * @param To            Upper bound (inclusive).
     * @param ErrorMessage  Message printed when the value is out of range.
     *                      Defaults to "Number is not within range, Enter again:\n".
     * @return The first valid in-range integer entered by the user.
     */
    static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        int Number = ReadIntNumber();
        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }
        return Number;
    }

    //---------------------------------
    static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        short Number = ReadIntNumber();
        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }
        return Number;
    }

    /**
     * @brief Reads a valid double from stdin, retrying on non-numeric input.
     *
     * Clears the error state and discards the bad input line before prompting
     * again, so the stream is always left in a usable state.
     *
     * @param ErrorMessage  Message printed when the input is not a valid double.
     *                      Defaults to "Invalid Number, Enter again\n".
     * @return The first valid double entered by the user.
     */
    static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        double Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    /**
     * @brief Reads a double that is guaranteed to lie within [From, To].
     *
     * First reads a valid double via ReadDblNumber(), then keeps prompting
     * until the value satisfies IsNumberBetween(Number, From, To).
     *
     * @param From          Lower bound (inclusive).
     * @param To            Upper bound (inclusive).
     * @param ErrorMessage  Message printed when the value is out of range.
     *                      Defaults to "Number is not within range, Enter again:\n".
     * @return The first valid in-range double entered by the user.
     */
    static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        double Number = ReadDblNumber();
        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }

    // -------------------------------------------------------------------------
    //  Date Validation
    // -------------------------------------------------------------------------

    /**
     * @brief Delegates to clsDate::IsValidDate() to verify a calendar date.
     *
     * A date is valid when the year is positive, the month is 1–12, and the
     * day is within the correct range for that month (accounting for leap years).
     *
     * @param Date  The clsDate object to validate.
     * @return true if the date is a real calendar date, false otherwise.
     */
    static bool IsValideDate(clsDate Date)
    {
        return clsDate::IsValidDate(Date);
    }
	// -------------------------------------------------------------------------
    // Read String
	// -------------------------------------------------------------------------
    /**
     * @brief Reads a line of text from stdin and returns it as a string.
     *
     * Uses std::getline to read an entire line, allowing for spaces in the input.
     *
     * @return The line of text entered by the user.
     */
    static string ReadString()
    {
        string Input;

        if (cin.peek() == '\n')
            cin.ignore();

        getline(cin, Input);
        return Input;
    }
	// -------------------------------------------------------------------------
	// Read Account Number
    // -------------------------------------------------------------------------
    /**
     * @brief Reads a bank account number from stdin, ensuring it is exactly 5 characters.
     *
     * Keeps prompting until the user enters a string of length 5, which is the
     * expected format for account numbers in this system.
     *
     * @param ErrorMessage  Message printed when the input is not 5 characters long.
     *                      Defaults to "Invalid Account Number, Enter again\n".
     * @return A valid account number string of length 5.
     */
    static string ReadAccountNumber(string ErrorMessage = "Invalid Account Number, Enter again\n")
    {
        if (cin.peek() == '\n') {
            cin.ignore();
        }
        string AccountNumber = ReadString();
        while (!IsNumberBetween(AccountNumber.length(), 4, 4))
        {
            cout << ErrorMessage;
            AccountNumber = ReadString();
        }
        return AccountNumber;
	}
};