/****************************
**Domain Scenario:** Smart Grid Energy Management

You are integrating a legacy analog power meter system with a new digital management dashboard.
1. Create a class `LegacyMeter` with a private float `voltage` and integer `id`.
2. Create a class `DigitalDashboard` that needs to read and process legacy data. Make `DigitalDashboard` a **Friend Class** to `LegacyMeter`.
3. **Data Conversion (Basic to User-Defined):** Provide a parameterized constructor in `LegacyMeter` so that a `float` implicitly converts to a `LegacyMeter` object.
4. **Data Conversion (User-Defined to Basic):** Overload the `operator float()` casting operator in `LegacyMeter` to return the `voltage`.
5. In `main()`, dynamically allocate an array of 5 `LegacyMeter` objects. Use the `this` pointer in a 
   chained member function `LegacyMeter& setID(int)` to initialize them sequentially.
6. Pass the array to a `DigitalDashboard` method that calculates the total voltage using the overloaded typecast operator.

*******************************/

#include <iostream>
#define METER_SIZE 5
#define START 0
using namespace std;

class DigitalDashboard;

class LegacyMeter{
    private:
     int id;
     static int countID;
     float voltage;

    public:
    LegacyMeter(float voltage=0) {
        this->voltage = voltage;
        id = ++countID;
    }
    LegacyMeter() = delete;

    operator float() {
        return float(voltage);
    }

    LegacyMeter& setID(int id){
        this->id = id;
        return *(this+1);
    }

    ~LegacyMeter(){
        cout<<"** Destroying meter with ID: "<<id<<endl<<endl;
    }

    void displayReading(){
        cout<<"** Meter ID: "<<id<<endl;
        cout<<"** Voltage: "<<voltage<<endl;
    }

    friend class DigitalDashboard;
};
int LegacyMeter::countID = 0;

class DigitalDashboard{
    public:
    void totalVoltage(LegacyMeter meter[], int size){
        float total=0, sum=0;
        for(int i=0; i<size; i++){
           total = meter[i];
           sum += total;
        }

        cout<<"* Total Volatge Utilized: "<<sum<<endl;

    }

    ~DigitalDashboard(){
        cout<<"** Destroying dashboard! \n";
    }

};



int main(){
    LegacyMeter* meters=  new LegacyMeter[METER_SIZE];
    DigitalDashboard dashboard;

    for(int i=START; i<METER_SIZE; i++){
        float voltage;
        cout<<"Volatge of meter "<<i+1<<": ";
        cin>>voltage;
        meters[i] = float(voltage);
    }

    meters[START].setID(2).setID(40).setID(1).setID(90).setID(10);
    dashboard.totalVoltage(meters, METER_SIZE);

     for(int i=START; i<METER_SIZE; i++){
        meters[i].displayReading();
    }

    delete[] meters;
    
    return 0;
}