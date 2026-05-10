/****************************************
**Domain Scenario:** High-Frequency Trading & Asset Management

**The Scenario:**
You are building the core memory-safe trading engine for a hedge fund.
It needs to handle complex financial derivatives, execute math at high speeds, and manage dynamically allocated trade logs without crashing.

**Your Tasks:**
1. **The Diamond Architecture (Inheritance):**
   - Create a base class `FinancialAsset` with a protected `double baseValue`.
   - Derive two classes from it: `Stock` and `Option`. 
   - Create a fourth class `ConvertibleBond` that inherits from *both* `Stock` and `Option` (Hybrid Inheritance). 
   - **CRITICAL:** Use the correct C++ keyword during inheritance to resolve the Diamond Problem, ensuring `ConvertibleBond` only has *one* copy of `baseValue`.

2. **The Portfolio Container (Templates & Dynamic Memory):**
   - Create a class template `TradeLog<T>`, where `T` is the type of asset being logged.
   - It must contain a dynamically allocated array `T* transactions` and an integer `logSize`.
   - Implement the **Rule of Three**: Write a parameterised constructor, 
     a deep copy constructor (to prevent shallow copy crashes when portfolios are passed by value), and a Destructor to free the array.

3. **High-Speed Math (Operator Overloading & Inline):**
   - Inside `TradeLog<T>`, overload the binary `+` operator as a member function so you can combine two trade logs (e.g., `log3 = log1 + log2`).
     It should return a new `TradeLog` object with a combined size and copied data.
   - Create an `inline` function `applyMarketShock(double percentage)` that rapidly reduces the value of all transactions in the log.
   - Overload the `<<` operator using a **Friend Function** so you can easily print a `TradeLog` object using `cout << myLog;`.

4. **Data Conversion:**
   - In the `FinancialAsset` class, implement a Basic-to-User-Defined conversion constructor so that a `double` (representing raw cash) can implicitly convert into a `FinancialAsset` object.
   - Implement a User-Defined-to-Basic conversion operator (e.g., `operator double()`) that extracts and returns the `baseValue` so the object can be used directly in standard math equations.

5. **The Simulation (`main`):**
   - Instantiate a `TradeLog<double>` to test the template with basic types.
   - Instantiate a `TradeLog<ConvertibleBond>` to test the template with your complex hybrid class. 
   - Pass one of the logs to a function *by value* to prove your copy constructor works, and print the log using your overloaded `<<` friend function.
******************************************************/

#include <iostream>
using namespace std;

class FinancialAsset{
   protected:
      double baseValue;
   
   public:
      FinancialAsset(double cashValue) : baseValue(cashValue) {}

      operator double(){
         return baseValue;
      }
};

class Stock : virtual public FinancialAsset{

};

class Option : virtual public FinancialAsset{

};

class ConvertibleBond : public Stock,  public Option{

};

template <typename T>
class TradeLog{
   private:
      T assetType;
      int logSize;
      T* transactions = new T[logSize];

   public:
      TradeLog(T logValue,  int size, T* transaction[]) : assetType(logValue), logSize(size){
         for(int i=0 ; i<size; i++)
            this->transactions[i] = transaction[i];
      }

      TradeLog(const TradeLog& log){
         this->assetType = log.assetType;
         this->logSize = log.logSize;
         this->transactions = new T[log.logSize];

         for(int i = 0; i< log.logSize ; i++)   this->transactions[i] = log.transactions[i];        
      }

      TradeLog& operator + (const TradeLog& logObj){
         int newSize =  this->logSize + logObj.logSize ;
         T newTransactions[newSize];

         for(int i = 0; i< this->logSize ; i++){ newTransactions[i] = this->transactions[i]; }
         for(int i = this->logSize -1 ; i < logObj.logSize ; i++){ newTransactions[i] = logObj.transactions[i]; }

         return TradeLog( (this->assetType + "-" + logObj.assetType), newSize , newTransactions );
      }

      inline void applyMarketShock(double percentage){
         for(int i=0 ; i<logSize; i++)
            this->transactions[i] -= (percentage/100)*transactions[i];
      }

      ~TradeLog(){
         cout<<"> Deleting all transactions!\n";
         delete[] transactions;
      }

      friend ostream& operator << (ostream& , const TradeLog&);
};

template <typename T>
ostream& operator << (ostream& stream , const TradeLog<T>& log){
   stream<<"\n[Asset Type: ]"<<log.assetType;
   stream<<"\n[Transactions Associated: ]\n";

   for(int i= 0; i< log.logSize; i++)
      stream<<log.transactions[i]<<endl;

   return stream;
}

int main(){
   double transacts[] ={120, 10.25, 45.67, 90.4667, 140};
   double value = 2100.4;
   TradeLog<double> log1(value, 5, transacts);
   TradeLog<ConvertibleBond> bond();


   return 0;
}