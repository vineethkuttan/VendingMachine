#pragma once
#include <iostream>

enum COIN { ONE=1, TWO=2, FIVE=5 };
enum CASH { TEN = 10, TWENTY = 20, FIFTY = 50 };

class PaymentMethod
{
public:
	int amountNeeded;
	virtual bool ProcessPayment(int amount) = 0;
};

class CashPayment : public PaymentMethod
{

public:
	bool ProcessPayment(int amount) override;
private:
	int currentAmount;
	void AddCash();
	void ReturnChange();//Considering Machine has Change all the time.
};

class CardPayment : public PaymentMethod
{
public:
	bool ProcessPayment(int amount) override;
private:
	void AddCardDetails();
	bool PaymentStatus();
};