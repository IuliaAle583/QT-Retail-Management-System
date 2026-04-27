#include "service.h"
#include <utility>
#include "exceptions.h"

Service::Service(Repository& repository, Repository& user_repository) :
    repository{ repository }, user_repository{ user_repository }, total_price{ 0 }
{
}

void Service::addService(std::string size, std::string color, int price, int quantity, std::string photograph) {
    TrenchCoat newCoat{ size, color, price, quantity, photograph };
    this->repository.AddRepo(std::move(size), std::move(color), price, quantity, std::move(photograph));
    Action* currentAction = new AddAction(this->repository, newCoat);
    this->undoStackAdminMode.push_back(currentAction);
    this->redoStackAdminMode.clear();
}

const std::vector<TrenchCoat>& Service::GetRepository() {
    return this->repository.getArray();
}

std::vector<TrenchCoat> Service::GetUserRepository() {
    return this->user_repository.getArray();
}

int Service::GetSize() {
    return this->repository.GetSize();
}

void Service::deleteService(const std::string& size, const std::string& color, const std::string& photograph, int criteria) {
    if (criteria == 1) {
        TrenchCoat deletedCoat = this->repository.getCoat(size, color, photograph);
        this->repository.deleteRepo(size, color, photograph);
        Action* currentAction = new DeleteAction(this->repository, deletedCoat);
        this->undoStackAdminMode.push_back(currentAction);
        this->redoStackAdminMode.clear();
    }
    else if (criteria == 2) {
        TrenchCoat deletedCoat = this->repository.getCoat(size, color, photograph);
        this->repository.soldOut(size, color, photograph);
        Action* currentAction = new DeleteAction(this->repository, deletedCoat);
        this->undoStackAdminMode.push_back(currentAction);
        this->redoStackAdminMode.clear();
    }
}

void Service::updatePriceService(std::string size, std::string color, std::string photograph, int price) {  
    TrenchCoat oldCoat = this->repository.getCoat(size, color, photograph);
    TrenchCoat newCoat = TrenchCoat{ size, color, price, oldCoat.GetQuantity(), photograph };
    this->repository.UpdatePriceRepo(std::move(size), std::move(color), std::move(photograph), price);
    Action* currentAction = new UpdatePriceAction(this->repository, oldCoat, newCoat);
    this->undoStackAdminMode.push_back(currentAction);
    this->redoStackAdminMode.clear();
}

void Service::updateQuantityService(std::string size, std::string color, std::string photograph, int quantity) {
    TrenchCoat oldCoat = this->repository.getCoat(size, color, photograph);
    TrenchCoat newCoat = TrenchCoat{ size, color, oldCoat.GetPrice(), quantity, photograph };
    this->repository.UpdateQuantityRepo(std::move(size), std::move(color), std::move(photograph), quantity);
    Action* currentAction = new UpdateQuantityAction(this->repository, oldCoat, newCoat);
    this->undoStackAdminMode.push_back(currentAction);
    this->redoStackAdminMode.clear();
}

int Service::addUserService(TrenchCoat coat, TrenchCoat cUser) {
    int index = this->user_repository.Check(cUser.GetSize(), cUser.GetColor(), cUser.GetPhotograph());
    if (index == -1) {

        this->user_repository.AddRepo(cUser.GetSize(), cUser.GetColor(), cUser.GetPrice(), cUser.GetQuantity(),
            coat.GetPhotograph());
        if (coat.GetQuantity() == 0) {
            Action* currentAction = new AddDeleteActionUserMode(this->repository, this->user_repository, coat, cUser);
            this->undoStackUserMode.push_back(currentAction);
            this->redoStackUserMode.clear();
        }
        else {
            Action* currentAction = new AddActionUserMode(this->repository, this->user_repository, coat,
                cUser);
            this->undoStackUserMode.push_back(currentAction);
            this->redoStackUserMode.clear();
        }
        this->total_price = this->total_price + cUser.GetPrice();
    }
    else {

        TrenchCoat oldCoatUser = this->user_repository.getCoat(cUser.GetSize(), cUser.GetColor(), cUser.GetPhotograph());
        TrenchCoat newCoatUser = TrenchCoat{ oldCoatUser.GetSize(), oldCoatUser.GetColor(), oldCoatUser.GetPrice(), oldCoatUser.GetQuantity() + 1, oldCoatUser.GetPhotograph() };
        int new_quantity = this->user_repository.getArray()[index].GetQuantity() + 1;

        this->user_repository.UpdateQuantityRepo(cUser.GetSize(), cUser.GetColor(), cUser.GetPhotograph(), new_quantity);
        this->total_price = this->total_price + cUser.GetPrice();
        if (coat.GetQuantity() == 0) {
            Action* currentAction = new UpdateActionDeletedUserMode(this->repository, this->user_repository, oldCoatUser, newCoatUser, coat);
            this->undoStackUserMode.push_back(currentAction);
            this->redoStackUserMode.clear();
        }
        else {
            Action* currentAction = new UpdateActionUserMode(this->repository, this->user_repository, oldCoatUser, newCoatUser, coat);
            this->undoStackUserMode.push_back(currentAction);
            this->redoStackUserMode.clear();
        }
    }
    if (coat.GetQuantity() == 0) {
        this->repository.soldOut(coat.GetSize(), coat.GetColor(), coat.GetPhotograph());

        return 1;
    }
    return 0;
}

int Service::GetTotalPrice() const {
    return this->total_price;
}
std::vector<TrenchCoat> Service::GetFilteredRepository(std::string size) {
    if (size == "All sizes")
        return this->GetRepository();
    else {
        std::vector<TrenchCoat> elements(GetRepository().size());
        auto it = copy_if(GetRepository().begin(), GetRepository().end(), elements.begin(),
            [size](TrenchCoat coat) { return coat.GetSize() == size; });
        elements.resize(it - elements.begin());
        return elements;
    }
}

void Service::undoLastAction(std::vector<Action*>& currentUndoStack, std::vector<Action*>& currentRedoStack) {
    if (currentUndoStack.empty()) {
        throw ExceptionsService("no more undos");
    }

    Action* currentAction = currentUndoStack.back();
    currentAction->executeUndo();
    currentRedoStack.push_back(currentAction);
    currentUndoStack.pop_back();
}

void Service::redoLastAction(std::vector<Action*>& currentUndoStack, std::vector<Action*>& currentRedoStack) {
    if (currentRedoStack.size() == 0) {
        throw ExceptionsService("no more redos");
    }

    Action* currentAction = currentRedoStack.back();
    currentAction->executeRedo();
    currentUndoStack.push_back(currentAction);
    currentRedoStack.pop_back();
}

void Service::undoAdminMode() {
    this->undoLastAction(this->undoStackAdminMode, this->redoStackAdminMode);
}

void Service::redoAdminMode() {
    this->redoLastAction(this->undoStackAdminMode, this->redoStackAdminMode);
}

void Service::undoUserMode() {
    this->undoLastAction(this->undoStackUserMode, this->redoStackUserMode);
}

void Service::redoUserMode() {
    this->redoLastAction(this->undoStackUserMode, this->redoStackUserMode);
}
