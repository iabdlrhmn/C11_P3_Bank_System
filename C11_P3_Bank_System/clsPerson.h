#pragma once
#include <iostream>
using namespace std;

class clsPerson
{
private:
	string _FirstName = "";
	string _LastName = "";
	string _Email = "";
	string _Phone = "";

public:
	// Constructor
	clsPerson(string FirstName = "", string LastName = "", string Email = "", string Phone = "") :
		_FirstName(FirstName), _LastName(LastName), _Email(Email), _Phone(Phone){}

	// Setters
	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}
	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}
	void SetEmail(string Email)
	{
		_Email = Email;
	}
	void SetPhone(string Phone)
	{
		_Phone = Phone;
	}

	// Getters
	string GetFirstName()
	{
		return _FirstName;
	}
	_declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;
	string GetLastName()
	{
		return _LastName;
	}
	_declspec(property(get = GetLastName, put = SetLastName)) string LastName;
	string GetEmail()
	{
		return _Email;
	}
	_declspec(property(get = GetEmail, put = SetEmail)) string Email;
	string GetPhone()
	{
		return _Phone;
	}
	_declspec(property(get = GetPhone, put = SetPhone)) string Phone; 
	// C++ does not support properties natively, but we can use Microsoft-specific extensions to achieve similar functionality.




};

