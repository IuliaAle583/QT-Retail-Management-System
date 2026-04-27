#pragma once
#include <string>
#include <vector>
#include <sstream>

class TrenchCoat {
private:
    std::string size;
    std::string colour;
    int price;
    int quantity;
    std::string link;

public:

    /// Constructor
    TrenchCoat();

    /// initialize the coat
    /// @param size the size of the coat
    /// @param color the color of the coat
    /// @param price the price of the coat
    /// @param quantity the quantity of the coat
    /// @param photograph the link of the coat
    TrenchCoat(std::string size, std::string colour, int price, int quantity, std::string link);

    /// set the quantity of the coat
    /// @param quantity the quantity we want to set
    void SetQuantity(int quantity);

    /// set the price of the coat
    /// @param price the price we want to set
    void SetPrice(int price);

    /// get the size of the coat
    /// @return returns the size of the coat
    const std::string& GetSize() const;

    /// get the color of the coat
    /// @return returns the color of the coat
    const std::string& GetColor() const;

    /// get the price of the coat
    /// @return returns the price of the coat
    const int& GetPrice() const;

    /// get the quantity of the coat
    /// @return returns the quantity of the goat
    int GetQuantity() const;

    static std::vector<std::string> tokenize(std::string str, char delimiter);

    /// get the link to the photograph of the coat
    /// @return returns the the link to the photograph of the coat
    [[nodiscard]] const std::string& GetPhotograph() const;

    friend std::ostream& operator<<(std::ostream&, const TrenchCoat&);

    friend std::istream& operator>>(std::istream&, TrenchCoat&);

    TrenchCoat& operator=(const TrenchCoat& coat);

    std::string toString() const {
        std::ostringstream oss;
        oss << "Size: " << this->size
            << ", Color: " << this->colour
            << ", Price: " << this->price
            << ", Quantity: " << this->quantity
            << ", Link: " << this->link;
        return oss.str();
    }
};

