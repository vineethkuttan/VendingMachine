#include "Logger.h"
#include "Product.h"
#include <mutex>

Product::Product(std::string arg_name, int arg_price): name(arg_name), price(arg_price)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	productId = static_cast<int>(std::time(nullptr));
	//DEBUGLOG("ProductName %s ProductPrice %d ProductId %d\n", GetName().c_str(), GetPrice(), GetProductId());
}

std::string Product::GetName()
{
	return name;
}

int Product::GetPrice()
{
	return price;
}

int Product::GetProductId()
{
	return productId;
}
