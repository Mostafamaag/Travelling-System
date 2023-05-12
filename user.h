
#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

enum class UserType{
	CustomerUser = 0,
	AdminUser =	1
};

class User{
	string name;
	string username;
	string password;
	string email;
	UserType type = UserType::CustomerUser;

public:

	//prevent copy constructor and assigning operator
	User(const User&) = delete;
	void operator =(const User&) = delete;

	User(){

	}

	virtual ~User(){ //to allow dynamic casting

	}
	void ReadUser(const string& user){
		setUsername(user);

		string s;
		cout << "Enter your name: ";
		cin >> s;
		setName(s);

		cout << "Enter your password: ";
		cin >> s;
		setPassword(s);

		cout << "Enter your email: ";
		cin >> s;
		setEmail(s);

	}

	string ToString() const{

		ostringstream oss;

		oss << "Name : " << name ;
		if(type == UserType::AdminUser){
			oss << " | Admin\n";
		}
		else{
			oss << " | Customer\n";
		}
		oss << "Username : " << username <<endl;
		oss << "Password : " << password <<endl;
		oss << "Email : " << email <<endl;

		return oss.str();
	}

	const string& getEmail() const {
		return email;
	}

	void setEmail(const string &email) {
		this->email = email;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string &name) {
		this->name = name;
	}

	const string& getPassword() const {
		return password;
	}

	void setPassword(const string &password) {
		this->password = password;
	}

	const string& getUsername() const {
		return username;
	}

	void setUsername(const string &username) {
		this->username = username;
	}

	UserType getType() const {
		return type;
	}

	void setType(UserType type) {
		this->type = type;
	}
};

class Admin : public User{

public:

    Admin(const Admin&) = delete;
    void operator=(const Admin&) = delete;

    Admin(){
    	setType(UserType::AdminUser);
    }


};

#endif /* USER_H_ */
