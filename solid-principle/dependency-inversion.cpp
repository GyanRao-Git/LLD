#include <iostream>
#include <string>
using namespace std;

/*

Dependency Injection (DI) is a design pattern where a class receives the objects it depends on (its dependencies) from outside, rather than creating them itself. This promotes loose coupling, making the code more flexible, modular, and easier to test. For example, instead of a Car class creating its own Engine, the Engine is injected into the Car, allowing different types of engines to be used without changing the Car code.

*/

// Abstraction - interface
class IDatabase {
public:
    virtual void saveOrder(string orderData) = 0;
    virtual ~IDatabase() {}
};

// Low-level class 1 - MySQL
class MySQLDatabase : public IDatabase {
public:
    void saveOrder(string orderData) override {
        cout << "Saving order to MySQL: " << orderData << endl;
    }
};

//  Low-level class 2 - MongoDB
class MongoDBDatabase : public IDatabase {
public:
    void saveOrder(string orderData) override {
        cout << "Saving order to MongoDB: " << orderData << endl;
    }
};

//  High-level class - depends on abstraction, not implementation
class OrderService {
private:
    IDatabase* database;

public:
    // Dependency is injected via constructor
    OrderService(IDatabase* db) { // interface passed so it can be any of the child classes based on what it is passed 
        this->database = db;
    }

    void placeOrder(string orderData) {
        cout << "Processing order: " << orderData << endl;
        database->saveOrder(orderData); // Use abstraction
    }
};

//  Main - show DIP in action
int main() {
    // You can choose any database at runtime!
    IDatabase* db1 = new MySQLDatabase();   // base class can point to derived class
    OrderService service1(db1);
    service1.placeOrder("Order#123");

    IDatabase* db2 = new MongoDBDatabase();
    OrderService service2(db2);
    service2.placeOrder("Order#456");

    delete db1;
    delete db2;

    return 0;
}
