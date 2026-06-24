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
 * Dependencies: clsMyString.h, clsMyDateFunctions.h
 */

#include <iostream>
#include <string>
#include <limits>
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
     * @brief Checks whether a numeric value lies within [From, To] (inclusive).
     *
     * Works with any numeric type (short, int, float, double, size_t...).
     *
     * @tparam T      Any comparable numeric type.
     * @param Number  The value to test.
     * @param From    Lower bound (inclusive).
     * @param To      Upper bound (inclusive).
     * @return true if From <= Number <= To, false otherwise.
     */
    template <typename T>
    static bool IsNumberBetween(T Number, T From, T To)
    {
        return (Number >= From && Number <= To);
    }

    /**
     * @brief Checks whether a date falls between two boundary dates (inclusive).
     *
     * Order-independent: accepts Date if it lies between From and To
     * regardless of which boundary is earlier on the calendar.
     *
     * @param Date  The date to test.
     * @param From  One boundary date (inclusive).
     * @param To    The other boundary date (inclusive).
     * @return true if Date is within the range, false otherwise.
     */
    static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
    {
        if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)) &&
            (clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)))
            return true;

        if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)) &&
            (clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)))
            return true;

        return false;
    }

    // -------------------------------------------------------------------------
    //  Safe Console Input
    // -------------------------------------------------------------------------

    /**
     * @brief Reads a value of type T from stdin, retrying on invalid input.
     *
     * Clears the error state and discards the bad input line before prompting
     * again, so the stream is always left in a usable state.
     *
     * @tparam T            Any type supported by cin >> (int, float, double, short...).
     * @param ErrorMessage  Message printed when input fails to parse.
     * @return The first successfully parsed value of type T.
     */
    template <typename T>
    static T ReadNumber(string ErrorMessage = "Invalid input, Enter again:\n")
    {
        T Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    /**
     * @brief Reads a value of type T guaranteed to lie within [From, To].
     *
     * Calls ReadNumber<T>() then keeps prompting until the value satisfies
     * IsNumberBetween(Number, From, To).
     *
     * @tparam T            Any comparable numeric type.
     * @param From          Lower bound (inclusive).
     * @param To            Upper bound (inclusive).
     * @param ErrorMessage  Message printed when the value is out of range.
     * @return The first valid in-range value of type T.
     *
     * @par Usage examples:
     * @code
     * int    x = clsInputValidate::ReadNumberBetween<int>(1, 10);
     * float  y = clsInputValidate::ReadNumberBetween<float>(0.0f, 1.0f);
     * short  z = clsInputValidate::ReadNumberBetween<short>(1, 5, "Pick 1-5: ");
     * @endcode
     */
    template <typename T>
    static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        T Number = ReadNumber<T>();
        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadNumber<T>();
        }
        return Number;
    }

    // -------------------------------------------------------------------------
    //  Backward-Compatible Aliases
    //  (عشان باقي الكود اللي بيستخدم الأسامي القديمة يفضل شغال من غير تعديل)
    // -------------------------------------------------------------------------

    static int    ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again:\n") { return ReadNumber<int>(ErrorMessage); }
    static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again:\n") { return ReadNumber<double>(ErrorMessage); }
    static float  ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again:\n") { return ReadNumber<float>(ErrorMessage); }

    static int    ReadIntNumberBetween(int    From, int    To, string ErrorMessage = "Number is not within range, Enter again:\n") { return ReadNumberBetween<int>(From, To, ErrorMessage); }
    static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n") { return ReadNumberBetween<double>(From, To, ErrorMessage); }
    static short  ReadShortNumberBetween(short  From, short  To, string ErrorMessage = "Number is not within range, Enter again:\n") { return ReadNumberBetween<short>(From, To, ErrorMessage); }

    // -------------------------------------------------------------------------
    //  Date Validation
    // -------------------------------------------------------------------------

    /**
     * @brief Delegates to clsDate::IsValidDate() to verify a calendar date.
     * @param Date  The clsDate object to validate.
     * @return true if the date is a real calendar date, false otherwise.
     */
    static bool IsValideDate(clsDate Date)
    {
        return clsDate::IsValidDate(Date);
    }

    // -------------------------------------------------------------------------
    //  String Input
    // -------------------------------------------------------------------------

    /**
     * @brief Reads a full line of text from stdin (supports spaces).
     * @return The line entered by the user.
     */
    static string ReadString()
    {
        string Input;
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, Input);
        return Input;
    }

    /**
     * @brief Reads a bank account number, ensuring it is exactly 4 characters.
     * @param ErrorMessage  Message printed on invalid input.
     * @return A valid account number string of length 4.
     */
    static string ReadAccountNumber(string ErrorMessage = "Invalid Account Number, Enter again:\n")
    {
        if (cin.peek() == '\n')
            cin.ignore();

        string AccountNumber = ReadString();
        while (!IsNumberBetween(AccountNumber.length(), (size_t)4, (size_t)4))
        {
            cout << ErrorMessage;
            AccountNumber = ReadString();
        }
        return AccountNumber;
    }
};