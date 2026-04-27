
#include "UserGUI.h"
#include "AdminGUI.h"
#include "GUI.h"
#include "qformlayout.h"
#include "qgridlayout.h"
#include "CSVShoppingBasket.h"
#include "HTMLShoppingBasket.h"
#include "qlabel.h"
#include <iostream>
#include <QMessageBox>


using namespace std;

GUI::GUI(Service& service, Repository& repository, QWidget* parent) : repository{ repository }, service{ service }, QMainWindow(parent)
{
    this->initGUI();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {

    QFont buttonsFont("Roboto", 13, true);

    this->saveButton = new QPushButton{ "Save File Type" };
    this->saveButton->setFont(buttonsFont);
    this->saveButton->setStyleSheet("background-color: #4682B4; color: white;");

    this->adminModeButton = new QPushButton{ "Admin Mode" };
    this->adminModeButton->setFont(buttonsFont);
    this->adminModeButton->setStyleSheet("background-color: #4682B4; color: white;");


    this->userModeButton = new QPushButton{ "User Mode" };
    this->userModeButton->setFont(buttonsFont);
    this->userModeButton->setStyleSheet("background-color: #4682B4; color: white;");

    this->filetypeComboBox = new QComboBox{};
    this->filetypeComboBox->setFont(buttonsFont);
    this->filetypeComboBox->addItem("CSV File");
    this->filetypeComboBox->addItem("HTML File");
    this->filetypeComboBox->setStyleSheet(
        "QComboBox {"
        "   background-color: #4682B4;"
        "   color: white;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #4682B4;"
        "   color: white;"
        "}"
    );

    QVBoxLayout* mainLayout = new QVBoxLayout();

    QLabel* introduction = new QLabel();
    introduction->setText("WELCOME TO THE TRENCH COATS SHOP");
    introduction->setAlignment(Qt::AlignCenter);
    QFont introduction_font("Roboto", 20);
    introduction_font.setWeight(QFont::Bold);
    introduction->setFont(introduction_font);

    QLabel* space = new QLabel();
    space->setText("");

    QLabel* filename = new QLabel();
    filename->setText("Choose the type of the file");
    QFont font_filename("Roboto", 15, true);
    filename->setFont(font_filename);

    mainLayout->addWidget(introduction);
    mainLayout->addWidget(space);
    mainLayout->addWidget(space);

    QFormLayout* fileDetails = new QFormLayout();
    fileDetails->addRow(filename, this->filetypeComboBox);

    mainLayout->addLayout(fileDetails);

    QGridLayout* buttonsLayout = new QGridLayout();
    buttonsLayout->addWidget(this->saveButton, 0, 0);
    buttonsLayout->addWidget(this->userModeButton, 1, 0);
    buttonsLayout->addWidget(this->adminModeButton, 2, 0);

    mainLayout->addLayout(buttonsLayout);

    QWidget* mainWindow = new QWidget();
    mainWindow->setLayout(mainLayout);
    mainWindow->setStyleSheet("background-color: #F0F8FF;");
    setCentralWidget(mainWindow);


}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->saveButton, &QPushButton::clicked, this, &GUI::saveFileType);
    QObject::connect(this->userModeButton, &QPushButton::clicked, this, &GUI::startUserModeGUI);
    QObject::connect(this->adminModeButton, &QPushButton::clicked, this, &GUI::startAdminModeGUI);;
}

void GUI::startUserModeGUI() {
    if (type == "empty") {
        QMessageBox::critical(this, "Error", "You have to choose a type for the file first!");
        return;
    }
    else {
        this->setCursor(Qt::WaitCursor);
        UserModeGUI* umg = new UserModeGUI{ this->service, this->repository, this->ASB };
        //        umg->show();
        this->setCursor(Qt::ArrowCursor);
    }
}

void GUI::startAdminModeGUI() {
    if (type == "empty") {
        QMessageBox::critical(this, "Error", "You have to choose a type for the file first!");
        return;
    }
    else {
        this->setCursor(Qt::WaitCursor);
        AdminModeGUI* amg = new AdminModeGUI{ service };
        //        amg->show();
        this->setCursor(Qt::ArrowCursor);
    }
}

void GUI::saveFileType() {
    this->type = this->filetypeComboBox->currentText().toStdString();
    if (this->type == "CSV File")
        this->ASB = new CSVShoppingBasket();
    else if (this->type == "HTML File")
        this->ASB = new HTMLShoppingBasket();
}

GUI::~GUI() {

}
