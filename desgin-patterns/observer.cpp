#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    Observer -> Pattern used when one object changes and many objects need update

    Subject keeps a list of observers

    Observers subscribe using attach() and unsubscribe using detach()

    When subject changes, it calls notifyObservers()

    Subject does not care what observers do after update

    Interview signal:
        notify, subscribe, event, listener, update many components

    Examples:
        stock price update, order placed event, notification service, UI listeners

*/

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(string symbol, double price) = 0;
};

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

class Stock : public Subject {
private:
    vector<Observer*> observers;
    string symbol;
    double price = 0.0;

public:
    Stock(string symbol) : symbol(symbol) {}

    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void setPrice(double newPrice) {
        price = newPrice;
        notifyObservers(); // state changed, tell all subscribers
    }

    void notifyObservers() override {
        for (Observer* observer : observers) {
            observer->update(symbol, price);
        }
    }
};

class PriceDisplay : public Observer {
public:
    void update(string symbol, double price) override {
        cout << "Display updated: " << symbol << " = " << price << "\n";
    }
};

class PriceAlert : public Observer {
private:
    double threshold;

public:
    PriceAlert(double threshold) : threshold(threshold) {}

    void update(string symbol, double price) override {
        if (price > threshold) {
            cout << "Alert! " << symbol << " crossed " << threshold << "\n";
        }
    }
};

// Usage
// int main() {
//     Stock stock("AAPL");
//
//     PriceDisplay display;
//     PriceAlert alert(150.00);
//
//     stock.attach(&display);
//     stock.attach(&alert);
//
//     stock.setPrice(145.00);
//     stock.setPrice(155.00);
//
//     return 0;
// }

/*
    Simple: subject has a vector of observers and for an update it calls .notify in all
    Flow:
        Stock is subject / publisher
        PriceDisplay and PriceAlert are observers / subscribers
        Observers attach themselves to stock
        Stock price changes, so stock calls notifyObservers()
        notifyObservers() calls update() on every observer

    Benefit:
        To add EmailAlert, create new observer class and attach it
        Stock class does not need to know about EmailAlert

    Note:
        In production C++, prefer smart pointers or clear ownership rules
        Here raw pointers are used only to keep interview notes simple

    EOF
*/
