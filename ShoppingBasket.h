#ifndef SHOPPINGBASKET_H
#define SHOPPINGBASKET_H

#pragma once
#include <vector>
#include "domain.h"

class ShoppingBasket {
public:
    // Virtual function to save the current basket data to a storage medium (e.g., file, database).
    // It is expected that the implementation of this method will handle writing
    // the basket's content (trench coats) to the specified storage.
    virtual void write() = 0;

    // Virtual function to open and load the basket's content from storage (e.g., file, database).
    // This will retrieve the items saved in the basket and populate it.
    virtual void open() = 0;

    // Virtual function to assign a set of trench coats(elements) to the basket.
    // The `elements` parameter is a vector of `TrenchCoat` objects to be added to the basket.
    virtual void data(std::vector<TrenchCoat> elements) = 0;

    // Virtual destructor, ensuring proper cleanup of resources when derived class objects are destroyed.
    virtual ~ShoppingBasket() = default;
};

#endif 
