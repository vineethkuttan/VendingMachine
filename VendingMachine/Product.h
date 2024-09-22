#pragma once
#include <string>
class Product
{
private:
	int productId;
	std::string name;
	int price;
public:
	Product(std::string arg_name, int arg_price);
	std::string GetName();
	int GetPrice();
	int GetProductId();
};