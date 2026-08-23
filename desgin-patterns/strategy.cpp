#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

/*
    Strategy -> Pattern used when we have multiple ways to do same task

    Instead of many if else / switch cases, create separate classes for each logic

    Context class keeps a strategy object and delegates work to it

    We can change the strategy at runtime

    Interview signal:
        payment methods, pricing rules, sorting algorithms, route finding

    Easy line:
        Factory decides which object to create
        Strategy decides which behavior to use

    Avoid when there are only 1-2 simple cases and logic will not grow

*/

// PaymentStrategy -> Simpel Abstract class which pays
class PaymentStrategy {
public:
    virtual bool pay(double amount) = 0;
};

class CreditCardPayment : public PaymentStrategy {
private:
    string cardNumber;
public:
    CreditCardPayment(string cardNumber) : cardNumber(cardNumber) {}

    bool pay(double amount) override {
        // Credit card payment logic
        return true;
    }
};

class PayPalPayment : public PaymentStrategy {
private:
    string email;
public:
    PayPalPayment(string email) : email(email) {}

    bool pay(double amount) override {
        // PayPal payment logic
        return true;
    }
};

/*
    Two classes that are children of PaymentStrategy
*/

class ShoppingCart {
private:
    unique_ptr<PaymentStrategy> paymentStrategy;

public:
    void setPaymentStrategy(unique_ptr<PaymentStrategy> strategy) {
        paymentStrategy = move(strategy);
    }

    void checkout(double amount) {
        if (paymentStrategy == nullptr) {
            throw runtime_error("Payment strategy not selected");
        }

        paymentStrategy->pay(amount);
    }
};

// Usage
int main() {
    ShoppingCart cart;

    cart.setPaymentStrategy(make_unique<CreditCardPayment>("1234-5678"));
    cart.checkout(100.00);

    cart.setPaymentStrategy(make_unique<PayPalPayment>("user@example.com"));
    cart.checkout(50.00);

    return 0;
}

/*
    Flow:
        PaymentStrategy is base class / interface
        CreditCardPayment and PayPalPayment are concrete strategies

    ->  Main method takes in the object itself as an argument and then calls its method

        ShoppingCart does not care which payment logic is used
        It just calls paymentStrategy->pay(amount)

    Benefit:
        To add UPIPayment, create new class and set it
        ShoppingCart does not need new if else conditions

    EOF
*/
