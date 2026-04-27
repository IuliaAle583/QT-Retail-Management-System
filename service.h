#pragma once
#include <cstdlib>
#include <algorithm>
#include "domain.h"
#include "repository.h"
#include "Action.h"
#include <stack>

class Service
{
private:
    std::vector<Action*> undoStackAdminMode;
    std::vector<Action*> redoStackAdminMode;
    std::vector<Action*> undoStackUserMode;
    std::vector<Action*> redoStackUserMode;
    Repository& repository;
    Repository& user_repository;
    int total_price;
public:
    void undoLastAction(std::vector<Action*>& currentUndoStack, std::vector<Action*>& currentRedoStack);
    void redoLastAction(std::vector<Action*>& currentUndoStack, std::vector<Action*>& currentRedoStack);
    void undoAdminMode();

    void redoAdminMode();

    void undoUserMode();

    void redoUserMode();

    /// Returns the total price of the items in the user's repository (cart).
    /// @return The total price of items in the user's cart
    [[nodiscard]] int GetTotalPrice() const;

    /// Constructor that initializes the Service with two repositories:
    /// one for the main trench coat repository and one for the user's cart.
    /// @param repository: The main repository holding trench coats.
    /// @param user_repository: The user's repository (cart)
    Service(Repository& repository, Repository& user_repository);

    /// Adds a trench coat to the user's repository (cart).
    /// @param coat: The trench coat to be added to the user repository.
    /// @param cUser: The trench coat user (to track user-specific details).
    /// @return An integer indicating the result of the operation (e.g., 0 for success)
    int addUserService(TrenchCoat coat, TrenchCoat cUser);

    /// Adds a new trench coat to the main repository.
    /// @param size: The size of the trench coat.
    /// @param color: The color of the trench coat.
    /// @param price: The price of the trench coat.
    /// @param quantity: The available quantity of the trench coat.
    /// @param photograph: The file path or link to the photograph of the trench coat
    void addService(std::string size, std::string color, int price, int quantity, std::string photograph);

    /// Retrieves the entire list of trench coats in the repository.
    /// @return A constant reference to the vector of trench coats in the repository
    const std::vector<TrenchCoat>& GetRepository();

    /// Filters the repository based on a specific size and returns the filtered list.
    /// @param size: The size to filter the trench coats by (e.g., "M", "L").
    /// @return A vector of trench coats that match the specified size.
    std::vector<TrenchCoat> GetFilteredRepository(std::string size);

    /// Retrieves the user's repository (cart).
    /// @return A vector containing all trench coats in the user's repository.
    std::vector<TrenchCoat> GetUserRepository();

    /// Deletes a trench coat from the repository based on size, color, and photograph, with an optional criteria for deletion.
    /// @param size: The size of the trench coat to delete.
    /// @param color: The color of the trench coat to delete.
    /// @param photograph: The photograph (or file path) of the trench coat to delete.
    /// @param criteria: A number or flag indicating the criteria for deletion (e.g., "sold out")
    void deleteService(const std::string& size, const std::string& color, const std::string& photograph, int criteria);

    /// Updates the price of a specific trench coat in the repository.
    /// @param size: The size of the trench coat to update.
    /// @param color: The color of the trench coat to update.
    /// @param photograph: The photograph (or file path) of the trench coat to update.
    /// @param price: The new price of the trench coat.
    void updatePriceService(std::string size, std::string color, std::string photograph, int price);

    /// Updates the quantity of a specific trench coat in the repository.
    /// @param size: The size of the trench coat to update.
    /// @param color: The color of the trench coat to update.
    /// @param photograph: The photograph (or file path) of the trench coat to update.
    /// @param quantity: The new quantity of the trench coat.
    void updateQuantityService(std::string size, std::string color, std::string photograph, int quantity);

    /// Returns the number of elements in the repository.
    /// @return The size of the repository (number of trench coats).
    int GetSize();


};

