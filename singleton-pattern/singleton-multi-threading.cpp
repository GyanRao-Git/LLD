     #include <iostream>
     #include <mutex>
     using namespace std;

     class Singleton{
     private:
          static Singleton* instance;
          static mutex singletonMutex;
          Singleton(){
               cout<<"constructor called"<<endl;
          }
     public:
          static Singleton * getInstance(){
               if(instance==nullptr){
                    std::lock_guard<mutex> createInstance(singletonMutex);
                    if(instance==nullptr){
                         instance = new Singleton();
                    }
               }
               return instance;
          }
     };

     Singleton * Singleton::instance=nullptr;
     std::mutex Singleton::singletonMutex;


     int main(){
          Singleton * s1= Singleton::getInstance();
          Singleton*s2=Singleton::getInstance();

          cout<< (s1==s2)<< endl;
     }