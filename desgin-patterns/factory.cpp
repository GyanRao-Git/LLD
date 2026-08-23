#include <iostream>
#include <string>
#include <memory>

using namespace std;

/*
    Factory -> Pattern that controls how objects are created, hides creation logic

    Factory takes baseclass, calls .create() method and returns the object

    Example:

    Notification system -> can have email, sms, alert ...

    Notification factory -> returns a notification type object which can be its child

    Factory will have create method with a string argument, compares and creates

*/

// Base class
class Notification{
public:
    virtual ~Notification() = default; // Compiler default destructor
    virtual void send(string message) = 0;
};

class EmailNotification: Notification{
    void send(string message) override{/*Send Logic*/}
};

class SmsNotification: Notification{
    void send(string message) override{/*Send Logic*/}
};

class NotificationFactory{
public:
    // unique_ptr helps create smart pointer -> Object goes out of scope = delete
    static unique_ptr<Notification> create (string type){
        if (type == "email") return make_unique<Notification>();
        else if (type == "sms") return make_unique<Notification>();
        else{
            throw invalid_argument("Unknown type");
        }
    }
};

// Usage

int main(){

    auto sms = NotificationFactory::create("sms");
    sms->send("Hello");

    return 0;
}





