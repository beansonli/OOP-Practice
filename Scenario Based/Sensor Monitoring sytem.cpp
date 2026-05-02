/******************************************************************************
# Question 1 — Smart Sensor Monitoring System

Design an **abstract class `Sensor`**.

## Data Members
- int sensorID
- double currentValue
- static int sensorCounter

## Requirements
- Implement a constructor that assigns `sensorID` automatically using the static counter.
- Declare a **pure virtual function** `computeReading()`.
- Implement a **virtual destructor**.
- Implement a **static member function** `getTotalSensors()`.

## Derived Classes
- `TemperatureSensor`
- `PressureSensor`

Each class should:
- Override `computeReading()`
- Use **dynamic initialization** to set sensor values.

## Additional Requirements
- Implement a **friend function** `compareSensors(Sensor&, Sensor&)` that compares readings.
- Demonstrate **pointer to derived class objects stored in a base class pointer array**.
- Dynamically allocate sensors using `new`.

## In main()
- Create an array of `Sensor*`.
- Store objects of derived classes.
- Call `computeReading()` using **dynamic binding**.

*******************************************************************************/

#include <iostream>
using namespace std;

class Sensor{
    protected:
    int sensorID;
    double currentValue;
    static int sensorCount;
    
    public: 
    virtual double computeReading()=0;
    friend void compareSensors(Sensor&, Sensor&);
    
    Sensor(double value){
        ++sensorCount;
        sensorID=sensorCount;
        currentValue=value;
    }
    
    virtual ~Sensor(){
        cout<<"Sensor destructor called!"<<endl;
    }
    
    static int getTotalSensors(){
        return sensorCount;
    }
};

int Sensor::sensorCount=0;

void compareSensors(Sensor& s1, Sensor& s2){
    if(s1.computeReading()> s2.computeReading())
        cout<<"\nSensor "<<s1.sensorID<<" has greater readings!"<<endl;
    else
        cout<<"\nSensor "<<s2.sensorID<<" has greater readings!"<<endl;
}

class TemperatureSensor: public Sensor{
    public:
    TemperatureSensor(double value): Sensor(value){};

    
    double computeReading() override{
        return currentValue;
    }
};

class PressureSensor:  public Sensor{
    public:
    
    PressureSensor(double value): Sensor(value){};

    
    double computeReading() override{
        return currentValue;
    }
};


int main()
{
    int t, p;
    cout<<"Enter no. of temperature sensors: ";
    cin>>t;
    cout<<"Enter no. of pressure sensors: ";
    cin>>p;
    
    Sensor* tempSensors[t];
    Sensor* presSensors[p];
    double val;
    
    for(int i=0; i<t; i++){
        cout<<"Enter temp sensor "<<i+1<<" reading: ";
        cin>>val;
        tempSensors[i] = new TemperatureSensor(val);
    }
    
    for(int i=0; i<p; i++){
        cout<<"Enter pressure sensor "<<i+1<<" reading: ";
        cin>>val;
        presSensors[i] = new PressureSensor(val);
    }
    
    compareSensors(*tempSensors[1], *tempSensors[2]);
    compareSensors(*presSensors[1], *presSensors[2]);
    
    cout<<"\nTotal sensors: "<<Sensor::getTotalSensors()<<endl;
    
    for(int i=0; i<t; i++)
       delete tempSensors[i];
    
    
    for(int i=0; i<p; i++)
        delete presSensors[i];
    
    
    return 0;
}
