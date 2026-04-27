#pragma once
#include <string>
#include <exception>
#include <utility>
using namespace std;

class Exceptions : public std::exception
{
protected:
    std::string message;

public:
    /// Constructor for the Exceptions class.
    /// Initializes the exception with a specific message.
    /// @param MessageException: The error message associated with the exception.
    explicit Exceptions(std::string MessageException);

    /// Returns the error message when the exception is thrown.
    /// This method overrides the `what` method in the base `std::exception` class.
    /// @return A pointer to a constant character array containing the error message.
    [[nodiscard]] const char* what() const noexcept override;

};

class ValidatorException : public Exceptions
{
public:
    /// Constructor for the ValidatorException class.
    /// Initializes the exception with a specific message.
    /// @param MessageException: The error message associated with the exception.
    explicit ValidatorException(std::string MessageException);
};

class RepositoryException : public Exceptions
{
public:
    /// Constructor for the RepositoryException class.
    /// Initializes the exception with a specific message.
    /// @param MessageException: The error message associated with the exception.
    explicit RepositoryException(std::string MessageException);
};

class ExceptionsService : public Exceptions {

public:
    explicit ExceptionsService(string MessageException);
};