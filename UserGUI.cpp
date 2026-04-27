#include "UserGUI.h"
#include "qformlayout.h"
#include "qgridlayout.h"
#define NOMINMAX
#define _NO_CVCONST_H
#define _WINSOCKAPI_
#define NO_MINMAX
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#define STRICT
#include "windows.h"
#include <ShellAPI.h>
#undef byte
#include <qlabel.h>
#include "Delegate.h"
#include <QMessageBox>

UserModeGUI::UserModeGUI(Service& service, Repository& repository, ShoppingBasket* ASB, QWidget* parent) : repository{ repository }, service{ service }, ASB{ ASB }, QDialog{ parent } {
    this->initUserModeGUI();
    this->connectSignalsAndSlots();
    this->tableMode = new TableMode{ this->repository };
    this->shoppingBasketTableView = new QTableView{};
    this->shoppingBasketTableView->setModel(this->tableMode);
    this->shoppingBasketTableView->setItemDelegate(new PictureDelegate{});
}

void UserModeGUI::initUserModeGUI() {
    QFont buttonsFont("Roboto", 13, true);

    this->shoppingBasketListWidget = new QListWidget{};
    this->shoppingBasketListWidget->setFont(buttonsFont);

    this->sizeComboBox = new QComboBox{};
    this->sizeComboBox->setFont(buttonsFont);

    this->sizeComboBox->addItem("All sizes");
    this->sizeComboBox->addItem("XXS");
    this->sizeComboBox->addItem("XS");
    this->sizeComboBox->addItem("S");
    this->sizeComboBox->addItem("M");
    this->sizeComboBox->addItem("L");
    this->sizeComboBox->addItem("XL");
    this->sizeComboBox->addItem("XXL");

    this->tableButton = new QPushButton{ "Open Table View" };
    this->tableButton->setFont(buttonsFont);
    this->tableButton->setStyleSheet("background-color: #4682B4; color: white; border-radius: 5px;");

    this->undoButton = new QPushButton{ "Undo" };
    this->undoButton->setFont(buttonsFont);
    this->undoButton->setStyleSheet("background-color: #4682B4; color: white; border-radius: 5px;");

    this->redoButton = new QPushButton{ "Redo" };
    this->redoButton->setFont(buttonsFont);
    this->redoButton->setStyleSheet("background-color: #4682B4; color: white; border-radius: 5px;");

    this->displayProductsButton = new QPushButton{ "Display Products" };
    this->displayProductsButton->setFont(buttonsFont);
    this->displayProductsButton->setStyleSheet("background-color: #4682B4; color: white; border-radius: 5px;");

    this->displayShoppingBasketButton = new QPushButton{ "Display Shopping Basket" };
    this->displayShoppingBasketButton->setFont(buttonsFont);
    this->displayShoppingBasketButton->setStyleSheet("background-color: #4682B4; color: white; border-radius: 5px;");

    this->openApplicationButton = new QPushButton{ "Open Application" };
    this->openApplicationButton->setFont(buttonsFont);
    this->openApplicationButton->setStyleSheet("background-color: #4682B4; color: white; border-radius: 5px;");

    QLabel* space = new QLabel();
    space->setText("");

    QLabel* size = new QLabel();
    size->setText("Size");
    size->setFont(buttonsFont);

    QLabel* coatsText = new QLabel();
    coatsText->setText("Shopping Basket");
    QFont coatsFont("Roboto", 15, true);
    coatsText->setFont(coatsFont);

    QVBoxLayout* userLayout = new QVBoxLayout(this);
    userLayout->addWidget(coatsText);
    userLayout->addWidget(this->shoppingBasketListWidget);

    QFormLayout* coatDetails = new QFormLayout();
    coatDetails->addRow(size, this->sizeComboBox);
    userLayout->addLayout(coatDetails);

    QGridLayout* buttonsLayout = new QGridLayout();
    buttonsLayout->addWidget(this->displayProductsButton, 0, 0);
    buttonsLayout->addWidget(this->displayShoppingBasketButton, 1, 0);
    buttonsLayout->addWidget(this->openApplicationButton, 2, 0);
    buttonsLayout->addWidget(this->undoButton, 3, 0);
    buttonsLayout->addWidget(this->redoButton, 4, 0);
    buttonsLayout->addWidget(this->tableButton, 5, 0);

    userLayout->addLayout(buttonsLayout);

    QWidget* userDisplayWindow = new QWidget();
    userDisplayWindow->setLayout(userLayout);
    userDisplayWindow->show();
}

void UserModeGUI::connectSignalsAndSlots() {
    QObject::connect(this->displayProductsButton, &QPushButton::clicked, this, &UserModeGUI::displayProducts);
    QObject::connect(this->displayShoppingBasketButton, &QPushButton::clicked, this, &UserModeGUI::populateShoppingBag);
    QObject::connect(this->openApplicationButton, &QPushButton::clicked, this, &UserModeGUI::openApplication);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &UserModeGUI::undo);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &UserModeGUI::redo);
    QObject::connect(this->tableButton, &QPushButton::clicked, this, &UserModeGUI::openTableView);
}

void UserModeGUI::connectSignalsAndSlotsDisplayFunction() {
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserModeGUI::nextProduct);
    QObject::connect(this->buyButton, &QPushButton::clicked, this, &UserModeGUI::buyProduct);
}

UserModeGUI::~UserModeGUI() {

}

int UserModeGUI::getSelectedIndex() {
    QModelIndexList selectedIndexes = this->coatsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
        return -1;
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void UserModeGUI::displayProducts() {
    if (this->service.GetRepository().size() == 0) {
        QMessageBox::critical(this, "Error", "There are no products on the stock!");
        return;
    }
    else {
        this->size = this->sizeComboBox->currentText().toStdString();
        this->initDisplayProducts();
        this->displayUserProducts();
    }
}

void UserModeGUI::initDisplayProducts() {
    QFont buttonsFont("Roboto", 13, true);

    this->coatsListWidget = new QListWidget{};
    this->coatsListWidget->setFont(buttonsFont);

    this->nextButton = new QPushButton{ "Next" };
    this->nextButton->setFont(buttonsFont);

    this->buyButton = new QPushButton{ "Buy" };
    this->buyButton->setFont(buttonsFont);

    //    this->payButton = new QPushButton{"Pay"};
    //    this->payButton->setFont(buttonsFont);

    QLabel* coatsText = new QLabel();
    coatsText->setText("Products");
    QFont coatsFont("Consolas", 15, true);
    coatsText->setFont(coatsFont);

    QVBoxLayout* displayLayout = new QVBoxLayout();
    displayLayout->addWidget(coatsText);
    displayLayout->addWidget(this->coatsListWidget);

    QGridLayout* buttonsLayout = new QGridLayout();
    buttonsLayout->addWidget(this->nextButton, 0, 0);
    buttonsLayout->addWidget(this->buyButton, 0, 1);
    //    buttonsLayout->addWidget(this->payButton, 0, 2);

    displayLayout->addLayout(buttonsLayout);
    QWidget* mainDisplayWindow = new QWidget();
    mainDisplayWindow->setLayout(displayLayout);
    mainDisplayWindow->show();
}

void UserModeGUI::populateDisplayProducts(int position, vector<TrenchCoat> coats) {
    this->coatsListWidget->clear();
    TrenchCoat c = coats[position];
    //    this->position = position;
    this->coatsListWidget->addItem(QString::fromStdString(c.GetSize() + " - " + c.GetColor() + " - " + to_string(c.GetPrice()) + " - " + to_string(c.GetQuantity())
        + " - " + c.GetPhotograph()));
    //    ShellExecute(NULL, "open", coats[position].GetPhotograph().c_str(), NULL, NULL, SW_SHOWNORMAL);
    std::string photoPath = coats[position].GetPhotograph();
    std:wstring widePhotoPath(photoPath.begin(), photoPath.end());
    ShellExecute(nullptr, L"open", widePhotoPath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

}

void UserModeGUI::populateShoppingBag() {
    this->shoppingBasketListWidget->clear();
    vector<TrenchCoat> Coats = this->service.GetUserRepository();
    for (TrenchCoat& c : Coats) {
        this->shoppingBasketListWidget->addItem(QString::fromStdString(c.GetSize() + " - " + c.GetColor() + " - " + to_string(c.GetPrice()) + " - " + to_string(c.GetQuantity())
            + " - " + c.GetPhotograph()));

    }
}

void UserModeGUI::clearPopulatedList() {
    this->coatsListWidget->clear();
}

void UserModeGUI::nextProduct() {
    vector<TrenchCoat> coats = this->service.GetFilteredRepository(this->size);
    if (coats.size() == 0) {
        QMessageBox::critical(this, "Error", "There are no products on the stock!");
        return;
    }
    if (this->position == coats.size() - 1)
        this->position = 0;
    else
        this->position += 1;
    this->populateDisplayProducts(this->position, coats);
    this->notifyModel();

}

void UserModeGUI::buyProduct() {
    vector<TrenchCoat> coats = this->service.GetFilteredRepository(this->size);
    if (coats.size() == 0) {
        QMessageBox::critical(this, "Error", "There are no products on the stock!");
        return;
    }
    int pos = this->position;
    int i = this->getSelectedIndex();
    if (i == -1) {
        QMessageBox::critical(this, "Error", "Please select the item!");
        return;
    }
    else {
        if (coats[pos].GetQuantity() == 1 && coats.size() == 1)
        {
            QMessageBox::information(this, "Information", "Congratulations! You spent all your money and bought everything :) !");
            this->clearPopulatedList();

        }
        else if (coats[pos].GetQuantity() == 1) {
            this->populateDisplayProducts(this->position++, coats);
        }
        this->service.updateQuantityService(coats[pos].GetSize(), coats[pos].GetColor(), coats[pos].GetPhotograph(),
            coats[pos].GetQuantity() - 1);

        TrenchCoat oldCoat(coats[pos].GetSize(), coats[pos].GetColor(), coats[pos].GetPrice(), coats[pos].GetQuantity() - 1,
            coats[pos].GetPhotograph());
        TrenchCoat addedCoat(coats[pos].GetSize(), coats[pos].GetColor(), coats[pos].GetPrice(), 1, coats[pos].GetPhotograph());
        if (this->position == coats.size() - 1)
            this->position = 0;
        else
            this->position += 1;
        this->service.addUserService(oldCoat, addedCoat);
        this->notifyModel();
    }
}

void UserModeGUI::displayUserProducts() {
    this->position = 0;
    vector<TrenchCoat> coats = this->service.GetFilteredRepository(this->size);
    if (coats.size() == 0)
    {
        QMessageBox::critical(this, "Error", "There are no products on the stock!");
        return;
    }
    this->populateDisplayProducts(0, coats);
    this->connectSignalsAndSlotsDisplayFunction();
}

void UserModeGUI::openApplication() {
    this->ASB->data(this->service.GetUserRepository());
    this->ASB->write();
    this->ASB->open();

}

void UserModeGUI::undo() {
    try {
        this->service.undoUserMode();
        this->notifyModel();
    }
    catch (...) {
        QMessageBox::critical(this, "Error", "There are no more undos!");
    }
}

void UserModeGUI::redo() {

    try {
        this->service.redoUserMode();
        this->notifyModel();
    }
    catch (...) {
        QMessageBox::critical(this, "Error", "There are no more redos!");

    }
}

void UserModeGUI::openTableView() {
    //    this->tableMode = new TableMode {this->repository};
    //    this->shoppingBasketTableView = new QTableView{};
    //    this->shoppingBasketTableView->setModel(this->tableMode);
    this->shoppingBasketTableView->resize(1000, 800);
    this->shoppingBasketTableView->resizeColumnsToContents();
    this->shoppingBasketTableView->resizeRowsToContents();
    this->shoppingBasketTableView->show();
}

void UserModeGUI::notifyModel() {
    this->tableMode->updateInternalData();
    this->shoppingBasketTableView->resize(1200, 800);
    this->shoppingBasketTableView->resizeColumnsToContents();
    this->shoppingBasketTableView->resizeRowsToContents();
}