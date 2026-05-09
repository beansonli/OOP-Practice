/*************************************
**Domain Scenario:** Autonomous Systems (Robotics)

You are designing the architecture for an autonomous search-and-rescue fleet. 
1. Create an abstract base class `Robot` with a protected data member `batteryLevel` and a pure virtual function `void navigate()`.
2. Derive two classes from `Robot`: `AerialDrone` and `GroundRover`. Both should override `navigate()` 
to print specific movement logistics (e.g., "Flying at altitude", "Driving on terrain"). 
3. Create a fourth class `HybridTransformer` that inherits from BOTH `AerialDrone` and `GroundRover` (Hybrid Inheritance).
4. **The Challenge:** Resolve the ambiguity (Diamond Problem) introduced by this hierarchy. Ensure `HybridTransformer` has only one instance of `batteryLevel`.
5. In `main()`, create an array of `Robot*` pointers. Instantiate one `AerialDrone`, one `GroundRover`,
and one `HybridTransformer`. Loop through the array, calling `navigate()` on each to demonstrate Run-time Polymorphism.
Ensure no memory leaks occur when deleting the array.

**************************************/
#include <iostream>
using namespace std;

int main(){

    return 0;
}