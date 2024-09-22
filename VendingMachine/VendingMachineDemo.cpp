#include "VendingMachine.h"


int main()
{
     auto VendingMachineInstance=VendingMachine::getInstance();
     VendingMachineInstance->ScanRackAndProducts();
     while (1)
     {
         VendingMachineInstance->SelectProduct();
         VendingMachineInstance->ProcessPayment();
         VendingMachineInstance->DispenseProduct();
     }     
}