#pragma once
#include <QWidget>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QComboBox>
#include <QVBoxLayout>
#include "service.h"
#include <QDialog>
#include "QShortcut"

class AdminModeGUI : public QDialog {

private:
    Service& service;
    QListWidget* coatsListWidget;
    QLineEdit* colorLineEdit, * priceLineEdit, * quantityLineEdit, * photographLineEdit;
    QComboBox* sizeComboBox;
    QPushButton* addButton, * deleteSoldOutButton, * deleteButton, * updatePriceButton,
        * updateQuantityButton, * displayButton, * undoButton, * redoButton, *goBackButton;
    QShortcut* undoShortcut, * redoShortcut;

public:
    AdminModeGUI(Service& service, QWidget* parent = NULL);
    ~AdminModeGUI();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    void populateList();
    void addCoat();
    void deleteCoat();
    void deleteSoldOutCoat();
    void updatePriceCoat();
    void updateQuantityCoat();
    void initAdminModeGUI();
    void undo();
    void redo();
    void clickGoBack();
    void goBack();

};
