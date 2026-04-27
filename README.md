# Retail Management System

A C++ application based on the Qt framework designed to manage retail operations. The system provides an intuitive interface for handling inventory, sales, and client relationships, ensuring an efficient workflow for small to medium-sized retail businesses.

## Features

- **Inventory Management:** Comprehensive tools to add, update, and remove products from the database.
- **Sales Tracking:** Record transactions and monitor daily sales activities.
- **Client Management:** Maintain a database of customers, including contact details and purchase history.
- **Filtering & Sorting:** Advanced search options to quickly locate items by brand, category, or price.
- **Data Persistence:** Ensuring all records are saved and retrieved correctly between sessions.

## Built With

- **C++:** The core programming language for logic and performance.
- **Qt Framework:** Used for building the Graphical User Interface (GUI) and handling events.
- **Qt Designer:** For creating and styling the application windows.

## Architecture

The project follows a modular design to ensure code maintainability:

- **Domain:** Defines the core entities (Product, Client, Sale).
- **Repository:** Handles data storage and retrieval logic.
- **Service:** Contains the business logic and acts as an intermediary between the UI and Repository.
- **UI:** Implementation of the windows and dialogs using Qt's signal and slot mechanism.

## License

This project was developed for educational purposes as part of the Object-Oriented Programming curriculum.
