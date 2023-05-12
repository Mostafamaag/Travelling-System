
#ifndef COMMON_RESERVATION_H_
#define COMMON_RESERVATION_H_

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Reservation {

public:

	virtual Reservation* Clone() const = 0;
	virtual double TotalCost() const = 0;
	virtual string ToString() const = 0;

	//since the class has virtual function
	//we need to create virtual destructor
	virtual ~Reservation(){

	}

};

class ItineraryReservation : public Reservation {

	vector<Reservation*> reservations;

public:
	ItineraryReservation(){

	}

	//since the class has pointers
	//we need to create copy constructor
	ItineraryReservation(const ItineraryReservation &another_reservation){
		for(const Reservation* reservation : another_reservation.getReservations() ){
			AddReservation(*reservation);
		}

	}

	const vector<Reservation*>& getReservations() const {
		return reservations;
	}

	void setReservations(const vector<Reservation*> &reservations) {
		this->reservations = reservations;
	}

	void AddReservation(const Reservation& reservation) {
		reservations.push_back(reservation.Clone());

	}

	virtual double TotalCost() const override {
		double totalcost = 0 ;

		for(const Reservation *reservation : reservations ){
			totalcost += reservation->TotalCost();
		}

		return totalcost;
	}

	virtual ~ItineraryReservation(){
		Clear();
	}

	//we need to free our pointers
	void Clear(){
		for(const Reservation *reservation : reservations){
			delete reservation;
			reservations.clear();
		}
	}

	virtual string ToString() const override {
		ostringstream oss;

		oss<<"**********************************\n";
		oss<< "Itinerary of " << reservations.size() << " sub-reservations\n";

		for(const Reservation *reservation : reservations){
			oss<<reservation->ToString() << "\n";
		}

		oss<<"Total Itinerary cost : " << TotalCost() << endl;
		oss<<"**********************************\n";

		return oss.str();

	}

	virtual Reservation* Clone() const override {
		return new ItineraryReservation(*this);
	}

};


class ReservationsSet : public ItineraryReservation{

public:
	// this class act like set of different reservations (not itinerary)
	// has same functionalities as ItineraryReservation
    // It is much better to have its own class, even empty class (for future changes)

	using ItineraryReservation::ItineraryReservation; //use ItineraryReservation copy constructor

	virtual Reservation* Clone() const override {
		return new ReservationsSet(*this);
	}

};


#endif /* COMMON_RESERVATION_H_ */
