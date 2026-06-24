#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "clsMyDateFunctions.h"

// Forward declaration for clsDate used in Swap
class clsDate;

using namespace std;
/**
 * @class clsUtil
 * @brief A utility class containing static methods for random generation, array manipulation, and cryptography.
 */
class clsUtil
{
public:

    /**
     * @enum enCharType
     * @brief Defines the types of characters that can be generated.
     */
    enum enCharType {
        SamallLetter = 1,     ///< Lowercase letters (a-z)
        CapitalLetter = 2,    ///< Uppercase letters (A-Z)
        Digit = 3,            ///< Numeric digits (0-9)
        MixChars = 4,         ///< Mixture of lowercase, uppercase, and digits
        SpecialCharacter = 5  ///< Special characters (e.g., !, @, #, etc.)
    };

    /**
     * @brief Seeds the random number generator.
     * @note This should be called only once in the entire application, typically at the start of main().
     */
    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    /**
     * @brief Generates a random integer within a specified range.
     * @param From The minimum value (inclusive).
     * @param To The maximum value (inclusive).
     * @return A random integer between From and To.
     */
    static int RandomNumber(int From, int To)
    {
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    /**
     * @brief Generates a single random character based on the specified type.
     * @param CharType The type of character to generate (from enCharType).
     * @return A random character of the requested type.
     */
    static char GetRandomCharacter(enCharType CharType)
    {
        if (CharType == MixChars)
        {
            // Capital / Small / Digits only
            CharType = (enCharType)RandomNumber(1, 3);
        }

        switch (CharType)
        {
        case enCharType::SamallLetter:
            return char(RandomNumber(97, 122));
            break;
        case enCharType::CapitalLetter:
            return char(RandomNumber(65, 90));
            break;
        case enCharType::SpecialCharacter:
            return char(RandomNumber(33, 47));
            break;
        case enCharType::Digit:
            return char(RandomNumber(48, 57));
            break;
        default:
            return char(RandomNumber(65, 90));
            break;
        }
    }

    /**
     * @brief Generates a random string (word) of a specified length.
     * @param CharType The type of characters to use in the word.
     * @param Length The number of characters the word should contain.
     * @return A string containing the generated word.
     */
    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word;
        for (int i = 1; i <= Length; i++)
        {
            Word = Word + GetRandomCharacter(CharType);
        }
        return Word;
    }

    /**
     * @brief Generates a formatted license/product key (e.g., XXXX-XXXX-XXXX-XXXX).
     * @param CharType The type of characters to use (defaults to CapitalLetter).
     * @return A formatted key string.
     */
    static string GenerateKey(enCharType CharType = CapitalLetter)
    {
        string Key = "";
        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);
        return Key;
    }

    /**
     * @brief Generates and prints a specified number of formatted keys to the console.
     * @param NumberOfKeys The amount of keys to generate.
     * @param CharType The type of characters to use for the keys.
     */
    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {
        for (int i = 1; i <= NumberOfKeys; i++)
        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }

    /**
     * @brief Fills a static integer array with random numbers.
     * @param arr The integer array to fill.
     * @param arrLength The length of the array.
     * @param From The minimum random value.
     * @param To The maximum random value.
     */
    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(From, To);
    }

    /**
     * @brief Fills a static string array with randomly generated words.
     * @param arr The string array to fill.
     * @param arrLength The length of the array.
     * @param CharType The character type to use for the words.
     * @param Wordlength The length of each generated word.
     */
    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateWord(CharType, Wordlength);
    }

    /**
     * @brief Fills a static string array with randomly generated formatted keys.
     * @param arr The string array to fill.
     * @param arrLength The length of the array.
     * @param CharType The character type to use for the keys.
     */
    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateKey(CharType);
    }

    /**
     * @brief Swaps the values of two integers.
     * @param A Reference to the first integer.
     * @param B Reference to the second integer.
     */
    static void Swap(int& A, int& B)
    {
        int Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swaps the values of two double-precision floating point numbers.
     * @param A Reference to the first double.
     * @param B Reference to the second double.
     */
    static void Swap(double& A, double& B)
    {
        double Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swaps the values of two booleans.
     * @param A Reference to the first boolean.
     * @param B Reference to the second boolean.
     */
    static void Swap(bool& A, bool& B)
    {
        bool Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swaps the values of two characters.
     * @param A Reference to the first character.
     * @param B Reference to the second character.
     */
    static void Swap(char& A, char& B)
    {
        char Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swaps the values of two strings.
     * @param A Reference to the first string.
     * @param B Reference to the second string.
     */
    static void Swap(string& A, string& B)
    {
        string Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    /**
     * @brief Swaps two custom clsDate objects.
     * @param A Reference to the first clsDate object.
     * @param B Reference to the second clsDate object.
     */
    static void Swap(clsDate& A, clsDate& B)
    {
        // clsDate has a static SwapDates method
        clsDate::SwapDates(A, B);
    }

    /**
     * @brief Randomly shuffles the elements of an integer array.
     * @param arr The integer array to shuffle.
     * @param arrLength The number of elements in the array.
     */
    static void ShuffleArray(int arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    /**
     * @brief Randomly shuffles the elements of a string array.
     * @param arr The string array to shuffle.
     * @param arrLength The number of elements in the array.
     */
    static void ShuffleArray(string arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    /**
     * @brief Generates and prints a string containing a specified number of tab characters.
     * @param NumberOfTabs The number of tab characters to generate.
     * @return A string containing the sequence of tab characters.
     */
    static string Tabs(short NumberOfTabs)
    {
        string t = "";
        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    /**
     * @brief Encrypts a text string by shifting character ASCII values by a specific key.
     * @param Text The original text string to encrypt.
     * @param EncryptionKey The integer value used to shift the characters.
     * @return The encrypted text string.
     */
    static string EncryptText(string Text, short EncryptionKey = 2)
    {
        // Note: Using `< Text.length()` instead of `<=` to avoid out-of-bounds errors on string
        for (int i = 0; i < Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text;
    }

    /**
     * @brief Decrypts a text string by reversing the character ASCII shift.
     * @param Text The encrypted text string to decrypt.
     * @param EncryptionKey The integer value originally used to shift the characters.
     * @return The decrypted (original) text string.
     */
    static string DecryptText(string Text, short EncryptionKey = 2)
    {
        // Note: Using `< Text.length()` instead of `<=` to avoid out-of-bounds errors on string
        for (int i = 0; i < Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text;
    }


    static string _NumberToWords(int Number)
    {
        if (Number == 0) return "Zero";

        string Ones[] = { "", "One", "Two", "Three", "Four", "Five", "Six",
                           "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve",
                           "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                           "Seventeen", "Eighteen", "Nineteen" };

        string Tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty",
                           "Sixty", "Seventy", "Eighty", "Ninety" };

        string Result = "";

        if (Number >= 1000000)
        {
            Result += _NumberToWords(Number / 1000000) + " Million ";
            Number %= 1000000;
        }
        if (Number >= 1000)
        {
            Result += _NumberToWords(Number / 1000) + " Thousand ";
            Number %= 1000;
        }
        if (Number >= 100)
        {
            Result += Ones[Number / 100] + " Hundred ";
            Number %= 100;
        }
        if (Number >= 20)
        {
            Result += Tens[Number / 10] + " ";
            Number %= 10;
        }
        if (Number > 0)
        {
            Result += Ones[Number] + " ";
        }

        return Result;
    }

    static string _FloatToWords(float Amount)
    {
        int Dollars = (int)Amount;
        int Cents = (int)round((Amount - Dollars) * 100);

        string Result = _NumberToWords(Dollars) + "Dollars";

        if (Cents > 0)
            Result += " and " + _NumberToWords(Cents) + "Cents";

        return Result;
    }

    
};