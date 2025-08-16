#include <iostream>
#include <string>
#include<vector>

using namespace std;

//burger factory creates the objects for client 

class Burger{
     public:
     virtual void prepare()=0;
};

class SimpleBurger:public Burger{
     public:
     void prepare()override{
          cout << "simple burger prepared "<<endl;
          return;
     }
};
class StandardBurger:public Burger{
     public:
     void prepare()override{
          cout<<"Standard Burger prepared"<<endl;
     }
};
class PremiumBurger:public Burger{
     public:
     void prepare()override{
          cout<<"Premium Burger prepared"<<endl;
     };
};

class Burgerfactory{
public:
     Burger* prepareBurger(string burgerType){
          if(burgerType=="simple"){
               return new SimpleBurger();
          }
          else if(burgerType=="standard"){
               return new StandardBurger();
          }
          else if(burgerType=="premium"){
               return new PremiumBurger();
          }
          cout<<"Invalid Burger Type";
          return nullptr;
     }
};

int main(){
     Burgerfactory * factory=new Burgerfactory();
     Burger* myBurger=factory->prepareBurger("simple");
     myBurger->prepare();

     return 0;
}