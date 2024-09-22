#include "VendingMachine.h"

VendingMachine::VendingMachine()
{
    idlestate=std::make_shared<IdleState>(this);
    selectstate=std::make_shared<SelectState>(this);
    dispensestate = std::make_shared<DispenseState>(this);
    currentState = idlestate;
    inventory = std::make_shared<Inventory>();
}

void VendingMachine::initSingleton()
{
    instance.reset(new VendingMachine());
}

std::shared_ptr<VendingMachine> VendingMachine::getInstance()
{
    std::call_once(initInstanceFlag, &VendingMachine::initSingleton);
    return instance;
}

void VendingMachine::ScanRackAndProducts()
{
    //LOGIC FOR SCANNING PRODUCTS

    //FOR DEMO PURPOSE
    std::shared_ptr<Product> product1(std::make_shared<Product>("Kurkure", 20));
    std::shared_ptr<Product> product2(std::make_shared<Product>("Lays", 30));
    std::shared_ptr<Product> product3(std::make_shared<Product>("RedBull", 70));
    std::shared_ptr<Spindle> spindle1(std::make_shared<Spindle>(product1, 10, 1));
    std::shared_ptr<Spindle> spindle2(std::make_shared<Spindle>(product1, 10, 2));
    std::shared_ptr<Spindle> spindle3(std::make_shared<Spindle>(product2, 10, 3));
    std::shared_ptr<Spindle> spindle4(std::make_shared<Spindle>(product3, 10, 4));
    std::shared_ptr<Rack> rack1(new Rack(1));
    std::shared_ptr<Rack> rack2(new Rack(2));
    rack1->AddSpindle(spindle1);
    rack1->AddSpindle(spindle2);
    rack2->AddSpindle(spindle3);
    rack2->AddSpindle(spindle4);
    inventory->AddRack(rack1);
    inventory->AddRack(rack2);
}

std::shared_ptr<Inventory>& VendingMachine::GetInventory()
{
    return inventory;
}

void VendingMachine::SelectProduct()
{
    currentState->SelectProduct();
}

bool VendingMachine::ProcessPayment()
{
    return currentState->ProcessPayment();
}

void VendingMachine::DispenseProduct()
{
    currentState->DispenseProduct();
}

void VendingMachine::SetCurrentState(std::shared_ptr<VendingMachineState>& state)
{
    currentState = state;
}

std::shared_ptr<VendingMachineState>& VendingMachine::GetIdleState()
{
    return idlestate;
}

std::shared_ptr<VendingMachineState>& VendingMachine::GetSelectState()
{
    return selectstate;
}

std::shared_ptr<VendingMachineState>& VendingMachine::GetDispenseState()
{
    return dispensestate;
}

std::shared_ptr<VendingMachine> VendingMachine::instance = nullptr;
std::once_flag VendingMachine::initInstanceFlag;