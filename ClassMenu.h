#pragma once
#include<bits/stdc++.h>
#include"ClassAccount.h"
using namespace std;
class Menu :protected Account {
	static void MenuShowClientList()
	{
		ShowClientsList();
	}
	static void MenuAddNewClient()
	{
		AddNewClient();
	}
	static void MenuDeletClient()
	{
		DeletClient();
	}
	static void MenuUpdataClient()
	{
		UpdateClient();
	}
	static void MenuDepositMoney()
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
			int Money;
			cout << "\nPlease Enter Deposit value: ";
			cin >> Money;
			CurClient.Set_AccountBalance(CurClient.Get_AccountBalance() + Money);
			UpdateDataBaes(CurClient);
			AddNewClientDataBase(CurClient);
			cout << "\nThe money has been deposited successfully.\n";
		}
	}
	static void MenuWithdrawMoney()
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
			int Money;

			bool Enough = 0;
			while (!Enough)
			{
				cout << "\nPlease Enter Deposit value: ";
				cin >> Money;
				if (Money > CurClient.Get_AccountBalance())
				{
					cout << "\nYour balance is insufficient: ";
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
				Enough = 1;
			}
			CurClient.Set_AccountBalance(CurClient.Get_AccountBalance() - Money);
			UpdateDataBaes(CurClient);
			AddNewClientDataBase(CurClient);
			cout << "\nThe money was withdrawn successfully.\n";
		}
	}
public:
	static void MainMenu()
	{
		cout << "\t" << string(25, '=') << '\n';
		cout << "\t\tMain Menu : \n";
		cout << "\t" << string(25, '=') << '\n';
		cout << "\t[1] Show Client Lists.\n";
		cout << "\t[2] Add New Client.\n";
		cout << "\t[3] Delet Client.\n";
		cout << "\t[4] Updata Client Info.\n";
		cout << "\t[5] Deposit Money.\n";
		cout << "\t[6] Withdraw Money.\n";
		cout << "\t[7] Exit.\n";
		cout << "\t" << string(25, '=') << '\n';
		cout << "\tchose what do you want to do? [1:7] : \n\t";
		int Choice; bool Done = 0;
		while (!Done)
		{
			cin >> Choice;
			if (Choice >= 1 and Choice <= 7)
			{
				Done = 1;
				if (Choice == 1)MenuShowClientList();
				else if (Choice == 2)MenuAddNewClient();
				else if (Choice == 3)MenuDeletClient();
				else if (Choice == 4)MenuUpdataClient();
				else if (Choice == 5)MenuDepositMoney();
				else if (Choice == 6)MenuWithdrawMoney();
				else {
					cout << "\tGood Bye\n";
					return;
				}
			}
			else {
				cout << "\tPlease rty again,chose what do you want to do? [1:7] : \n\t";
			}
		}
		MainMenu();
	}
};