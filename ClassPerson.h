#pragma once
#include<bits/stdc++.h>
using namespace std;
class Person
{
	string FirstName, LastName, Email, Phone;
public:
	Person(string FirstName, string LastName, string Email, string Phone)
	{
		this->FirstName = FirstName, this->LastName = LastName;
		this->Email = Email, this->Phone = Phone;
	}
	void Set_FirstName(string FirstName) { this->FirstName = FirstName; }
	void Set_LastName(string LastName) { this->LastName = LastName; }
	void Set_Email(string Email) { this->Email = Email; }
	void Set_Phone(string Phone) { this->Phone = Phone; }

	string Get_FirstName() { return this->FirstName; }
	string Get_LastName() { return this->LastName; }
	string Get_Email() { return this->Email; }
	string Get_Phone() { return this->Phone; }
};
