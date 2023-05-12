

#ifndef BACKEND_H_
#define BACKEND_H_

#include "expedia_flights_api.h"
#include "expedia_payments_api.h"
#include "expedia_hotels_api.h"
#include "payment_card.h"
#include "common_reservation.h"

class ExpediaBackend {

	vector<IFlightsManager*> flights_managers;
	vector<IHotelsManager*> hotels_managers;
	IPayment *payment_helper;
public:

	//prevent copy constructor
	//prevent assignment operator
	ExpediaBackend(const ExpediaBackend&) = delete;
	void operator =(const ExpediaBackend&) = delete;

	ExpediaBackend(){
		flights_managers = FlightsFactory::GetManagers();
		hotels_managers = HotelsFactory::GetManagers();
		payment_helper = PaymentFactory::GetPaymentHelper();

	}

	//find flights cross all airlines
	vector<Flight> FindFlights(const FlightRequest &request) const {
		vector<Flight> flights;
		for (IFlightsManager* manager : flights_managers){

			manager->SetFlightRequest(request);
			vector<Flight> all_flights = manager->SearchFlights();

			flights.insert(flights.end(), all_flights.begin(), all_flights.end());
		}
		return flights;
	}

	//find hotels
	vector<HotelRoom> FindHotels(const HotelRequest &request) const {
		vector<HotelRoom> rooms;
		for(IHotelsManager* manager : hotels_managers){

			manager->SetHotelRequest(request);
			vector<HotelRoom> all_rooms = manager->SearchHotelRooms();

			rooms.insert(rooms.end(), all_rooms.begin(), all_rooms.end());
		}
		return rooms;
	}

	bool ChargeCost (double cost , PaymentCard &payment_card){

		DebitCard* debitcard = nullptr;
		CreditCard* creditcard = nullptr;

		// determining the entry card either (credit or debit card)
		if( (debitcard = dynamic_cast<DebitCard*>(&payment_card)) ){
			payment_helper->SetUserInfo(payment_card.getOwner(),debitcard->getBillingAddress());
		}
		else if ( (creditcard = dynamic_cast<CreditCard*>(&payment_card)) ){
			payment_helper->SetUserInfo(payment_card.getOwner(),"");
		}

		payment_helper->SetCardInfo(payment_card.getCardNumber(), payment_card.getExpiryDate(),payment_card.getSecurityNumber());

		bool payment_status = payment_helper->MakePayment(cost);

		if(!payment_status) return false; // fail to reserve this flight

		return true;
	}


	bool UnChargeCost(double cost , PaymentCard &payment_card) const {
		return true;
	}

	bool CancelReservertion(const Reservation& reservation){
		return true;
	}

	bool ConfirmReservation(const Reservation& reservation){

		Reservation* reservationCopy = reservation.Clone();

		// check if reservation is flight reservation
		FlightReservation* flight= nullptr;

		if( (flight = dynamic_cast<FlightReservation*>(reservationCopy)) ){
			string name = flight->GetFlight().GetAirlineName();
			IFlightsManager* mgr = FlightsFactory::GetManager(name);


			if( mgr != nullptr && mgr->ReserveFlight(*flight))
				return true;

			return false; // we shouldn't delete mgr pointer. In future, the factory should do so
		}

		// check if reservation is hotel reservation
		HotelReservation* hotel = nullptr;
		if( (hotel = dynamic_cast<HotelReservation*>(reservationCopy)) ){
			string name = hotel->GetRoom().GetHotelName();
			IHotelsManager* mgr = HotelsFactory::GetManager(name);

			if (mgr != nullptr && mgr->ReserveRoom(*hotel))
				return true;

			return false;  // we shouldn't delete mgr pointer. In future, the factory should do so
		}

		// check if reservation is itinerary reservation
		ItineraryReservation* itinerary = nullptr;
		if( (itinerary = dynamic_cast<ItineraryReservation*>(reservationCopy)) ){
			vector<Reservation*> confirmed_reservations;

			for(Reservation* sub_reservation : itinerary->getReservations()){

				bool is_confirmed = ConfirmReservation(*sub_reservation);

				if(is_confirmed)
					confirmed_reservations.push_back(sub_reservation);

				else{
					// If failed to reserve, cancel all what is confirmed so far!
					for(Reservation* conf_reservation : confirmed_reservations){
						CancelReservertion(*conf_reservation);
					}
					return false;
				}
			}
		}
		else
			assert(false);

        // there is memory leak.
        // The above returns won't come here to remove this memory!
        // Always be sure you can return in middle of function or not.
		// Better not if u have pointers
		delete reservationCopy;
		reservationCopy = nullptr;
		return true;
	}



};

#endif /* BACKEND_H_ */
