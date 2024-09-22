#pragma once
#include "MachineState.h"
#include "Inventory.h"
#include<mutex>
class VendingMachine
{
private:
	std::shared_ptr<VendingMachineState> idlestate;
	std::shared_ptr<VendingMachineState> selectstate;
	std::shared_ptr<VendingMachineState> dispensestate;
	std::shared_ptr<VendingMachineState> currentState;
	VendingMachine();
	static void initSingleton();
	std::shared_ptr<Inventory> inventory;
public:
	static std::shared_ptr<VendingMachine> instance;
	static std::once_flag initInstanceFlag;
	static std::shared_ptr<VendingMachine> getInstance();
	void ScanRackAndProducts();
	std::shared_ptr<Inventory>& GetInventory();
	void SelectProduct();
	bool ProcessPayment();
	void DispenseProduct();
	void SetCurrentState(std::shared_ptr<VendingMachineState>& state);
	std::shared_ptr<VendingMachineState>& GetIdleState();
	std::shared_ptr<VendingMachineState>& GetSelectState();
	std::shared_ptr<VendingMachineState>& GetDispenseState();
	VendingMachine(const VendingMachine&) = delete;
	VendingMachine& operator=(const VendingMachine&) = delete;
};