#pragma once
class VendingMachine;

class VendingMachineState
{
public:
	virtual void SelectProduct()=0;
	virtual bool ProcessPayment()=0;
	virtual void DispenseProduct()=0;
};

class IdleState : public VendingMachineState
{
private:
	VendingMachine* vendingMachine;
public:
	IdleState(VendingMachine* a_vendingMachine);
	void SelectProduct() override;
	bool ProcessPayment() override;
	void DispenseProduct() override;
};

class SelectState : public VendingMachineState
{
private:
	VendingMachine* vendingMachine;
public:
	SelectState(VendingMachine* vendingMachine);
	void SelectProduct() override;
	bool ProcessPayment() override;
	void DispenseProduct() override;
};

class DispenseState : public VendingMachineState
{
private:
	VendingMachine* vendingMachine;
public:
	DispenseState(VendingMachine* vendingMachine);
	void SelectProduct() override;
	bool ProcessPayment() override;
	void DispenseProduct() override;
};