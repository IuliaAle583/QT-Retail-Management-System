#include "FileRepository.h"
#include <utility>
#include "Exceptions.h"
#include "domain.h"

FileRepository::FileRepository(std::string file) :Repository() {
    this->FileName = std::move(file);
    this->loadData();
}

void FileRepository::addRepo(const std::string& size, const std::string& color, int price, int quantity, std::string photograph) {

    int position;
    position = this->Check(size, color, photograph);
    if (position != -1)
    {
        throw RepositoryException("The given product already exists!");
    }
    else
    {
        TrenchCoat c(size, color, price, quantity, photograph);
        elements.push_back(c);
        writeData();
    }
}

void FileRepository::deleteRepo(std::string size, std::string color, std::string photograph) {
    int position = this->Check(size, color, photograph);
    if (position != -1)
    {
        elements.erase(elements.begin() + position);
        writeData();
    }
    else
        throw RepositoryException("The given product doesn't exist!");
}

void FileRepository::UpdatePriceRepo(std::string size, std::string color, std::string photograph, int price) {
    int position = this->Check(size, color, photograph);
    if (position != -1)
    {
        int quantity = elements[position].GetQuantity();
        TrenchCoat c(size, color, price, quantity, photograph);
        elements[position] = c;
        writeData();
    }
    else
        throw RepositoryException("The given product doesn't exist!");
}

void FileRepository::UpdateQuantityRepo(std::string size, std::string color, std::string photograph, int quantity) {
    int position = this->Check(size, color, photograph);
    if (position != -1)
    {
        int price = elements[position].GetPrice();
        TrenchCoat c(size, color, price, quantity, photograph);
        elements[position] = c;
        writeData();
    }
    else
        throw RepositoryException("The given product doesn't exist!");
}

void FileRepository::soldOut(std::string size, std::string color, std::string photograph) {
    int position = this->Check(size, color, photograph);
    int quantity = elements[position].GetQuantity();
    if (position != -1 && quantity == 0)
    {
        elements.erase(elements.begin() + position);
        writeData();
    }
    else
        throw RepositoryException("The given product isn't sold out or it doesn't exist!");
}

int FileRepository::Check(std::string size, std::string color, std::string photograph) {
    for (int i = 0; i < elements.size(); i++)
        if (elements[i].GetSize() == size && elements[i].GetColor() == color && elements[i].GetPhotograph() == photograph)
            return i;
    return -1;
}

int FileRepository::GetSize() {
    return elements.size();
}

void FileRepository::writeData() {

    std::ofstream  outFile(this->FileName);
    for (auto CurrentElement : this->elements)
    {
        outFile << CurrentElement << '\n';
    }
}

void FileRepository::loadData() {
    std::ifstream inFile(this->FileName);
    TrenchCoat CurrentElement;
    while (inFile >> CurrentElement)
    {
        this->elements.push_back(CurrentElement);
    }
}

const std::vector<TrenchCoat>& FileRepository::getArray() {
    return elements;
}

