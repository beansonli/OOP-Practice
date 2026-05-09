/*************************************
**Domain Scenario:** High-Performance Game Physics Engine

**The Scenario:**
You are developing a core physics engine for a simulation software. 
The engine needs to manage "Entities" (particles or objects) that have dynamic properties. 
Because performance is critical, some calculations must be inline, and because memory is shared, you must ensure that cloning an entity doesn't lead to "Dangling Pointers" or "Double Free" crashes.

**Your Tasks:**

1.  **The PhysicsEntity Class:**
    *   Create a class `PhysicsEntity` with a private `double* velocity` (this must be dynamically allocated in the constructor to hold a single double value).
    *   Implement a `static int entityCount` that tracks the total number of `PhysicsEntity` objects currently alive in memory.
    *   **The Rule of Three:** Implement a **Destructor**, a **Deep Copy Constructor**, and a **Deep Assignment Operator** (`operator=`).
    *   The copy operations must allocate new memory and copy the value, not just the pointer address.
    *   Include an `inline` function `void applyImpulse(double force)` that adds the force to the velocity.

2.  **The Entity Manager (Templates):**
    *   Create a **Class Template** `EntityManager<T, int Capacity>` where `Capacity` is a non-type template parameter.
    *   The manager should contain an array of type `T` of size `Capacity`.
    *   Implement a function `void setEntity(int index, T item)` to store an entity.
    *   **Function Template Overloading:** Outside the class, write a function template `printStatus<T>(T& entity)` 
    *   that is overloaded specifically for `PhysicsEntity` to print the velocity and the current `entityCount`.

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

class PhysicsEntity;

template<typename T> void printStatus(T& entity){
    cout<<"\n> Entity active!\n";
};

void printStatus(PhysicsEntity& entity){
    // cout<<"> ID: "<<entity.getID()<<endl;
    // cout<<"> Velocity: "<<entity.getVelocity()<<endl;
}

template<typename T, int Capacity>
class EntityManager{
    private:
        T manager[Capacity];

    public:

        void setEntity(int index, T item){
            manager[index] = item;
        }

        friend void printStatus<T>(T& entity);

        ~EntityManager(){ cout<<"> Destroying entity!\n"; }
};

class PhysicsEntity{
    private:
        double* velocity;
        static int entityCount;
        int entityID;

    public:
        PhysicsEntity(double vel){
            velocity = new double(vel);
            entityID = entityCount++;
        }

        PhysicsEntity(const PhysicsEntity& obj){
            double* copyVelocity= new double(*(obj.velocity));
            this->velocity = copyVelocity;
            this->entityID = obj.entityID;
            entityCount++;
            delete copyVelocity;
        }

        PhysicsEntity& operator = (const PhysicsEntity& obj){
            PhysicsEntity temp(obj);
            return temp ;
        }

        inline void applyImpulse(double force){
            *velocity += force;
        }

        inline int getID(){
            return entityID;
        }

        inline double getVelocity(){
            return *velocity;
        }

        static int getTotalEntities(){
            return entityCount;
        }

        ~PhysicsEntity(){
            cout<<"> Destroying entity "<<entityID<<endl;
            //delete velocity;
        }

        friend void printStatus(PhysicsEntity&);

};

int PhysicsEntity::entityCount = 0;


int main(){

    //EntityManager<PhysicsEntity, 2> obj1;
    PhysicsEntity e1(10.5);
    PhysicsEntity e2 = e1;

    e1.applyImpulse(70);

    printStatus(e1);
    printStatus(e2);

    // entity.setEntity(0, e1);
    // entity.setEntity(1, e2);

    cout<<"> Total Entity Count: "<<PhysicsEntity::getTotalEntities()<<endl;

    return 0;
}