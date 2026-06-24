#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsMyString
{
private:
	string _value;
public:
//constructors
	clsMyString() : _value(""){}
	clsMyString(string value) : _value(value) {}
//setters and getters
	void SetValue(string value)
	{
		_value = value;
	}
	string GetValue()
	{
		return _value;
	}
//deal with value with = operator
	__declspec(property(get = GetValue, put = SetValue)) string Value;

//other methods
//1.count words
    static short CountWords(string S1)
    {

        string delim = " "; // delimiter  
        short Counter = 0;
        short pos = 0;
        string sWord; // define a string variable  

        // use find() function to get the position of the delimiters  
        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word   
            if (sWord != "")
            {
                Counter++;
            }
            //erase() until positon and move to next word.
            S1.erase(0, pos + delim.length());
        }

        if (S1 != "")
        {
            Counter++; // it counts the last word of the string.
        }
        return Counter;
    }
    short CountWords()
    {
        return CountWords(clsMyString::_value);
    }
//2.Upper case first letter of each word
    static string  UpperFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);

            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }
    void UpperFirstLetterOfEachWord()
    {
        _value = UpperFirstLetterOfEachWord(clsMyString::_value);
	}
//3.LowerFirstLetterOfEachWord
    static string  LowerFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = tolower(S1[i]);
            }
            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }
    void LowerFirstLetterOfEachWord()
    {
        _value = LowerFirstLetterOfEachWord(clsMyString::_value);
	}
//4.Upper all string
    static string  UpperAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }

    void  UpperAllString()
    {
        _value = UpperAllString(_value);
    }

//5.Lower all string
    static string  LowerAllString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = tolower(S1[i]);
        }
        return S1;
    }

    void  LowerAllString()
    {
        _value = LowerAllString(_value);
    }
//6.Invert letter case
    static char  InvertLetterCase(char char1)
    {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    static string  InvertAllLettersCase(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = InvertLetterCase(S1[i]);
        }
        return S1;
    }

    void  InvertAllLettersCase()
    {
        _value = InvertAllLettersCase(_value);
    }
//7.Count capital letters, small letters, or all letters
    enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };
//7.1 if we want to count all letters, we can return the length of the string, otherwise we will loop and count capital or small letters.
    static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
    {
        if (WhatToCount == enWhatToCount::All)
        {
            return S1.length();
        }
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {

            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
                Counter++;

            if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
                Counter++;
        }
        return Counter;
    }
//7.2 if we want to count all letters, we can return the length of the string, otherwise we will loop and count capital or small letters.
    static short  CountCapitalLetters(string S1)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {

            if (isupper(S1[i]))
                Counter++;
        }
        return Counter;
    }

    short  CountCapitalLetters()
    {
        return CountCapitalLetters(_value);
    }
//7.3 if we want to count all letters, we can return the length of the string, otherwise we will loop and count capital or small letters.
    static short  CountSmallLetters(string S1)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (islower(S1[i]))
                Counter++;
        }
        return Counter;
    }

    short  CountSmallLetters()
    {
        return CountSmallLetters(_value);
    }
//8.Count specific letter with case sensitivity or without case sensitivity
    static short  CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (MatchCase)
            {
                if (S1[i] == Letter)
                    Counter++;
            }
            else
            {
                if (tolower(S1[i]) == tolower(Letter))
                    Counter++;
            }
        }
        return Counter;
    }

    short  CountSpecificLetter(char Letter, bool MatchCase = true)
    {
        return CountSpecificLetter(_value, Letter, MatchCase);
    }
//9.Count vowels in string
    static bool IsVowel(char Ch1)
    {
        Ch1 = tolower(Ch1);

        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }
//9.1 Count vowels in string
    static short  CountVowels(string S1)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (IsVowel(S1[i]))
                Counter++;
        }
        return Counter;
    }
//9.2 Count vowels in string
    short  CountVowels()
    {
        return CountVowels(_value);
    }
//10.Split string into vector of strings based on specific delimiter
    static vector<string> Split(string S1, string Delim)
    {
        vector<string> vString;

        short pos = 0;
        string sWord; // define a string variable  

        // use find() function to get the position of the delimiters  
        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word   
            if (sWord != "")
            {
                vString.push_back(sWord);
            }
            S1.erase(0, pos + Delim.length());  /* erase() until position and move to next word. */
        }

        if (S1 != "")
        {
            vString.push_back(S1); // it adds last word of the string.
        }

        return vString;
    }
//10.1 Split string into vector of strings based on specific delimiter
    vector<string> Split(string Delim)
    {
        return Split(_value, Delim);
    }
//11.Trim left, right, or both sides of the string
    static string TrimLeft(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(i, S1.length() - i);
            }
        }
        return "";
    }

    void TrimLeft()
    {
        _value = TrimLeft(_value);
    }
//11.2 Trim right of the string
    static string TrimRight(string S1)
    {
        for (short i = S1.length() - 1; i >= 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }

    void TrimRight()
    {
        _value = TrimRight(_value);
    }
//11.3 Trim both sides of the string
    static string Trim(string S1)
    {
        return (TrimLeft(TrimRight(S1)));
    }

    void Trim()
    {
        _value = Trim(_value);
    }
//12.Join vector of strings or array of strings into one string with specific delimiter
    static string JoinString(vector<string> vString, string Delim)
    {
        string S1 = "";

        for (string& s : vString)
        {
            S1 = S1 + s + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }
//12.2 Join vector of strings or array of strings into one string with specific delimiter
    static string JoinString(string arrString[], short Length, string Delim)
    {
        string S1 = "";

        for (short i = 0; i < Length; i++)
        {
            S1 = S1 + arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }
//13.Reverse words in string
    static string ReverseWordsInString(string S1)
    {
        vector<string> vString;
        string S2 = "";

        vString = Split(S1, " ");

        // declare iterator
        vector<string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {
            --iter;

            S2 += *iter + " ";
        }

        S2 = S2.substr(0, S2.length() - 1); //remove last space.

        return S2;
    }

    void ReverseWordsInString()
    {
        _value = ReverseWordsInString(_value);
    }
//14.Replace word in string with case sensitivity or without case sensitivity
    static string ReplaceWord(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
    {
        vector<string> vString = Split(S1, " ");

        for (string& s : vString)
        {
            if (MatchCase)
            {
                if (s == StringToReplace)
                {
                    s = sRepalceTo;
                }
            }
            else
            {
                if (LowerAllString(s) == LowerAllString(StringToReplace))
                {
                    s = sRepalceTo;
                }
            }
        }
        return JoinString(vString, " ");
    }
//14.2 Replace word in string with case sensitivity or without case sensitivity
    string ReplaceWord(string StringToReplace, string sRepalceTo)
    {
        return ReplaceWord(_value, StringToReplace, sRepalceTo);
    }
//15.Remove punctuations from string
    static string RemovePunctuations(string S1)
    {
        string S2 = "";

        for (short i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
            {
                S2 += S1[i];
            }
        }
        return S2;
    }

    void RemovePunctuations()
    {
        _value = RemovePunctuations(_value);
    }




};

