
#include "service.h"
#include "validator.h"
#include "ShoppingBasket.h"
#include <QVBoxLayout>
#include "AdminGUI.h"
#include "UserGUI.h"
#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QComboBox>
#include <QMainWindow>

class GUI : public QMainWindow
{
    Q_OBJECT
private:
    string type = "empty";
    Service& service;
    Repository& repository;
    ShoppingBasket* ASB;
    void initGUI();
    QComboBox* filetypeComboBox;
    QPushButton* adminModeButton, * userModeButton, * saveButton;

public:
    GUI(Service& service, Repository& repository, QWidget* parent = 0);
    ~GUI();
    void connectSignalsAndSlots();
    void startUserModeGUI();
    void startAdminModeGUI();
    void saveFileType();

};
