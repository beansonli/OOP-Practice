/*************************************
**Domain Scenario:** High-Performance Game Physics Engine

**The Scenario:**
You are developing a core physics engine for a simulation software. The engine needs to manage "Entities" (particles or objects) that have dynamic properties. Because performance is critical, some calculations must be inline, and because memory is shared, you must ensure that cloning an entity doesn't lead to "Dangling Pointers" or "Double Free" crashes.

**Your Tasks:**

1.  **The PhysicsEntity Class:**
    *   Create a class `PhysicsEntity` with a private `double* velocity` (this must be dynamically allocated in the constructor to hold a single double value).
    *   Implement a `static int entityCount` that tracks the total number of `PhysicsEntity` objects currently alive in memory.
    *   **The Rule of Three:** Implement a **Destructor**, a **Deep Copy Constructor**, and a **Deep Assignment Operator** (`operator=`). The copy operations must allocate new memory and copy the value, not just the pointer address.
    *   Include an `inline` function `void applyImpulse(double force)` that adds the force to the velocity.

2.  **The Entity Manager (Templates):**
    *   Create a **Class Template** `EntityManager<T, int Capacity>` where `Capacity` is a non-type template parameter.
    *   The manager should contain an array of type `T` of size `Capacity`.
    *   Implement a function `void setEntity(int index, T item)` to store an entity.
    *   **Function Template Overloading:** Outside the class, write a function template `printStatus<T>(T& entity)` that is overloaded specifically for `PhysicsEntity` to print the velocity and the current `entityCount`.

3.  **The Implementation Task (main):**
    *   Instantiate an `EntityManager<PhysicsEntity, 2>`.
    *   Create one `PhysicsEntity` (e.g., `e1`) with a velocity of `10.5`.
    *   Use the **Assignment Operator** to create a clone: `PhysicsEntity e2 = e1;`.
    *   Modify the velocity of `e1`. Prove that `e2` remains unchanged (demonstrating a successful deep copy).
    *   Store both in your `EntityManager`.
    *   Print the `static entityCount` to show that the engine correctly tracks all active entities.

**************************************/
#include <iostream>
using namespace std;

class Robot{

};

class AerialDrone : public Robot{
    
}

int main(){

    return 0;
}