#include <iostream>
#include<vector>
#include <string>
using namespace std;

//A class should do only one thing — it should have one responsibility or one job.


/*   1. Product class

     Responsibility: Represents a product (with name and price).

     SRP Role: Only holds product data — no unrelated logic.

     2. ShoppingCart class

     Responsibility: Manages a collection of Products.

     Methods:

     addProduct() → adds a product to the cart.

     getProduct() → returns the list of products (read-only).

     calcTotalPrice() → calculates total cost of products.

     SRP Role: Handles only cart operations (not display/printing).

     3. ShoppingCartPrinter class

     Responsibility: Prints the cart’s contents (invoice).

     Uses the ShoppingCart object to access products.

     SRP Role: Handles only presentation/printing logic.

*/


class Product{
public:
     double price;
     std::string name;

     Product(string name, double price){
          this->name=name;
          this->price=price;
     }

};

class ShoppingCart{
private:
     vector<Product*> products; //shopping cart (has a) relationship with product (1:M)
public:

     void addProduct(Product * p){ //setter
          products.push_back(p);
     }

     const vector<Product*> & getProduct(){ // returns a reference to the member but const so it cannot be modified
          return products;
     }

     double calcTotalPrice(){
          double total;
          for(auto p:products){ 
               total += p->price;
          }
          return total;
     }
};

class ShoppingCartPrinter{
private:
     ShoppingCart * cart=nullptr;
public:
     ShoppingCartPrinter(ShoppingCart * cart){
          this->cart=cart;
     }
     
     void printInvoice(){
          const vector<Product*>&products=cart->getProduct();
          for(auto i:products){
               cout << i->name << " " << i->price << "\n";
          }
     }
};

int main(){
     ShoppingCart * sc=new ShoppingCart(); 

     sc->addProduct(new Product("atta", 100));
     sc->addProduct(new Product("maida", 200));

     cout<<"Total price = "<<sc->calcTotalPrice()<<'\n';

     ShoppingCartPrinter *cart= new ShoppingCartPrinter(sc);
     cart->printInvoice();
}
