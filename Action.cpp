#include "Action.h"

AddAction::AddAction(Repository& repository, TrenchCoat addedCoat) : repository{ repository } {
    this->addedCoat = addedCoat;
}

void AddAction::executeUndo() {
    this->repository.deleteRepo(this->addedCoat.GetSize(), this->addedCoat.GetColor(), this->addedCoat.GetPhotograph());
}

void AddAction::executeRedo() {
    this->repository.AddRepo(this->addedCoat.GetSize(), this->addedCoat.GetColor(), this->addedCoat.GetPrice(), this->addedCoat.GetQuantity(), this->addedCoat.GetPhotograph());
}

DeleteAction::DeleteAction(Repository& repository, TrenchCoat deletedCoat) : repository{ repository } {
    this->deletedCoat = deletedCoat;
}

void DeleteAction::executeUndo() {
    this->repository.AddRepo(this->deletedCoat.GetSize(), this->deletedCoat.GetColor(), this->deletedCoat.GetPrice(), this->deletedCoat.GetQuantity(), this->deletedCoat.GetPhotograph());
}

void DeleteAction::executeRedo() {
    this->repository.deleteRepo(this->deletedCoat.GetSize(), this->deletedCoat.GetColor(), this->deletedCoat.GetPhotograph());
}


UpdateQuantityAction::UpdateQuantityAction(Repository& repository, TrenchCoat oldCoat, TrenchCoat newCoat) : repository{ repository } {
    this->oldCoat = oldCoat;
    this->newCoat = newCoat;
}

void UpdateQuantityAction::executeUndo() {
    this->repository.UpdateQuantityRepo(this->oldCoat.GetSize(), this->oldCoat.GetColor(), this->oldCoat.GetPhotograph(), this->oldCoat.GetQuantity());
}

void UpdateQuantityAction::executeRedo() {
    this->repository.UpdateQuantityRepo(this->newCoat.GetSize(), this->newCoat.GetColor(), this->newCoat.GetPhotograph(), this->newCoat.GetQuantity());
}

UpdatePriceAction::UpdatePriceAction(Repository& repository, TrenchCoat oldCoat, TrenchCoat newCoat) : repository{ repository } {
    this->oldCoat = oldCoat;
    this->newCoat = newCoat;
}

void UpdatePriceAction::executeUndo() {
    this->repository.UpdatePriceRepo(this->oldCoat.GetSize(), this->oldCoat.GetColor(), this->oldCoat.GetPhotograph(), this->oldCoat.GetPrice());
}

void UpdatePriceAction::executeRedo() {
    this->repository.UpdatePriceRepo(this->newCoat.GetSize(), this->newCoat.GetColor(), this->newCoat.GetPhotograph(), this->newCoat.GetPrice());
}

AddActionUserMode::AddActionUserMode(Repository& repository, Repository& user_repository, TrenchCoat oldCoat, TrenchCoat newCoat) : repository{ repository }, user_repository{ user_repository } {
    this->oldCoat = oldCoat;
    this->newCoat = newCoat;
}

void AddActionUserMode::executeUndo() {
    this->user_repository.deleteRepo(this->oldCoat.GetSize(), this->oldCoat.GetColor(), this->oldCoat.GetPhotograph());
    this->repository.UpdateQuantityRepo(this->oldCoat.GetSize(), this->oldCoat.GetColor(), this->oldCoat.GetPhotograph(), this->oldCoat.GetQuantity() + 1);
}

void AddActionUserMode::executeRedo() {
    this->user_repository.AddRepo(this->newCoat.GetSize(), this->newCoat.GetColor(), this->newCoat.GetPrice(), this->newCoat.GetQuantity(), this->newCoat.GetPhotograph());
    this->repository.UpdateQuantityRepo(this->oldCoat.GetSize(), this->oldCoat.GetColor(), this->oldCoat.GetPhotograph(), this->oldCoat.GetQuantity());
}

UpdateActionUserMode::UpdateActionUserMode(Repository& repository, Repository& user_repository, TrenchCoat oldCoatUser,
    TrenchCoat newCoatUser, TrenchCoat oldCoatAdmin) : repository{ repository }, user_repository{ user_repository } {
    this->oldCoatAdmin = oldCoatAdmin;
    this->oldCoatUser = oldCoatUser;
    this->newCoatUser = newCoatUser;
}


void UpdateActionUserMode::executeUndo() {
    this->user_repository.UpdateQuantityRepo(this->oldCoatUser.GetSize(), this->oldCoatUser.GetColor(), this->oldCoatUser.GetPhotograph(), this->oldCoatUser.GetQuantity());
    this->repository.UpdateQuantityRepo(this->oldCoatAdmin.GetSize(), this->oldCoatAdmin.GetColor(), this->oldCoatAdmin.GetPhotograph(), this->oldCoatAdmin.GetQuantity() + 1);

}

void UpdateActionUserMode::executeRedo() {
    this->user_repository.UpdateQuantityRepo(this->newCoatUser.GetSize(), this->newCoatUser.GetColor(), this->newCoatUser.GetPhotograph(), this->newCoatUser.GetQuantity());
    this->repository.UpdateQuantityRepo(this->oldCoatAdmin.GetSize(), this->oldCoatAdmin.GetColor(), this->oldCoatAdmin.GetPhotograph(), this->oldCoatAdmin.GetQuantity());
}

UpdateActionDeletedUserMode::UpdateActionDeletedUserMode(Repository& repository, Repository& user_repository,
    TrenchCoat oldCoatUser, TrenchCoat newCoatUser, TrenchCoat oldCoatAdmin) : repository{ repository }, user_repository{ user_repository } {
    this->oldCoatUser = oldCoatUser;
    this->oldCoatAdmin = oldCoatAdmin;
    this->newCoatUser = newCoatUser;

}
void UpdateActionDeletedUserMode::executeUndo() {
    this->user_repository.UpdateQuantityRepo(this->oldCoatUser.GetSize(), this->oldCoatUser.GetColor(), this->oldCoatUser.GetPhotograph(), this->oldCoatUser.GetQuantity());
    this->repository.AddRepo(oldCoatAdmin.GetSize(), oldCoatAdmin.GetColor(), oldCoatAdmin.GetPrice(), oldCoatAdmin.GetQuantity() + 1, oldCoatAdmin.GetPhotograph());
}

void UpdateActionDeletedUserMode::executeRedo() {
    this->user_repository.UpdateQuantityRepo(this->newCoatUser.GetSize(), this->newCoatUser.GetColor(), this->newCoatUser.GetPhotograph(), this->newCoatUser.GetQuantity());
    this->repository.deleteRepo(this->oldCoatAdmin.GetSize(), this->oldCoatAdmin.GetColor(), this->oldCoatAdmin.GetPhotograph());
}

AddDeleteActionUserMode::AddDeleteActionUserMode(Repository& repository, Repository& user_repository, TrenchCoat oldCoat, TrenchCoat newCoat) : repository{ repository }, user_repository{ user_repository } {
    this->oldCoat = oldCoat;
    this->newCoat = newCoat;
}

void AddDeleteActionUserMode::executeUndo() {
    this->repository.AddRepo(this->oldCoat.GetSize(), this->oldCoat.GetColor(), this->oldCoat.GetPrice(), this->oldCoat.GetQuantity() + 1, this->oldCoat.GetPhotograph());
    this->user_repository.deleteRepo(this->newCoat.GetSize(), this->newCoat.GetColor(), this->newCoat.GetPhotograph());
}

void AddDeleteActionUserMode::executeRedo() {
    this->repository.deleteRepo(this->oldCoat.GetSize(), this->oldCoat.GetColor(), this->oldCoat.GetPhotograph());
    this->user_repository.AddRepo(this->newCoat.GetSize(), this->newCoat.GetColor(), this->newCoat.GetPrice(), this->newCoat.GetQuantity(), this->newCoat.GetPhotograph());
}