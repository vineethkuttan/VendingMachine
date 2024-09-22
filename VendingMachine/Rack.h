#pragma once
#include "Spindle.h"
#include<unordered_map>
#include<unordered_set>
using std::shared_ptr;
#define RACK_TABLE std::unordered_map<int, std::unordered_map<int, std::tuple<std::string,int, int,int>>>
				//					rackid,				  spindleid		productName,productid,Count,Price
class Rack
{
private:
	int rackID;
	std::unordered_map<int,shared_ptr<Spindle>> spindles;
	std::unordered_map<int, std::unordered_set<int>> productToSpindleID;
public:
	Rack(int arg_rackID);
	int GetRackId();
	void AddSpindle(shared_ptr<Spindle>& spindleToBeAdded);
	void UpdateSpindle(shared_ptr<Spindle>& spindleToUpdated);
	std::unordered_map<std::string,int> GetEmptySpindles();
	std::unordered_set<int> GetSpindleIDs(int productId);
	shared_ptr<Spindle> GetSpindleHandle(int spindleId);
	void RemoveAllEmptySpindle();
	RACK_TABLE GetAllAvailableProducts();
	void DispenseSpindleProduct(int spindleId, int count);
};