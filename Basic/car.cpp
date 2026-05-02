/******************************************************************************
Design a Car class with private attributes, speed, and fuel, and
implement a constructor that uses this pointer to initialize these
attributes. Develop all the necessary methods required to display
the details.

*******************************************************************************/

#include <iostream>
using namespace std;

class Car{
    float speed;
    int fuel;
    
    public:
    Car(float s, int f){
        fuel=f;
        speed=s;
    }
    
    void getSpeed()
    {  cout<<"Speed of the car is "<<speed<<" km/hr.\n"; }
    
    void getFuel()
    {   cout<<"Fuel in car is "<<fuel<<"%.\n"; }
};


int main()
{
    Car bmw(20,40);
    Car wagonR(1,15);
    
    bmw.getSpeed();
    wagonR.getFuel();
    

    return 0;
}
