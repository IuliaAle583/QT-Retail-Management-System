#pragma once
#include "repository.h"

class Action {

public:

    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;

};

class AddAction : public Action {

private:
    Repository& repository;
    TrenchCoat addedCoat;

public:
    AddAction(Repository& repository, TrenchCoat addedCoat);
    void executeUndo() override;
    void executeRedo() override;

};

class DeleteAction : public Action {

private:
    Repository& repository;
    TrenchCoat deletedCoat;

public:
    DeleteAction(Repository& repository, TrenchCoat deletedCoat);
    void executeUndo() override;
    void executeRedo() override;

};


class DeleteSoldOutAction : public Action {

private:
    Repository& repository;
    TrenchCoat deletedCoat;

public:
    DeleteSoldOutAction(Repository& repository, TrenchCoat deletedCoat);
    void executeUndo() override;
    void executeRedo() override;

};


class UpdateQuantityAction : public Action {

private:
    Repository& repository;
    TrenchCoat oldCoat;
    TrenchCoat newCoat;

public:
    UpdateQuantityAction(Repository& repository, TrenchCoat oldCoat, TrenchCoat newCoat);
    void executeUndo() override;
    void executeRedo() override;

};

class UpdatePriceAction : public Action {

private:
    Repository& repository;
    TrenchCoat oldCoat;
    TrenchCoat newCoat;

public:
    UpdatePriceAction(Repository& repository, TrenchCoat oldCoat, TrenchCoat newCoat);
    void executeUndo() override;
    void executeRedo() override;

};

class AddActionUserMode : public Action {

private:
    Repository& repository;
    Repository& user_repository;
    TrenchCoat oldCoat;
    TrenchCoat newCoat;

public:
    AddActionUserMode(Repository& repository, Repository& user_repository, TrenchCoat oldCoat, TrenchCoat newCoat);
    void executeUndo() override;
    void executeRedo() override;
};

class UpdateActionUserMode : public Action {

private:
    Repository& repository;
    Repository& user_repository;
    TrenchCoat oldCoatUser;
    TrenchCoat newCoatUser;
    TrenchCoat oldCoatAdmin;

public:
    UpdateActionUserMode(Repository& repository, Repository& user_repository, TrenchCoat oldCoatUser, TrenchCoat newCoatUser, TrenchCoat oldCoatAdmin);
    void executeUndo() override;
    void executeRedo() override;

};

class UpdateActionDeletedUserMode : public Action {

private:
    Repository& repository;
    Repository& user_repository;
    TrenchCoat oldCoatUser;
    TrenchCoat newCoatUser;
    TrenchCoat oldCoatAdmin;

public:
    UpdateActionDeletedUserMode(Repository& repository, Repository& user_repository, TrenchCoat oldCoatUser, TrenchCoat newCoatUser, TrenchCoat oldCoatAdmin);
    void executeUndo() override;
    void executeRedo() override;

};

class AddDeleteActionUserMode : public Action {

private:
    Repository& repository;
    Repository& user_repository;
    TrenchCoat oldCoat;
    TrenchCoat newCoat;

public:
    AddDeleteActionUserMode(Repository& repository, Repository& user_repository, TrenchCoat oldCoat, TrenchCoat newCoat);
    void executeUndo() override;
    void executeRedo() override;

};