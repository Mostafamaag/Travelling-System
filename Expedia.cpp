//============================================================================
// Name        : Expedia.cpp
// Author      : Mostafa
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include "user_manager.h"
#include "customer_view.h"

class ExpediaFrontend{
private:
	UsersManager* users_manager;
	ExpediaBackend* expedia_manager;
	CustomerManager* customer_manager = nullptr;

	void LoadDatabase(){
		users_manager->LoadDatabase();
	}

public:
	ExpediaFrontend(): users_manager(new UsersManager()),expedia_manager(new ExpediaBackend()){

	}

    ~ExpediaFrontend() {
        cout << "Destructor: ExpediaFrontend\n";

        if (users_manager != nullptr) {
            delete users_manager;
            users_manager = nullptr;
        }
    }

    void Run(){
    	LoadDatabase();
    	while(true){
    		users_manager->AccessSystem();
    		// the code focus on the customer view only
    		if (users_manager->getCurrentUser()->getType() == UserType::CustomerUser){
    			customer_manager = new CustomerManager(users_manager->getCurrentUser(),*expedia_manager);
    			CustomerView view(*customer_manager);
    			view.CutomerMenu();
    		}
    		else assert(false);
    	}
    }
};

int main() {

	ExpediaFrontend site;
	site.Run();


	return 0;
}
