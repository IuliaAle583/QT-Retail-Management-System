#pragma once
#include "repository.h"
#include "domain.h"
#include <fstream>
#include <string>

class FileRepository : public Repository
{
public:
    // Constructor to initialize the repository with a file.
    // Loads the data from the given file during initialization.
    explicit FileRepository(std::string file);

    // Returns the array of trench coats in the repository.
    // This function overrides the base class method.
    const std::vector<TrenchCoat>& getArray() override;

    // Adds a new trench coat to the repository.
    // Creates a new TrenchCoat object using the provided parameters
    // and saves the updated list to the file.
    void addRepo(const std::string& size, const std::string& color, int price, int quantity, std::string photograph);

    // Deletes a trench coat from the repository based on the given size, color, and photograph.
    // Updates the file after the deletion.
    void deleteRepo(std::string size, std::string color, std::string photograph) override;

    // Marks a trench coat as sold out (sets its quantity to 0) 
    // based on the size, color, and photograph, and saves the updated data.
    void soldOut(std::string size, std::string color, std::string photograph) override;

    // Updates the price of a trench coat based on size, color, and photograph.
    // After updating the price, the changes are saved to the file.
    void UpdatePriceRepo(std::string size, std::string color, std::string photograph, int price) override;

    // Updates the quantity of a trench coat based on size, color, and photograph.
    // The updated quantity is saved to the file.
    void UpdateQuantityRepo(std::string size, std::string color, std::string photograph, int quantity) override;

    // Checks if a trench coat with the given size, color, and photograph exists in the repository.
    int Check(std::string size, std::string color, std::string photograph) override;

    // Returns the size of the repository (number of trench coats).
    int GetSize() override;

private:
    std::string FileName;
    void loadData();
    void writeData();
};

