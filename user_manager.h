

#ifndef USER_MANGER_H_
#define USER_MANGER_H_

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include "user.h"
#include "customer.h"
#include "payment_card.h"
#include "utilities.h"

class UsersManager {
	User *current_user = nullptr;
	map<string, User*> username_to_userObj;

	void FreeLoadedData() {
		for (auto pair : username_to_userObj) {
			delete pair.second;
		}
		username_to_userObj.clear();
		current_user = nullptr;
	}


public:

	UsersManager(){}

	~UsersManager() {
		cout << "Destructor: UsersManager\n";

		FreeLoadedData();

	}

	UsersManager(const UsersManager&) = delete;
	void operator =(const UsersManager&) = delete;


	void LoadDatabase() {
		cout << "UsersManager Loading Database ..\n";

		//Dummy data

		Admin *admin_user = new Admin();
		admin_user->setUsername("mostafa12");
		admin_user->setPassword("12345");
		admin_user->setEmail("mostafa@gmail.com");
		admin_user->setName("Mostafa A");
		username_to_userObj[admin_user->getUsername()] = admin_user;

		Customer *customer_user = new Customer();
		customer_user->setUsername("user");
		customer_user->setPassword("123");
		customer_user->setEmail("user@gmail.com");
		customer_user->setName("user test");

		DebitCard *debit_card = new DebitCard();
		debit_card->setOwner(customer_user->getName());
		debit_card->setCardNumber("11-22-33-44");
		debit_card->setExpiryDate("11/23");
		debit_card->setSecurityNumber(111);
		debit_card->setBillingAddress("111 hello st, BC, Canada");
		customer_user->AddCard(*debit_card);

		CreditCard *credit_card = new CreditCard();
		credit_card->setOwner(customer_user->getName());
		credit_card->setCardNumber("44-33-22-11");
		credit_card->setExpiryDate("12/23");
		credit_card->setSecurityNumber(333);
		customer_user->AddCard(*credit_card);

		username_to_userObj[customer_user->getUsername()] = customer_user;

	}

	void SignUp() {
		string username;

		while (true) {
			cout << "Enter your username (No spaces) : ";
			cin >> username;

			if (username_to_userObj.count(username)) {
				cout << "This username already used! Try another one";
			} else
				break;
		}

		current_user = new Customer();
		current_user->ReadUser(username);


		username_to_userObj[current_user->getUsername()] = current_user;

		Login();

	}

	void Login() {

		LoadDatabase();
		string username, password;

		while (true) {
			cout << "Enter your username : ";
			cin >> username;

			cout << "Enter your password : ";
			cin >> password;

			if (!username_to_userObj.count(username)) {
				cout << "\nInvalid username! Try agin\n\n";
				continue;
			}

			User *user = username_to_userObj.find(username)->second;
			if (user->getPassword() != password) {
				cout << "\nInvalid password! Try agin\n\n";
				continue;
			}
			current_user = user;
			break;
		}

	}

	void AccessSystem() {
		//cout << "1.Login\n" << "2.SignUp\n";

		int choice = ShowMenu( { "Login", "SignUp" });
		if (choice == 1)
			Login();
		else
			SignUp();
	}

	User* getCurrentUser() const {
		// For simplicity, I don't return it as const, which is not good
		// One ok way: return as const, and user support clone + copy contstructor. Then caller can make his own copy
		return current_user;
	}
};

#endif /* USER_MANGER_H_ */
