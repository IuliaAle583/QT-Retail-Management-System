#include "validator.h"
#include <ctype.h>
#include <string>
#include <stdexcept>

bool Validator::validate_color_product(std::string color) {
    for (char i : color)
        if (isdigit(i))
            return false;
    return true;
}

bool Validator::validate_size_product(std::string size) {
    if (size != "XXS" && size != "XS" && size != "S" && size != "M" && size != "L" && size != "XL" && size != "XXL")
        return false;
    else
        return true;
}

int Validator::validate_price_product(std::string price) {
    if (price.size() == 0)
        return -1;
    for (char i : price)
        if (isalpha(i))
            return -1;
    try {
        int new_price = std::stoi(price);
        if (new_price <= 0) {
            return -1;
        }
        return new_price;
    }
    catch (const std::invalid_argument& e) {
        return -1;
    }
    catch (const std::out_of_range& e) {
        return -1;
    }

}

bool Validator::validate_photograph_product(std::string photograph) {
    if (photograph.length() < 13)
        return false;
    if (photograph[0] != 'h' || photograph[1] != 't' || photograph[2] != 't' || photograph[3] != 'p' ||
        photograph[4] != 's' || photograph[5] != ':' || photograph[6] != '/' || photograph[7] != '/')
        return false;
    if (photograph.find(".com") == std::string::npos && photograph.find(".jpg") == std::string::npos)
        return false;
    return true;
}

int Validator::validate_quantity_product(std::string quantity)
{
    if (quantity.size() == 0)
        return -1;
    for (char i : quantity)
        if (isalpha(i))
            return -1;
    int new_quantity;
    new_quantity = stoi(quantity);
    return new_quantity;
}