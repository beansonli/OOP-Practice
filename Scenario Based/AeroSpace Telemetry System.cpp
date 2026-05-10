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
using namespace std;

int main(){

    return 0;
}