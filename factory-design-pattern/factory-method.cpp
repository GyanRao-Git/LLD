#include <iostream>
#include <string>
#include<vector>

using namespace std;

//same as simple factory but there are two factories 
//singhburger- creates same basic,standard,premium
//kingburger- creates wheat version of basic , std, premium
// solution: abstract the factory clas and make two concrete factories whom client can call to choose his type

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

class SimpleWheatBurger:public Burger{
     public:
     void prepare()override{
          cout << "Simple WheatBurger  prepared "<<endl;
          return;
     }
};
class StandardWheatBurger:public Burger{
     public:
     void prepare()override{
          cout << "standard WheatBurger  prepared "<<endl;
          return;
     }
};
class PremiumWheatBurger:public Burger{
     public:
     void prepare()override{
          cout << "Premium WheatBurger  prepared "<<endl;
          return;
     }
};

// abstract class for burger factory
class Burgerfactory{
public:
     virtual Burger* prepareBurger(string burgerType)=0;
};

class SinghBurger: public Burgerfactory{
     Burger* prepareBurger(string burgerType) override{
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
class KingBurger: public Burgerfactory{
     Burger* prepareBurger(string burgerType) override{
          if(burgerType=="simple"){
               return new SimpleWheatBurger();
          }
          else if(burgerType=="standard"){
               return new StandardWheatBurger();
          }
          else if(burgerType=="premium"){
               return new PremiumWheatBurger();
          }
          cout<<"Invalid Burger Type";
          return nullptr;
     }
};


int main(){
     Burgerfactory * factory=new KingBurger();
     Burger* myBurger=factory->prepareBurger("simple");
     myBurger->prepare();

     return 0;
}