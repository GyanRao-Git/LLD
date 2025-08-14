// Subclass should be subsitutable for base class

#include <iostream>
#include <vector>
#include <string>
using namespace std;



class NonWithdrawAbleAcc{

public:
     virtual double getBalance()=0;
     virtual void deposit(int amount)=0;
     
};

class WithdrawAbleAccount: public NonWithdrawAbleAcc{
     public:
     virtual string withdraw (int amount)=0;

};

class SavingsAcc: public WithdrawAbleAccount{
private:
     double balance;
     int accountNumber;

public:
     SavingsAcc(){
          this->balance=0;
          this->accountNumber= rand() % 1000;
     }
     public:
     void deposit(int amount){
          balance+=amount;
     }
     string withdraw(int amount){
          if(amount>balance) return "insufficient balance";
          else{
               balance-=amount;
               return "withdraw sucessfull";
          }
     }
};
class CurrentAcc: public WithdrawAbleAccount{
private:
     double balance;
     int accountNumber;

public:
     CurrentAcc(){
          this->balance=0;
          this->accountNumber= rand() % 1000;
     }
     public:
     void deposit(int amount){
          balance+=amount;
     }
     string withdraw(int amount){
          if(amount>balance) return "insufficient balance";
          else{
               balance-=amount;
               return "withdraw sucessfull";
          }
     }
};
class FixedDepositAcc: public NonWithdrawAbleAcc{
private:
     double balance;
     int accountNumber;

public:
     FixedDepositAcc(){
          this->balance=0;
          this->accountNumber= rand() % 1000;
     }
     public:
     void deposit(int amount){
          balance+=amount;
     }
};

class BankClient{
     private: 
     vector<WithdrawAbleAccount*> withdrawAcc;
     vector<NonWithdrawAbleAcc *> depAcc;

     public:
     BankClient(vector<WithdrawAbleAccount*> withdrawAcc, vector<NonWithdrawAbleAcc *> depAcc){
          this->withdrawAcc = withdrawAcc;
          this->depAcc = depAcc;
     }
};
