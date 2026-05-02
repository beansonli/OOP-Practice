/******************************************************************************
Smart Parking System 

Design a system with:
> Class Vehicle (Abstract base class)
vehicleNumber
virtual calculateParkingFee() = 0

> Derived classes:
- Car
- Bike
- Truck
- Class ParkingLot

= static totalVehicles
= array of pointers to Vehicle
= friend function applyDiscount(Vehicle&, double)
= Destructor that clears memory

Requirements:
- Dynamic memory allocation
- Array of pointer to objects
- Static member tracking vehicles
- Returning objects from functions
- Passing objects as arguments
- Friend function
- Constructor overloading
- Copy constructor
- Destructor
- Namespace usage

*******************************************************************************/

#include <iostream>
using namespace std;

class Vehicle{
    protected:
    int vehicleNumber;
    double ParkingFee;
    
    public:

    virtual void calculateParkingFee()=0;
    virtual ~Vehicle(){};
    friend void applyDiscount(Vehicle& , double);
};

class Car: public Vehicle{
    string model;
    
    public:
    Car(int num, string Model):Vehicle(){
        vehicleNumber=num;
        model=Model;
    }
    
    ~Car(){
        cout<<"Car Destructor called!"<<endl;
    }
    
    void calculateParkingFee(){
        ParkingFee=30;
        cout<<"Car Parking: "<<ParkingFee<<endl;
    }
};

class Bike: public Vehicle{
    string model;
    
    public:
    Bike(int num, string Model):Vehicle(){
        vehicleNumber=num;
        model=Model;
    }
    
    ~Bike(){
        cout<<"Bike Destructor called!"<<endl;
    }
    
    void calculateParkingFee(){
        ParkingFee=10;
        cout<<"Bike Parking: "<<ParkingFee<<endl;
    }
    
};

class Truck: public Vehicle{
    string model;
    
    public:
    Truck(int num, string Model):Vehicle(){
        vehicleNumber=num;
        model=Model;
    }
    
    ~Truck(){
        cout<<"Truck Destructor called!"<<endl;
    }
    
    void calculateParkingFee(){
        ParkingFee=50;
        cout<<"Truck Parking: "<<ParkingFee<<endl;
    }
};

class ParkingLot{
    static int totalVehicles;
    
    public:
    
    ParkingLot(Vehicle & v){
        cout<<"Parked a vehicle!"<<endl;
        ++totalVehicles;
    }
    ~ParkingLot(){
        cout<<"Parking Lot object destroyed!"<<endl;
    }
    
    static int VehicleCount(){
        return totalVehicles;
    }
    
    
};

int ParkingLot::totalVehicles = 0;

void applyDiscount(Vehicle& v, double discount){
    v.ParkingFee -= v.ParkingFee *(discount/100.0);
    cout<<"\nDiscounted Fee: "<<v.ParkingFee<<endl;
}


int main()
{
    Vehicle* vehicles[4];
    
    vehicles[0] = new Car(111, "Maruti-Suzuki");
    vehicles[1]= new Bike(904,"KTM");
    vehicles[2]= new Truck(525, "Pickup-Truck");
    
    ParkingLot* parking[3];
    
    for(int i = 0; i < 3; i++){
        vehicles[i]->calculateParkingFee();
        parking[i] = new ParkingLot(*vehicles[i]);
        // Dynamic binding
    }
    
    for(int i = 0; i < 3; i++){
        applyDiscount(*vehicles[i],10);
        delete vehicles[i];
    }
        
    cout<<"\nTotal vehicles: "<<ParkingLot::VehicleCount()<<endl;

    return 0;
}
