#include "CSVShoppingBasket.h"
#include "domain.h"
#include <string>
#include <fstream>
#include <windows.h>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <iostream>
#include <filesystem>


void CSVShoppingBasket::write() {
    /*
    std::ofstream outFile(this->fileName);
    for (const auto& CurrentElement : this->elements)
    {
        outFile << CurrentElement.GetSize() << ',' << CurrentElement.GetColor() << ',' << CurrentElement.GetPrice() << ','
            << CurrentElement.GetQuantity() << ',' << CurrentElement.GetPhotograph() << '\n';
    }
    outFile.close();
    this->elements.clear();*/

    std::ofstream outFile(this->fileName);
    if (!outFile.is_open()) {
        std::cerr << "ERROR: Could not open file for writing: " << this->fileName << std::endl;
    }
    for (const auto& CurrentElement : this->elements) {
        outFile << CurrentElement.GetSize() << ',' << CurrentElement.GetColor() << ','
            << CurrentElement.GetPrice() << ',' << CurrentElement.GetQuantity() << ','
            << CurrentElement.GetPhotograph() << '\n';
    }
    outFile.close();
    this->elements.clear();
}

/*
void CSVShoppingBasket::open() {
    std::ifstream  inFile(this->FileName);

    ShellExecute(nullptr, nullptr,
        reinterpret_cast<LPCWSTR>(R"(C:\Users\Iulia\Desktop\teste_oop\incercare2\incercare2\ShoppingBasket.csv)"),
        nullptr, nullptr, SW_SHOWNORMAL);
}*/

void CSVShoppingBasket::open() {
    //std::wstring wideFileName(this->fileName.begin(), this->fileName.end());

    //ShellExecute(nullptr, L"open", wideFileName.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    //sau
    std::string command = "start " + fileName;
    system(command.c_str());



}

CSVShoppingBasket::CSVShoppingBasket() {
    this->fileName = R"(D:\desktop2\oop\lab8_9\lab8_9\ShoppingBasket.csv)";
}

void CSVShoppingBasket::data(std::vector<TrenchCoat> data) {
    this->elements = data;
}