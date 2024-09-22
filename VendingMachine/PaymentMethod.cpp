#include "PaymentMethod.h"
#include "Logger.h"

bool IsValidAmount(int value) 
{
    switch (value) 
    {
        case ONE:
        case TWO:
        case FIVE:
        case TEN:
        case TWENTY:
        case FIFTY:
            return true;
        default:
            return false;
    }
}

void CashPayment::AddCash()
{
    DISPLAYMSG("Only cash of values %d,%d,%d\nAnd coins with %d,%d,%d is acceptable\n",ONE,TWO,FIVE,TEN,TWENTY,FIFTY);
    DISPLAYMSG("Enter Cash/Coin one by one\n -1 to quit\n");
    int data;
    while (1)
    {
        std::cin>>data;
        if (data == -1)
        {
            break;
        }
        else if (IsValidAmount(data))
        {
            currentAmount += data;
        }
        else
        {
            DISPLAYMSG("Invalid data retrived, please perform proper action\n");
        }
    }

}

void CashPayment::ReturnChange()
{
    if (currentAmount - amountNeeded > 0)
        DISPLAYMSG("Amount of %d has been returned\n", currentAmount - amountNeeded);
    else if (currentAmount - amountNeeded == 0)
        DISPLAYMSG("No Amount there to be returned\n");
    else
        DISPLAYMSG("Amount not enough so returning all your money\n");
}

bool CashPayment::ProcessPayment(int amount)
{
    amountNeeded = amount;
    currentAmount = 0;
    AddCash();
    bool retVal = false;
    if (currentAmount - amountNeeded >= 0)
    {
        retVal = true;
    }
    ReturnChange();
    return retVal;
}

bool CardPayment::ProcessPayment(int amount)
{
    amountNeeded = amount;
    AddCardDetails();
    return PaymentStatus();
}

void CardPayment::AddCardDetails()
{
    std::string cardNo, cardValidity, cardCVV, OTP;
    DISPLAYMSG("Enter Your Card Number\n");
    std::cin >> cardNo;
    DISPLAYMSG("Enter Your Card validity\n");
    std::cin >> cardValidity;
    DISPLAYMSG("Enter Your Card CVV Number\n");
    std::cin >> cardCVV;
    DISPLAYMSG("Enter OTP\n");
    std::cin >> OTP;
}

bool CardPayment::PaymentStatus()
{
    //Money Processing Logic
    return true;
}
