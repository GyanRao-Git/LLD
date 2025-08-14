// add new methods saveToMongo and saveToFile and to add we end up changing our save to db class
//violates open-close principle

//sol: create save to db as abstract class and override the save fn in other class making it open to expansion

/*
     NOTE: 
     persistence = abstract class
     mongoPersistence = inherited for mongo
     mysqlPersistence = inherited for mysql
     filePersistence = inherited for file

*/

#include <iostream>
#include<vector>
#include <string>
using namespace std;

class Product{
public:
     double price;
     string name;

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

class Persistence{  //abstract class with virtual fn
public:

     virtual void save(ShoppingCart * cart)=0;
};

class MongoPersistence: public Persistence { //inherited class with function override
public:
     void save(ShoppingCart * cart) override{
          cout<<"Saved to Mongo db "<<endl;
     }
};
class MysqlPersistence: public Persistence {
public:
     void save(ShoppingCart * cart) override{
          cout<<"Saved to Mysql "<<endl;
     }
};
class FilePersistence: public Persistence {
public:
     void save(ShoppingCart * cart) override{
          cout<<"Saved to File "<<endl;
     }
};



int main(){
     ShoppingCart * sc=new ShoppingCart(); 

     sc->addProduct(new Product("atta", 100));
     sc->addProduct(new Product("maida", 200));

     cout<<"Total price = "<<sc->calcTotalPrice()<<'\n';

     ShoppingCartPrinter *cart= new ShoppingCartPrinter(sc);
     cart->printInvoice();

     Persistence * mongoObject = new MongoPersistence();
     mongoObject->save(sc);
}
