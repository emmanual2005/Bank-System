#pragma once
#include<bits/stdc++.h>
#include"ClassPerson.h"
#include<fstream>
#include <random>
string RandomString(int length) {
	const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> dist(0, charset.size() - 1);
	string result;
	result.reserve(length);
	for (int i = 0; i < length; ++i) {
		result += charset[dist(generator)];
	}
	return result;
}
using namespace std;
class Account :public Person {
protected:
	enum enMod { EmptyMod = 0, UpdateMod = 1 };
	enMod Mod;
	string AccountNumber, Accountpassword;
	double AccountBalance;
	static Account ConvertData(string Line)
	{
		vector<string>ClientData;
		string temp;
		for (auto it : Line)
		{
			if (it == '/')
			{
				ClientData.push_back(temp);
				temp.clear();
			}
			else temp.push_back(it);
		}
		return Account(enMod::UpdateMod, ClientData[0], ClientData[1], ClientData[2],
			ClientData[3], ClientData[4], ClientData[5], stod(ClientData[6]));
	}
	static string ConvertClient(Account& Client)
	{
		string Temp;
		Temp = Client.Get_FirstName() + '/' + Client.Get_LastName() + '/' + Client.Get_Email() + '/' +
			Client.Get_Phone() + '/' + Client.Get_AccountNumber() + '/' + Client.Get_Accountpassword() +
			'/' + to_string(Client.Get_AccountBalance()) + '/';
		return Temp;
	}
	static Account EmptyClient()
	{
		return Account(enMod::EmptyMod, "", "", "", "", "", "", 0);
	}
	static void UpdateDataBaes(Account& Client)
	{
		vector<string>VectorDataClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Account CurClient = ConvertData(Line);
				if (Client.Get_AccountNumber() != CurClient.Get_AccountNumber())
					VectorDataClients.push_back(Line);
			}
			MyFile.close();
		}
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open())
		{
			for (auto it : VectorDataClients)
				MyFile << it << endl;
		}
		MyFile.close();

	}
	static void AddNewClientDataBase(Account& Client)
	{
		fstream Myfile;
		Myfile.open("Clients.txt", ios::out | ios::app);
		if (Myfile.is_open())
		{
			Myfile << ConvertClient(Client) << endl;
		}
	}
	static void ShowData(Account Client)
	{
		cout << Client.Get_FirstName() << string(15 - Client.Get_FirstName().size(), ' ') << '|';
		cout << Client.Get_LastName() << string(15 - Client.Get_LastName().size(), ' ') << '|';
		cout << Client.Get_Email() << string(35 - Client.Get_Email().size(), ' ') << '|';
		cout << Client.Get_Phone() << string(20 - Client.Get_Phone().size(), ' ') << '|';
		cout << "\n" << string(89, '-') << '\n';
	}

public:
	Account(enMod Mod, string Firstname, string LastName, string Email,
		string Phone, string AccountNumber, string Accountpassword, double AccountBalance)
		:Person(Firstname, LastName, Email, Phone)
	{
		this->Mod = Mod, this->AccountNumber = AccountNumber;
		this->Accountpassword = Accountpassword, this->AccountBalance = AccountBalance;
	}

	void Set_Accountpassword(string Accountpassword) { this->Accountpassword = Accountpassword; }
	void Set_AccountBalance(double AccountBalance) { this->AccountBalance = AccountBalance; }

	string Get_Accountpassword() { return this->Accountpassword; }
	string Get_AccountNumber() { return this->AccountNumber; }
	double Get_AccountBalance() { return this->AccountBalance; }
	bool IsEmpty()
	{
		return (Mod == enMod::EmptyMod);
	}
	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << this->Get_FirstName();
		cout << "\nLastName    : " << this->Get_LastName();
		cout << "\nEmail       : " << this->Get_Email();
		cout << "\nPhone       : " << this->Get_Phone();
		cout << "\nAcc. Number : " << this->AccountNumber;
		cout << "\nPassword    : " << this->Accountpassword;
		cout << "\nBalance     : " << this->AccountBalance;
		cout << "\n___________________\n";
	}

	static Account FindClient(string AccountNum, string Password)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Account CurClient = ConvertData(Line);
				if (AccountNum == CurClient.AccountNumber and Password == CurClient.Accountpassword)
				{
					MyFile.close();
					return CurClient;
				}
			}
			MyFile.close();
		}
		return EmptyClient();
	}
	static Account FindClient(string AccountNum)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				Account CurClient = ConvertData(Line);
				if (AccountNum == CurClient.AccountNumber)
				{
					MyFile.close();
					return CurClient;
				}
			}
			MyFile.close();
		}
		return EmptyClient();
	}
	static bool IsFoundClient(string AccountNum, string Password)
	{
		Account CheackCient = Account::FindClient(AccountNum, Password);
		return !(CheackCient.IsEmpty());
	}
	static bool IsFoundClient(string AccountNum)
	{
		Account CheackCient = Account::FindClient(AccountNum);
		return !(CheackCient.IsEmpty());
	}
	static void UpdateClient()
	{
		string AccountNumber, Password;
		bool flag = 0;
		while (!flag)
		{
			cout << "\nPlease Enter client Account Number: ";
			cin >> AccountNumber;
			cout << "\nPlease Enter client Account passwoed: ";
			cin >> Password;

			if (!IsFoundClient(AccountNumber, Password)) {
				cout << "\nAccount is not found: ";
				cout << "\nEnter 1 for tyr again";
				cout << "\nEnter 2 for Exit\n";
				int Option; cin >> Option;
				if (Option == 1)continue;
				else if (Option == 2)return;
				else {
					cout << "\n  did not understand your choice,Please try again.";
					continue;
				}
			}
			flag = 1;
			Account CurClient = Account::FindClient(AccountNumber, Password);
			string Temp;
			cout << "\nEnter FirstName: ";
			cin >> Temp; CurClient.Set_FirstName(Temp);

			cout << "\nEnter LastName: ";
			cin >> Temp; CurClient.Set_LastName(Temp);

			cout << "\nEnter Email: ";
			cin >> Temp; CurClient.Set_Email(Temp);

			cout << "\nEnter Phone: ";
			cin >> Temp; CurClient.Set_Phone(Temp);

			cout << "\nEnter Password: ";
			cin >> Temp; CurClient.Set_Accountpassword(Temp);
			UpdateDataBaes(CurClient);
			AddNewClientDataBase(CurClient);
			cout << "\nData updated.\n";
		}
	}
	static void AddNewClient()
	{
		Account CurClient = Account::EmptyClient();
		bool Done = 0;
		while (!Done)
		{
			string Temp = RandomString(10);
			if (!IsFoundClient(Temp))
			{
				Done = 1;
				CurClient.AccountNumber = Temp;
			}
		}
		string Temp;
		cout << "\nEnter FirstName: ";
		cin >> Temp; CurClient.Set_FirstName(Temp);

		cout << "\nEnter LastName: ";
		cin >> Temp; CurClient.Set_LastName(Temp);

		cout << "\nEnter Email: ";
		cin >> Temp; CurClient.Set_Email(Temp);

		cout << "\nEnter Phone: ";
		cin >> Temp; CurClient.Set_Phone(Temp);

		cout << "\nEnter Password: ";
		cin >> Temp; CurClient.Set_Accountpassword(Temp);

		AddNewClientDataBase(CurClient);
		cout << "\nAccount Created.\n";
	}
	static void DeletClient()
	{
		string AccountNumber, Password;
		bool flag = 0;
		while (!flag)
		{
			cout << "\nPlease Enter client Account Number: ";
			cin >> AccountNumber;
			cout << "\nPlease Enter client Account passwoed: ";
			cin >> Password;

			if (!IsFoundClient(AccountNumber, Password)) {
				cout << "\nAccount is not found: ";
				cout << "\nEnter 1 for tyr again.";
				cout << "\nEnter 2 for Exit.\n";
				int Option; cin >> Option;
				if (Option == 1)continue;
				else if (Option == 2)return;
				else {
					cout << "\ndid not understand your choice,Please try again.";
					continue;
				}
			}
			flag = 1;
			Account CurClient = Account::FindClient(AccountNumber, Password);
			UpdateDataBaes(CurClient);
			cout << "\nThe account has been deleted.\n";
		}
	}
	static void ShowClientsList()
	{
		cout << "FirstName" << string(6, ' ') << '|';
		cout << "LastName" << string(7, ' ') << '|';
		cout << "Email" << string(30, ' ') << '|';
		cout << "Phone" << string(15, ' ') << '|';
		cout << "\n" << string(89, '-') << '\n';
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		string Line;
		while (getline(MyFile, Line))
		{
			ShowData(ConvertData(Line));
		}
	}
};