#include "Spindle.h"
#include "Logger.h"

Spindle::Spindle(std::shared_ptr<Product>& product, int productCount, int SpindleId)
	: product(product), productCount(productCount), SpindleId(SpindleId)
{
	/*DEBUGLOG("SpindleProductName %s SpindleProductPrice %d SpindleProductId %d SpindleId %d ProductCount %d\n", 
		product->GetName().c_str(), product->GetPrice(), product->GetProductId(),SpindleId,productCount);*/
}

std::string Spindle::GetSpindleProductName()
{
	return product->GetName();
}
int Spindle::GetSpindleProductId()
{
	return product->GetProductId();
}
int Spindle::GetSpindleProductPrice()
{
	return product->GetPrice();
}
int Spindle::GetAvailableCount()
{
	return productCount;
}
int Spindle::GetSpindleId()
{
	return SpindleId;
}
void Spindle::DispenseSpindleProduct(int count_to_dispense)
{
	if(productCount>= count_to_dispense)
		productCount -= count_to_dispense;
	//Handle Exception
}
