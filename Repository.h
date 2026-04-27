#pragma once
#include <cstdlib>
#include "domain.h"
#include <vector>
using namespace std;

class Repository
{
protected:
    std::vector<TrenchCoat> elements;

public:

    /// Initializes the repository with predefined products
    //void init_repository();

    /// Returns the number of elements in the repository
    virtual int GetSize();

    /// Returns a constant reference to the internal vector of trench coats
    virtual const std::vector<TrenchCoat>& getArray();

    /// Default constructor for the Repository
    Repository();

    /// Adds a trench coat to the repository.
    /// @param size: The size of the trench coat
    /// @param color: The color of the trench coat
    /// @param price: The price of the trench coat
    /// @param quantity: The available quantity
    /// @param photograph: The link or path to the photograph
    virtual void AddRepo(std::string size, std::string color, int price, int quantity, std::string photograph);

    /// Checks if a trench coat exists in the repository based on size, color, and photograph.
    /// @return The index of the trench coat if it exists, otherwise -1
    virtual int Check(std::string size, std::string color, std::string photograph);

    /// Deletes a trench coat completely from the repository based on size, color, and photograph
    virtual void deleteRepo(std::string size, std::string color, std::string photograph);

    /// Deletes a trench coat if its quantity has reached 0 (sold out)
    virtual void soldOut(std::string size, std::string color, std::string photograph);

    /// Updates the price of an existing trench coat.
    /// @param price: The new price
    virtual void UpdatePriceRepo(std::string size, std::string color, std::string photograph, int price);

    /// Updates the quantity of an existing trench coat.
    /// @param quantity: The new quantity
    virtual void UpdateQuantityRepo(std::string size, std::string color, std::string photograph, int quantity);

    TrenchCoat getCoat(string size, string color, string photograph);

};