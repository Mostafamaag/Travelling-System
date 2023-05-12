

#ifndef PAYMENT_CARD_H_
#define PAYMENT_CARD_H_

#include <iostream>
using namespace std;

class PaymentCard {
	string owner;
	string card_number;
	string expiry_date;
	int security_number; //cvc
public:
	const string& getCardNumber() const {
		return card_number;
	}

	void setCardNumber(const string &cardNumber) {
		card_number = cardNumber;
	}

	const string& getExpiryDate() const {
		return expiry_date;
	}

	void setExpiryDate(const string &expiryDate) {
		expiry_date = expiryDate;
	}

	const string& getOwner() const {
		return owner;
	}

	void setOwner(const string &owner) {
		this->owner = owner;
	}

	int getSecurityNumber() const {
		return security_number;
	}

	void setSecurityNumber(int securityNumber) {
		security_number = securityNumber;
	}

	virtual string ToString() const {
		ostringstream oss;
		oss << "Owner: " << getOwner();
		oss << " Card number: " << getCardNumber();
		oss << " Expiry date: " << getExpiryDate();
		//oss << "CVC : " << getSecurityNumber() << "\n";

		return oss.str();
	}
	virtual PaymentCard* Clone() const = 0;

	virtual ~PaymentCard() {

	}
};

class CreditCard: public PaymentCard {

public:

	//override ToString()
	virtual string ToString() const override {
		ostringstream oss;
		oss << "[Credit Card] :" << PaymentCard::ToString();
		return oss.str();
	}

	//override Clone()
	virtual PaymentCard* Clone() const override {
		return new CreditCard(*this);
	}
};

class DebitCard: public PaymentCard {

	string billing_address;

public:


	//override ToString()
	virtual string ToString() const override{
		ostringstream oss;
		oss << "[Debit Card] :" << PaymentCard::ToString()<<
		" Billing Address: " << billing_address;
		;
		return oss.str();
	}

	//override Clone()
	virtual DebitCard* Clone() const override {
		return new DebitCard(*this);
	}

	const string& getBillingAddress() const {
		return billing_address;
	}

	void setBillingAddress(const string &billingAddress) {
		billing_address = billingAddress;
	}
};

#endif /* PAYMENT_CARD_H_ */
