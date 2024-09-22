#pragma once
#include "Rack.h"
class Inventory
{
private:
	std::unordered_map<int,shared_ptr<Rack>> racks;
	RACK_TABLE availableProductsMap;
	std::unordered_map<int,std::tuple<std::string,int,int>> productCountPrice;
	std::unordered_map<int, std::unordered_set<int>> productToRackID;
	std::unordered_map<int, int> cart;
public:
	bool IsProductAvailable(int arg_Productid, int count);
	void DisplayProducts();
	void AddRack(shared_ptr<Rack>& rackToBeAdded);
	void UpdateProducts();
	void AddToCart(int productId, int productCount);
	int GetCheckoutAmount();
	void EmptyCart();
	void DispenseCart();
};