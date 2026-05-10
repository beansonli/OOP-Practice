/********************************************
**Domain Scenario:** Financial Technology (Hedge Fund Trading)

**The Scenario:**
You are building a secure transaction logger for a trading desk. The system must handle currency conversions and ensure that invalid trades (like negative amounts) are caught before they hit the ledger.

**Your Tasks:**

1.  **The Transaction Class:**
    *   Create a class `Transaction` with private members `double amount` and `string currencyCode`.
    *   **Data Conversion (Basic to User-Defined):** Implement a constructor that allows a `double` to be implicitly converted into a `Transaction` (assuming a default currency of "USD").
    *   **Data Conversion (User-Defined to Basic):** Overload the `operator double()` to return the `amount` so a `Transaction` object can be used in direct mathematical additions.
    *   **Binary Operator Overloading:** Overload the `+` operator (member function) to add the amounts of two `Transaction` objects.

2.  **The Secure Ledger (Friendship & Exceptions):**
    *   Create a class `Ledger`. Make it a **Friend Class** of `Transaction`.
    *   In `Ledger`, implement a function `void post(Transaction t)`.
    *   **Exception Handling:** Inside `post()`, if the `Transaction` amount is less than or equal to 0, `throw` a custom exception object `InvalidTradeException`.
    *   Overload the `<<` operator as a **Friend Function** of `Transaction` to print the amount and currency formatted as `[USD: 500.00]`.

3.  **The Implementation Task (main):**
    *   Create a `Ledger` object.
    *   Attempt to create a `Transaction` using a simple `double` (e.g., `Transaction t = 500.50;`).
    *   Try to `post()` a transaction with a negative value inside a `try-catch` block. Catch the `InvalidTradeException` and print an error message.
    *   Demonstrate the `operator double()` by adding a `Transaction` object to a local `double` variable and printing the result.
*********************************************/

#include <iostream>
#include <exception>
using namespace std;

class Ledger;

class InvalidTradeException : public exception{
    string message;
    public:
        InvalidTradeException(string msg) : message(msg){}

        string getException(){
            return message;
        }
};

class Transaction{
    private:
        string currencyCode;
        double amount;

    public:
        Transaction(double val) : amount(val),  currencyCode("USD"){}

        operator double(){
            return amount;
        }

        Transaction operator + (const Transaction& obj){
            return Transaction(this->amount + obj.amount);
        }
        
        friend class Ledger;
        friend ostream& operator << (ostream& , const Transaction&);
};

ostream& operator << (ostream& stream , const Transaction& transact){
    stream << "[ " << transact.currencyCode << ": "<<transact.amount <<" ]" << endl;
    return stream;
}

class Ledger{

    public:
        void post(Transaction t){
            if(t.amount <=0) 
                throw InvalidTradeException("Trade amount must be positive!");
            
            cout<<"Posting transacted amount: "<<t.amount<<endl;
        }
};

int main(){

    Transaction t1 = 500.50, t2 = 600.10, t3 = t1+t2, t4 = -100;

    double value =t1;
    cout<<"Amount passed to object 1: "<<value<<endl;
    
    cout<<t1<<t2<<t3;
    Ledger ledge;
    try{
        ledge.post(t1);
        ledge.post(t4);
    }
    catch(InvalidTradeException exObject){
        cout<<"Exception: "<<exObject.getException()<<endl;
    }
    
    return 0;
}