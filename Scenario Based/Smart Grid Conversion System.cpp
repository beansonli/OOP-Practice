/****************************
 * lemme try something
**Domain Scenario:** Smart Grid Energy Management

You are integrating a legacy analog power meter system with a new digital management dashboard.
1. Create a class `LegacyMeter` with a private float `voltage` and integer `id`.
2. Create a class `DigitalDashboard` that needs to read and process legacy data. Make `DigitalDashboard` a **Friend Class** to `LegacyMeter`.
3. **Data Conversion (Basic to User-Defined):** Provide a parameterized constructor in `LegacyMeter` so that a `float` implicitly converts to a `LegacyMeter` object.
4. **Data Conversion (User-Defined to Basic):** Overload the `operator float()` casting operator in `LegacyMeter` to return the `voltage`.
5. In `main()`, dynamically allocate an array of 5 `LegacyMeter` objects. Use the `this` pointer in a chained member function `LegacyMeter& setID(int)` to initialize them sequentially.
6. Pass the array to a `DigitalDashboard` method that calculates the total voltage using the overloaded typecast operator.

*******************************/

#include <iostream>
using namespace std;

int main(){

    return 0;
}