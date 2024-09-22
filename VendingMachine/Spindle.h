#pragma once
#include "Product.h"
#include<memory>
class Spindle
{
private:
	std::shared_ptr<Product> product;
	int productCount;
	int SpindleId;
public:
	//Spindle(std::string arg_productName, int arg_productPrice, int arg_productCount,int arg_spindleId);
	std::string GetSpindleProductName();
	int GetSpindleProductId();
	int GetSpindleProductPrice();
	int GetAvailableCount();
	int GetSpindleId();
	void DispenseSpindleProduct(int count_to_dispense);
	Spindle(std::shared_ptr<Product>& product, int productCount, int SpindleId);
};