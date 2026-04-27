#include <cstring>
#include "Domain.h"
#include <iostream>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <sstream>

TrenchCoat::TrenchCoat() {
    size = "";
    colour = "";
    price = 0;
    quantity = 0;
    link = "";
}

TrenchCoat::TrenchCoat(std::string size, std::string color,
    int price, int quantity,
    std::string link) :
    size{ std::move(size) },
    colour{ std::move(color) },
    price{ price },
    quantity{ quantity },
    link{ std::move(link) } {
}


void TrenchCoat::SetQuantity(int quantity) {
    this->quantity = quantity;
}

void TrenchCoat::SetPrice(int price) {
    this->price = price;
}

const std::string& TrenchCoat::GetSize() const {
    return this->size;
}

const std::string& TrenchCoat::GetColor() const {
    return this->colour;
}

const int& TrenchCoat::GetPrice() const {
    return this->price;
}

int TrenchCoat::GetQuantity() const {
    return this->quantity;
}

const std::string& TrenchCoat::GetPhotograph() const {
    return this->link;
}

TrenchCoat& TrenchCoat::operator=(const TrenchCoat& coat) {
    this->size = coat.size;
    this->colour = coat.colour;
    this->price = coat.price;
    this->quantity = coat.quantity;
    this->link = coat.link;
    return *this;
}

std::vector<std::string> TrenchCoat::tokenize(std::string str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::ostream& operator<<(std::ostream& output, const TrenchCoat& coat) {
    output << coat.size << "," << coat.colour << "," << coat.price << "," << coat.quantity << "," << coat.link;
    return output;
}

std::istream& operator>>(std::istream& input, TrenchCoat& coat) {
    std::string line;
    getline(input, line);
    std::vector<std::string> tokens = TrenchCoat::tokenize(line, ',');
    if (tokens.size() != 5)
        return input;
    coat.size = tokens[0];
    coat.colour = tokens[1];
    coat.price = stoi(tokens[2]);
    coat.quantity = stoi(tokens[3]);
    coat.link = tokens[4];
    return input;
}