#include "Rack.h"
#include<tuple>
Rack::Rack(int rackID) : rackID(rackID)
{

}

int Rack::GetRackId()
{
	return rackID;
}

void Rack::AddSpindle(shared_ptr<Spindle>& spindleToBeAdded)
{
	productToSpindleID[spindleToBeAdded->GetSpindleProductId()].insert(spindleToBeAdded->GetSpindleId());
	spindles[spindleToBeAdded->GetSpindleId()] = spindleToBeAdded;
}

void Rack::UpdateSpindle(shared_ptr<Spindle>& spindleToUpdated)
{
	for(std::unordered_map<int, std::unordered_set<int>>::iterator it= productToSpindleID.begin();
		it!=productToSpindleID.end();++it)
	{
		if (it->second.count(spindleToUpdated->GetSpindleId()))
		{
			it->second.erase(spindleToUpdated->GetSpindleId());
		}
	}
	productToSpindleID[spindleToUpdated->GetSpindleProductId()].insert(spindleToUpdated->GetSpindleId());
	spindles[spindleToUpdated->GetSpindleId()] = spindleToUpdated;
}

std::unordered_map<std::string,int> Rack::GetEmptySpindles()
{
	std::unordered_map<std::string, int> resultant;
	for (auto it : spindles)
	{
		if (it.second->GetAvailableCount() <= 0)
		{
			resultant[it.second->GetSpindleProductName()] = it.first;
		}
	}
	return resultant;
}

std::unordered_set<int> Rack::GetSpindleIDs(int productId)
{
	return productToSpindleID[productId];
}

shared_ptr<Spindle> Rack::GetSpindleHandle(int spindleId)
{
	return spindles[spindleId];
}

void Rack::RemoveAllEmptySpindle()
{
	auto emptyProducts= GetEmptySpindles();
	for (auto it:emptyProducts)
	{
		spindles.erase(it.second);
	}
}

RACK_TABLE Rack::GetAllAvailableProducts()
{
	RemoveAllEmptySpindle();
	RACK_TABLE resultant;
	for (const auto& spindle : spindles)
	{
		resultant[rackID][spindle.first] = std::make_tuple(spindle.second->GetSpindleProductName(),
																spindle.second->GetSpindleProductId(),
																spindle.second->GetAvailableCount(),
															spindle.second->GetSpindleProductPrice());
	}
	return resultant;
}

void Rack::DispenseSpindleProduct(int spindleId, int count)
{
	spindles[spindleId]->DispenseSpindleProduct(count);
}
