

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "payment_card.h"
#include "common_reservation.h"
#include "user.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Customer: public User {

	vector<PaymentCard*> cards; //allow polymorphism
	ReservationsSet reservations;

public:

	// prevent copy constructor and assignment operator
	Customer(const Customer&) = delete;
	void operator=(const Customer&) = delete;

	// default constructor
	Customer() {
		setType(UserType::CustomerUser);



	}

	// add payment card to the customer
	void AddCard(const PaymentCard &card) {
		cards.push_back(card.Clone());
	}

	// add reservation to the customer
	void AddReservation(const Reservation &reservation) {
		reservations.AddReservation(*reservation.Clone());
	}

	// get customer's cards
	const vector<PaymentCard*>& getCards() const {
		return cards;
	}

	// get customer's reservations
	const ReservationsSet& getReservations() const {
		return reservations;
	}

	// destructor
	~Customer() {
		for (auto card : cards) {
			delete card;
		}
		cards.clear();
	}

};

#endif /* CUSTOMER_H_ */
