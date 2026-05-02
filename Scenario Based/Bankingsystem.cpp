/******************************************************************************
Multi-Level Banking System

Create:
- Base Class: Account
- accountNumber
- holderName
- balance
- virtual function calculateInterest() as a percentage of balance
- Constructor
- Virtual destructor

Derived Classes:
- SavingsAccount, gives positive interest
- CurrentAccount, may give lower or zero interest

Requirements:
- Override calculateInterest()
- Demonstrate constructor execution order
- Demonstrate destructor order
- Use protected inheritance in one derived class
- Create a function that takes base class reference and calls overridden function
- Use friend function with inheritance

Also: Show disadvantage of inheritance using an example in your explanation.

*******************************************************************************/

#include <iostream>
using namespace std;

class Account{
    protected:                  //cuz other classes have to access these members
    int accountNumber;
    string holderName;
    double balance;
    
    public:
    virtual void calculateInterest(){
        cout<<"\nBase Account Interest"<<endl;
    }
    
    Account(int accNo, string name, double amount){
        accountNumber = accNo;
        holderName = name;
        balance = amount;
        cout<<"Created account no: "<<accNo<<endl;
    }
    
    virtual ~Account(){
        cout<<"Deleting account no: "<<accountNumber<<endl;
    }
    
    friend void showInterest(Account &);
    
};

class SavingsAccount: public Account{
    public:
    SavingsAccount(int accNo, string name, double amount ): Account(accNo, name, amount){
        cout<<"\nSavings account "<<accNo<<" created!"<<endl;
    }
    
    ~SavingsAccount(){
        cout<<"\nSavings account "<<accountNumber<<" deleted!"<<endl;
    }
    
    void calculateInterest(){
        double interest = balance * 0.05;
        cout<<"Savings Account Interest: "<<interest<<endl;
    }
    
};

class CurrentAccount: protected Account{
    
    public:
    CurrentAccount(int accNo, string name, double amount): Account(accNo, name, amount){
        cout<<"\nCurrent account "<<accNo<<" created!"<<endl;
    }
    
    ~CurrentAccount(){
        cout<<"\nCurrent account "<<accountNumber<<" deleted!"<<endl;
    }
    
    void calculateInterest(){
        double interest = balance * 0.02;
        cout<<"Current Account Interest: "<<interest<<endl;
    }
    
    
};

void showInterest(Account& acc) {
    acc.calculateInterest();
}


int main()
{
    Account acc(17004, "juliana", 20000);   //single objects to test out
    SavingsAccount savings(1843, "juliana", 14489.25);
    CurrentAccount current(489, "juliana", 1800);
    
    showInterest(acc);
    savings.calculateInterest();
    current.calculateInterest();
//  showInterest(savings); doesn't work since friendship isn't inherited

    return 0;
}
