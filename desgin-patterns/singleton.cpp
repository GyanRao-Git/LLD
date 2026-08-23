#include <string>

/*
    Singleton -> Pattern that makes sure only one object of a class exists

    Constructor is private, so outside code cannot create objects directly

    getInstance() gives access to the same single object every time

    Useful for shared resources like database connection, logger, config manager

    Copy constructor and assignment operator are deleted, so object cannot be copied

*/

class DatabaseConnection {
public:
static DatabaseConnection& getInstance() {
    static DatabaseConnection instance;
    return instance;
}

private:
    DatabaseConnection() = default;

    //deleting the copy constructor
    /*
        DatabaseConnection db1;
        DatabaseConnection db2 = db1; // error
    */
    DatabaseConnection(const DatabaseConnection&) = delete;

    //deleting copy assignment operator
    /*
        DatabaseConnection db1;
        DatabaseConnection db2;

        db2 = db1; // error
    */
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
};

// Usage
// auto& db = DatabaseConnection::getInstance();
// db.query("SELECT * FROM users");

