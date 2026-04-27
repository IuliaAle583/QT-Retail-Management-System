#pragma once
#include <cstring>
#include "domain.h"
#include "ShoppingBasket.h"
#include <vector>



class HTMLShoppingBasket : public ShoppingBasket {
private:
    std::vector<TrenchCoat> elements;
    std::string fileName;

public:

    /// Default constructor for the HTMLShoppingBasket class.
    /// Initializes the basket with an empty elements vector and an empty fileName
    HTMLShoppingBasket();

    /// Writes the current shopping basket data (elements) to the file.
    /// This function overrides the `write` function in the base class.
    void write() override;

    /// Opens and reads the shopping basket data from the file.
    /// This function overrides the `open` function in the base class.
    void open() override;

    /// Assigns the given vector of trench coats to the `elements` in the shopping basket.
    /// This function overrides the `data` function in the base class.
    /// @param elements: A vector of trench coats to be stored in the shopping basket.
    void data(std::vector<TrenchCoat> elements) override;

    /// Destructor for the HTMLShoppingBasket class. Defaulted for automatic cleanup.
    ~HTMLShoppingBasket() override = default;

};



