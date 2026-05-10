/****************************************
**Domain Scenario:** Aerospace Telemetry & Fleet Tracking

**The Scenario:**
You are the lead software engineer for a satellite communications company.
You need to build a system that tracks different types of aerospace vehicles, processes their telemetry data, and calculates their orbital stability.

**Your Tasks:**
1. **The Base Architecture:** Create an abstract base class `AerospaceVehicle`. 
   - It must have a `protected` string `callsign` and a `double altitude`.
   - Include a `static int activeConnections` that increments when a vehicle is created and decrements when destroyed. Include a `static` member function to return this count.
   - Declare a pure virtual function `double calculateSignalStrength()`.
   - **CRITICAL:** Implement a virtual destructor that prints `"Link severed for [callsign]"`.

2. **The Fleet (Derived Classes):** 
   - Create two derived classes: `LowEarthSatellite` and `DeepSpaceProbe`.
   - Provide overloaded constructors for both to initialize their specific data (e.g., `probeType` or `orbitVelocity`) alongside the base class data using constructor chaining.
   - Override `calculateSignalStrength()` in both classes. For the probe, if the `altitude` exceeds 10^8 km, throw a custom exception object of type `TelemetryLostException` (derived from `std::exception`).

3. **The Control Center (STL & Polymorphism):**
   - In `main()`, create a `std::vector<AerospaceVehicle*>` to act as your fleet tracker.
   - Dynamically allocate at least 2 satellites and 2 probes and push them into the vector.
   - Use an STL **Iterator** (not a standard `for` loop) to traverse the vector. For each vehicle, print its signal strength using the polymorphic function.
   - Wrap the loop in a `try-catch` block. If a `TelemetryLostException` is caught, print a red-alert warning, but *continue* processing the rest of the vector.
   - Finally, delete all objects in the vector to trigger the virtual destructors and prevent memory leaks. Print the final `activeConnections` count (it should be 0).
******************************************************/

#include <iostream>
#include <exception>
#include <vector>
#include <cmath>
using namespace std;

class TelemetryLostException : public exception{
   private:
      string message;
   
   public:
      TelemetryLostException(string msg): message(msg){}

      const char* what() const throw() override{
         return message.c_str();
      }
};

class AerospaceVehicle{
   protected:
      string callsign;
      double altitude;
      static int activeConnections;

   public:
      AerospaceVehicle(string sign, double altitude){
         this->callsign = sign;
         this->altitude = altitude;
         activeConnections++;
      }

      static int getActiveConnections(){
         return activeConnections;
      }

      virtual double calculateSignalStrength()=0;

      virtual ~AerospaceVehicle(){
         cout<<"Link severed for "<<callsign<<endl;
         activeConnections--;
      }

};

int AerospaceVehicle::activeConnections = 0 ;

class LowEarthSatellite : virtual public AerospaceVehicle{
   private:
      double orbitVelocity;

   public:
      LowEarthSatellite(double velocity, string callsign, double altitude) : AerospaceVehicle(callsign , altitude){
         this->orbitVelocity = velocity;
      }

      double calculateSignalStrength() override{
         return orbitVelocity/altitude ; //some assumptions upon return statements
      }
};

class DeepSpaceProbe : virtual public AerospaceVehicle{
   private:
      double probeType;

   public:
      DeepSpaceProbe(double type, string callsign, double altitude) : AerospaceVehicle(callsign , altitude){
         this->probeType = type;
      }

      double calculateSignalStrength() override{
         if(altitude > pow( 10 , 8 ) )
            throw TelemetryLostException("Lost connection!");

         return altitude/probeType ;
      }
};


int main(){
   vector<AerospaceVehicle*> vehicles;
   LowEarthSatellite* sat1 = new LowEarthSatellite(1200.54, "Angel Dart", 4543.65);
   LowEarthSatellite* sat2 = new LowEarthSatellite(221.3, "NASCAR xx", 154700.65);

   DeepSpaceProbe* probe1 = new DeepSpaceProbe(150, "Scrumer", 34564543.65);
   DeepSpaceProbe* probe2 = new DeepSpaceProbe(600.5, "Rovert", 104434543.65);

   vehicles.push_back(sat1);
   vehicles.push_back(sat2);
   vehicles.push_back(probe1);
   vehicles.push_back(probe2);

   vector<AerospaceVehicle*>::iterator i;
   try{
      for(i = vehicles.begin(); i!= vehicles.end(); ++i){
         cout<<(*i)->calculateSignalStrength()<<endl;
      }
   }
   catch(TelemetryLostException& e){
      cout<<"Error: "<<e.what()<<endl;
   }

   for(i = vehicles.begin(); i!= vehicles.end(); ++i){
         delete *i;
   }

   cout<<"Active Connections: "<<AerospaceVehicle::getActiveConnections()<<endl;

   return 0;
}