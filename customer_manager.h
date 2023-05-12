/*
 * customer_manager.h
 *
 *  Created on: Jan 9, 2023
 *      Author: Maag
 */

#ifndef CUSTOMER_MANAGER_H_
#define CUSTOMER_MANAGER_H_

#include "backend.h"
#include "payment_card.h"
#include "common_reservation.h"
#include "customer.h"
#include "user.h"

class CustomerManager {
private:
	Customer *customer;
	ExpediaBackend &expedia_manager;
public:
	CustomerManager(User* user,ExpediaBackend &expedia_manager):
		customer(dynamic_cast<Customer*>(user)),expedia_manager(expedia_manager) {

		if (customer == nullptr) {
            cout << "Error: User is null pointer as input\n";
            assert(customer != nullptr);
        }

		//adding temp card to new customer for test
		if (customer->getCards().empty()) {

			CreditCard *credit_card = new CreditCard();
			credit_card->setOwner(customer->getName());
			credit_card->setCardNumber("99-55-88-11");
			credit_card->setExpiryDate("5/23");
			credit_card->setSecurityNumber(777);
			customer->AddCard(*credit_card);
		}
	}


	//find flights across all airlines
	vector<Flight> FindFlights(const FlightRequest &request) const {
		vector<Flight> flights;
		flights = expedia_manager.FindFlights(request);
		return flights;
	}

	//find hotels across all hotels
	vector<HotelRoom> FindHotels(const HotelRequest &request) const {
		vector<HotelRoom> hotels;
		hotels = expedia_manager.FindHotels(request);
		return hotels;
	}

	//get payment choices
	vector<string> GetPaymentChoices(){
		vector<string> cards_info;

		for(PaymentCard *card : customer->getCards()){
			cards_info.push_back(card->ToString());
		}
		return cards_info;
	}

	//make reservation
	bool MakeReservation(const Reservation& reservation , PaymentCard& payment_card){

		bool is_paid = expedia_manager.ChargeCost(reservation.TotalCost(), payment_card);

		if(is_paid){
			cout << "Money withdraw successfully!" <<endl;

			bool is_confirmed = expedia_manager.ConfirmReservation(reservation);

			if(is_confirmed){
				cout << "Reservation Confirmed!" << endl;
				customer->AddReservation(reservation);
				return true;
			}
			else{
				cout << "Failed to confirm some of your reservation items"<<endl;
				cout << "Canceling payment and whatever reserved"<<endl;

				bool is_uncharged = expedia_manager.UnChargeCost(reservation.TotalCost(), payment_card);

				if(!is_uncharged) cout <<"Problems in returning back your money. Call us on 911\n";
			}
		}
		else {
			cout << "Failed to withdraw money for the reservation" << endl;
		}

		return false;

	}


	//get itineraries
	vector<string> GetItineraries() const {
		vector<string> itineraries;
		const ReservationsSet& set = customer->getReservations();

		for(const Reservation* reservation : set.getReservations()){
			itineraries.push_back(reservation->ToString());
		}

		return itineraries;
	}

	const Customer* getCustomer() const {
		return customer;
	}
};

#endif /* CUSTOMER_MANAGER_H_ */
