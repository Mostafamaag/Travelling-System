

#ifndef CUSTOMER_VIEW_H_
#define CUSTOMER_VIEW_H_

#include "customer_manager.h"
#include "utilities.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class CustomerView {

	CustomerManager &customer_manager;
	const Customer &customer;
	ItineraryReservation current_itinerary;

	// read flight request from user;
	void ReadFlightRequest(FlightRequest &request) const {
		string str;

		cout << "Enter From : ";
		cin >> str;
		request.SetFrom(str);

		cout << "Enter From Date (dd/mm/yy) : ";
		cin >> str;
		request.SetDatetimeFrom(str);

		cout << "Enter To : ";
		cin >> str;
		request.SetTo(str);

		cout << "Enter To Date (dd/mm/yy) : ";
		cin >> str;
		request.SetDatetimeTo(str);

		int val;
		cout << "Enter number of adults, chlidren and infants : ";
		cin >> val;
		request.SetAdults(val);
		cin >> val;
		request.SetChildren(val);
		cin >> val;
		request.SetInfants(val);
	}

	// read hotel request from user;
	void ReadHotelRequest(HotelRequest &request) const {
		string str;

		cout << "Enter From Date (dd/mm/yy) : ";
		cin >> str;
		request.SetFromDate(str);

		cout << "Enter To Date (dd/mm/yy) : ";
		cin >> str;
		request.SetToDate(str);

        cout << "Enter Country : ";
        cin >> str;
        request.SetCountry(str);

        cout << "Enter City : ";
        cin >> str;
        request.SetCity(str);

		int val;
		cout << "Enter number of adults, chlidren : ";
		cin >> val;
		request.SetAdults(val);
		cin >> val;
		request.SetChildren(val);

	}

	int ChooseFlight(const vector<Flight> &flights) {
		if (flights.size() == 0) {
			cout << "No trips for this request!";
			return -1;
		}

		for (const Flight &flight : flights) {
			cout << flight.ToString() << endl;
		}

		return ReadInt(1, flights.size());
	}

	int ChooseRoom(const vector<HotelRoom> &rooms) {
		if (rooms.size() == 0) {
			cout << "No Rooms for this request!";
			return -1;
		}

		for (const HotelRoom &room : rooms) {
			cout << room.ToString() << endl;
		}

		return ReadInt(1, rooms.size());
	}

	void AddFlight() {
		FlightRequest request;
		ReadFlightRequest(request);

		vector<Flight> flights = customer_manager.FindFlights(request);
		int flight_choice = ChooseFlight(flights);

		if (flight_choice == -1)
			return;

		Flight &flight = flights[flight_choice - 1];
		FlightReservation reservation(request, flight);
		current_itinerary.AddReservation(reservation);
	}

	void AddHotel() {
		HotelRequest request;
		ReadHotelRequest(request);

		vector<HotelRoom> rooms = customer_manager.FindHotels(request);
		int room_choice = ChooseRoom(rooms);

		if (room_choice == -1)
			return;

		HotelRoom &room = rooms[room_choice - 1];
		HotelReservation reservation(request, room);
		current_itinerary.AddReservation(reservation);

	}

	void PayItinerary() {
		vector<string> payment_choices = customer_manager.GetPaymentChoices();
		int payment_choice = ShowMenu(payment_choices,
				"Select a payment chocie");


		PaymentCard *payment_card = customer.getCards()[payment_choice - 1];

		bool status = customer_manager.MakeReservation(current_itinerary,
				*payment_card);

		if (status)
			cout << "Itinerary reserved\n";
		else
			cout << "Failed to reserve the Itinerary\n";
	}
public:

	CustomerView(CustomerManager &customer_manager) :
			customer_manager(customer_manager), customer(
					*customer_manager.getCustomer()) {

	}

	void CutomerMenu() {
		cout << "\n\nHello " << customer.getName() << "\n";
		vector<string> menu;
		menu.push_back("View Profile");
		menu.push_back("Make Itinerary");
		menu.push_back("List My Itineraries");
		menu.push_back("Logout");

		while (true) {

			int choice = ShowMenu(menu);

			if (choice == 1) {
				ViewProfile();
			} else if (choice == 2) {
				MakeItinerary();
			} else if (choice == 3) {
				ListItineraries();
			} else {
				break;
			}
		}

	}

	void ViewProfile() const {
		cout << "\n" << customer.ToString() << "\n";
	}

	void MakeItinerary() {

		vector<string> menu;
		menu.push_back("Add flight");
		menu.push_back("Add hotel");
		menu.push_back("Done");
		menu.push_back("Cancel");

		while (true) {
			int choice = ShowMenu(menu);

			if (choice == 1)
				AddFlight();
			else if (choice == 2)
				AddHotel();
			else if (choice == 3) {
				PayItinerary();
				current_itinerary.Clear();
				break;
			} else {
				current_itinerary.Clear();
				break;
			}
		}
	}

	void ListItineraries() {
		vector<string> itineraries = customer_manager.GetItineraries();

		if (itineraries.size() == 0)
			cout << "No itineraries yet!";

		for (string &str : itineraries)
			cout << str << endl;
	}

};

#endif /* CUSTOMER_VIEW_H_ */
