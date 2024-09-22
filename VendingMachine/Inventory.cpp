#pragma once
#include "Logger.h"
#include "Inventory.h"
#include<iostream>
#include<iomanip>
int min(int a, int b)
{
    return a > b ? b : a;
}
bool Inventory::IsProductAvailable(int arg_Productid,int count)
{
    return std::get<1>(productCountPrice[arg_Productid]) >= count;
}

void Inventory::DisplayProducts()
{
    UpdateProducts();    
    printf("\n");
    std::cout << " ____________________________________________________" << std::endl;
    std::cout << "|"
        << std::setw(11) << std::left << "ProductName"
        << "|"
        << std::setw(14) << std::left << "ProductId"
        << "|"
        << std::setw(12) << std::left << "ProductPrice"
        << "|"
        << std::setw(12) << std::left << "ProductCount"
        << "|" << std::endl;

    for (auto it = productCountPrice.begin();
        it != productCountPrice.end(); ++it)
    {
        std::cout << " ----------------------------------------------------" << std::endl;        
        std::cout << "|"
            << std::setw(11) << std::left << std::get<0>(it->second).c_str()
            << "|"
            << std::setw(14) << std::left << it->first
            << "|"
            << std::setw(12) << std::left << std::get<2>(it->second)
            << "|" 
            << std::setw(12) << std::left << std::get<1>(it->second)
            << "|" << std::endl;
    }
    std::cout << " ----------------------------------------------------" << std::endl;
}

void Inventory::AddRack(shared_ptr<Rack>& rackToBeAdded)
{
    if (rackToBeAdded)
    {
        racks[rackToBeAdded->GetRackId()] = rackToBeAdded;
    }
    //racks.insert(std::make_pair(rackToBeAdded->GetRackId(), rackToBeAdded));
}

void Inventory::UpdateProducts()
{
    availableProductsMap.clear();
    productCountPrice.clear();
    productToRackID.clear();
    for (auto rack : racks)
    {
        auto currentRackProducts = rack.second->GetAllAvailableProducts();
        availableProductsMap.insert(currentRackProducts.begin(), currentRackProducts.end());
        for (auto spindle : currentRackProducts)
        {
            for (auto product : spindle.second)
            {
                if (!productCountPrice.count(std::get<1>(product.second)))
                {
                    productCountPrice[std::get<1>(product.second)] =
                        std::make_tuple(
                            std::get<0>(product.second),
                            std::get<2>(product.second),
                            std::get<3>(product.second));
                    productToRackID[std::get<1>(product.second)].insert(rack.first);
                }
                else
                {
                    std::get<1>(productCountPrice[std::get<1>(product.second)]) += std::get<2>(product.second);
                }
            }
        }
    }
}

void Inventory::AddToCart(int productId, int productCount)
{
    if (IsProductAvailable(productId, productCount))
    {
        cart[productId] = productCount;
        INFOLOG("Product %s of count %d is added\n", std::get<0>(productCountPrice[productId]).c_str(),
                                                      productCount);
        return;
    }
    ERRORLOG("Choosed Product is not Available at the Moment\n");
}

int Inventory::GetCheckoutAmount()
{
    int totalAmount = 0;
    for (auto item : cart)
    {
        int productAmount = std::get<2>(productCountPrice[item.first]);
        totalAmount += (productAmount * item.second);
    }
    return totalAmount;
}

void Inventory::EmptyCart()
{
    INFOLOG("Cart is Cleared\n");
    cart.clear(); 
}

void Inventory::DispenseCart()
{
    for (auto item : cart)
    {
        int productId = item.first;
        int productCountToBeDispensed = item.second;
        for (int rackID : productToRackID[productId])
        {
            int totalAvailableProductCount = 0;
            std::unordered_set<shared_ptr<Spindle>> allSpindleHandle;
            for (auto SpindleId : racks[rackID]->GetSpindleIDs(productId))
            {
                int availableProductCount=racks[rackID]->GetSpindleHandle(SpindleId)->GetAvailableCount();            
                if (availableProductCount >= productCountToBeDispensed)
                {                   
                    racks[rackID]->GetSpindleHandle(SpindleId)->DispenseSpindleProduct(productCountToBeDispensed);
                    productCountToBeDispensed = 0;
                    break;
                }
                else
                {
                    totalAvailableProductCount += racks[rackID]->GetSpindleHandle(SpindleId)->GetAvailableCount();
                    allSpindleHandle.insert(racks[rackID]->GetSpindleHandle(SpindleId));
                }
            }
            if (productCountToBeDispensed)
            {
                if (productCountToBeDispensed <= totalAvailableProductCount)
                {
                    for (auto spindle : allSpindleHandle)
                    {
                        int availableProductCountInCurrentSpindle = spindle->GetAvailableCount();
                        spindle->DispenseSpindleProduct(min(productCountToBeDispensed , availableProductCountInCurrentSpindle));
                        productCountToBeDispensed -= min(productCountToBeDispensed, availableProductCountInCurrentSpindle);
                        if (!productCountToBeDispensed)
                        {
                            racks[rackID]->RemoveAllEmptySpindle();
                            break;
                        }
                    }
                }
            }
            else
            {       
                racks[rackID]->RemoveAllEmptySpindle();
                break;
            }
        }

    }
}
