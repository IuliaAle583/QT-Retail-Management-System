#include "exceptions.h"
#include <utility>

Exceptions::Exceptions(std::string MessageException) {
    this->message = std::move(MessageException);
}

const char* Exceptions::what() const noexcept {
    return this->message.c_str();
}

ValidatorException::ValidatorException(std::string MessageException) :
    Exceptions(move(MessageException)) {

}

RepositoryException::RepositoryException(std::string MessageException) :
    Exceptions(move(MessageException)) {

}

ExceptionsService::ExceptionsService(string MessageException) : Exceptions(move(MessageException)) {

}