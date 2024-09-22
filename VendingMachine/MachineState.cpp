#include "VendingMachine.h"
#include "Logger.h"
#include "PaymentMethod.h"

IdleState::IdleState(VendingMachine* a_vendingMachine):vendingMachine(a_vendingMachine)
{
}

void IdleState::SelectProduct()
{
	int productId, productCount;
	vendingMachine->GetInventory()->DisplayProducts();
	while (true)
	{
		DISPLAYMSG("Enter the poduct id and count of it and -1 , -1 for finish selecting\n");
		std::cin >> productId >> productCount;
		if (productId == -1 && productCount == -1)
		{
			DISPLAYMSG("Finished Selecting\n");
			vendingMachine->SetCurrentState(vendingMachine->GetSelectState());
			break;
		}
		if (vendingMachine->GetInventory()->IsProductAvailable(productId, productCount))
		{
			vendingMachine->GetInventory()->AddToCart(productId, productCount);
		}
	}
}

bool IdleState::ProcessPayment()
{
	ERRORLOG("Payment Processing invoked in idlestate\n");
	DISPLAYMSG("Vending Machine corrupted please report to technician");
	throw std::runtime_error("UnsupportedOperationException");
	return false;
}

void IdleState::DispenseProduct()
{
	ERRORLOG("Dispensing Products invoked in idlestate\n");
	DISPLAYMSG("Vending Machine corrupted please report to technician");
	throw std::runtime_error("UnsupportedOperationException");
}

SelectState::SelectState(VendingMachine* a_vendingMachine):vendingMachine(a_vendingMachine)
{
}

void SelectState::SelectProduct()
{
	ERRORLOG("Selecting Products invoked in selectState\n");
	DISPLAYMSG("Vending Machine corrupted please report to technician");
	throw std::runtime_error("UnsupportedOperationException");
}

bool SelectState::ProcessPayment()
{
	std::shared_ptr<PaymentMethod> paymentMethod;
	int selectedPaymentMode;
	DISPLAYMSG("Enter you mode of payment \n1 for cash \n2 for card\n");
	std::cin >> selectedPaymentMode;
	if (selectedPaymentMode != 1 && selectedPaymentMode != 2)
	{
		ERRORLOG("Invalid Payment Method %d\n",selectedPaymentMode);
		vendingMachine->GetInventory()->EmptyCart();
		vendingMachine->SetCurrentState(vendingMachine->GetIdleState());
	}
	else if (selectedPaymentMode == 1)
	{
		paymentMethod = std::make_shared<CashPayment>();
	}
	else
	{
		paymentMethod = std::make_shared<CardPayment>();
	}
	int CheckOutAmount = vendingMachine->GetInventory()->GetCheckoutAmount();
	if (paymentMethod->ProcessPayment(CheckOutAmount))
	{
		vendingMachine->SetCurrentState(vendingMachine->GetDispenseState());
		return true;
	}
	else
	{
		DISPLAYMSG("PaymentFailed so Emptying cart\n");
		return false;
	}
}

void SelectState::DispenseProduct()
{
	ERRORLOG("Dispensing Products invoked in selectState\n");
	DISPLAYMSG("Vending Machine corrupted please report to technician");
	throw std::runtime_error("UnsupportedOperationException");
}

DispenseState::DispenseState(VendingMachine* a_vendingMachine):vendingMachine(a_vendingMachine)
{
}

void DispenseState::SelectProduct()
{
	ERRORLOG("Selecting Products invoked in dispenseState\n");
	DISPLAYMSG("Vending Machine corrupted please report to technician");
	throw std::runtime_error("UnsupportedOperationException");
}

bool DispenseState::ProcessPayment()
{
	ERRORLOG("Payment Processing invoked in dispenseState\n");
	DISPLAYMSG("Vending Machine corrupted please report to technician");
	throw std::runtime_error("UnsupportedOperationException");
	return false;
}

void DispenseState::DispenseProduct()
{
	vendingMachine->GetInventory()->DispenseCart();
	vendingMachine->SetCurrentState(vendingMachine->GetIdleState());
}
