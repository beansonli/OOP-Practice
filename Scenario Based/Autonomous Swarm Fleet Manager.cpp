/************************************************************
# CHALLENGE 03: The Autonomous Swarm Fleet Manager

## Scenario
You are designing the fleet management software for a swarm of autonomous warehouse robots. The system handles UAVs (Drones) and AGVs (Ground Vehicles) through a unified polymorphic interface.

## Core Requirements
1. **Strict Inheritance & Polymorphism:**
   - Base Class: `Robot`.
   - Derived Classes: `UAV` and `AGV`.
   - Use **Protected Inheritance** for a class `InternalCircuitry` that provides low-level motor methods to the `Robot` class but hides them from the `main()` function.
   - Implement **Virtual Functions** for `calculatePath()` and a **Pure Virtual Function** for `identifyType()`.

2. **Object Lifecycle & Chaining:**
   - Use **Constructor Overloading** to handle robots with varying battery capacities.
   - Demonstrate **Constructor Chaining** (passing arguments from derived to base constructor).
   - **CRITICAL:** Implement a **Virtual Destructor** in the base class and prove its necessity by deleting a derived object via a base pointer.

3. **Pointers & Identity:**
   - Use a `static` data member to assign a unique, auto-incrementing **Serial Number** to every robot created.
   - Implement an **Array of Pointers to Objects** to manage the fleet.
   - Use the `this` pointer to return a reference to the current object for **Method Chaining** (e.g., `myRobot.setSpeed(10).setTarget(x, y);`).

4. **Friendship & Operators:**
   - Create a **Friend Function** `void emergencyBypass(Robot& r)` that can modify private emergency flags.
   - Overload **Relational Operators** (`==` and `>`) to compare two robots based on their remaining battery life.

## The Implementation Task
Write a program that:
1. Creates a `std::vector` or a raw array of `Robot*`.
2. Populates it with a mix of `UAV` and `AGV` objects.
3. Sorts the robots using your overloaded `>` operator.
4. Iterates through the fleet and calls the polymorphic `calculatePath()` function.
5. Deletes the entire fleet, ensuring no memory leaks occur.

************************************************************/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Robot{
   protected:
      static int count;
      int serialNo;
      float batteryCapacity;
      double Xcoord=0 , Ycoord=0, speed=0;

   protected:
      void control(){
         cout<<"Control activated!\n";
      }

      void increaseCapacity(float incrementValue){
         this->batteryCapacity += incrementValue;
      }

   public:
      // constructor overloading for varying battery capacities
      Robot(float capacity){
         count++;
         this->serialNo = count;
         this->batteryCapacity = (float)capacity;
      }

      Robot(int capacity){
         count++;
         this->serialNo = count;
         this->batteryCapacity = float(capacity);
      }

      Robot() = delete;

	   friend void emergencyBypass(Robot&);

      virtual void identifyType()=0;

      virtual void calculatePath(float , float){
         cout << ">> Generic path calculation." << endl;
      }

      Robot* setSpeed(double speed = 0){
         this->speed = speed;

         return this;
      }

      void setTarget(double x=0, double y=0){
         this->Xcoord =x;
         this->Ycoord = y;
      }

      bool operator ==(const Robot& r){
         if(this->batteryCapacity == r.batteryCapacity)
	         return true;
         else
            return false;
	   }

      bool operator > (const Robot& r) const {
         return this->batteryCapacity > r.batteryCapacity;
      }

      virtual void displayInfo(){
         cout<<"> Serial No.: "<<serialNo<<endl;
         cout<<"> Battery Capacity: "<<this->batteryCapacity<<endl;
      }

      virtual ~Robot(){
         cout<<"\n>> Robot removed succeessfully!\n";
      }


};
int Robot::count=0;

void emergencyBypass(Robot& r){
	cout<<"\n****Implementing Emergency measures!****\n";
	cout<<">> Shuting down Robot!\n";
	r.batteryCapacity =0.0;
	r.setSpeed(0.0);

}

class AGV : public Robot{
   private:
      float wheelFriction; 
      int loadWeight;

   public:

      AGV(float capacity) : Robot(capacity){
         this->batteryCapacity = capacity;
         loadWeight = 1000;
         wheelFriction =0.2;
      }


      void identifyType() override{
            cout<<">> Robot Type: AGV\n";
      }

      void calculatePath(float targetX, float targetY) override{
         double D = abs(targetX - Xcoord) + abs(targetY - Ycoord);
         cout<<"> Calculated path distance: "<<D<<endl;
      }
      void displayInfo() override{
         cout<<"> Serial No.: "<<serialNo<<endl;
         cout<<"> Battery Capacity: "<<this->batteryCapacity<<endl;
         identifyType();
         cout<<"> Load Weight(in grams): "<<loadWeight<<endl;
         cout<<"> Wheel Friction: "<<wheelFriction<<endl;
      }

      ~AGV(){
         cout<<"\n>> Destroying AGV with Serial Number: "<<serialNo<<endl;
      }
};

class UAV : public Robot{
   private:
      float altitude, rotorSpeed;

   public:

      UAV(float capacity) : Robot(capacity){
         this->batteryCapacity = capacity;
         Xcoord = Ycoord = 0;
         rotorSpeed = 10;
         altitude = 0.00;
      }

      void identifyType() override{
         cout<<">> Robot Type: UAV\n";
      }

      void calculatePath(float targetX, float targetY) override{
         double altitude = sqrt(pow((targetX - Xcoord), 2) + pow((targetY - Ycoord), 2) );
         cout<<"> Calculated path distance: "<<altitude<<endl;
      }

      void displayInfo() override{
         cout<<"> Serial No.: "<<serialNo<<endl;
         cout<<"> Battery Capacity: "<<this->batteryCapacity<<endl;
         identifyType();
         cout<<"> Rotor Speed: "<<rotorSpeed<<endl;
         cout<<"> Altitude reached: "<<altitude<<endl;
      }

      ~UAV(){
         cout<<"\n>> Destroying UAV with Serial Number: "<<serialNo<<endl;
      }
};

class InternalCircuitry : protected Robot{
   private:
      float motorEfficiency, batteryVoltage;

   public:
      InternalCircuitry(float battery, float efficency, float voltage): Robot(battery){
         this->batteryCapacity = battery;
         this->motorEfficiency = efficency;
         this->batteryVoltage = voltage;
      }

      void identifyType() override{
         cout<<">> Robot Type: Internal Circuitry (IC)\n";
      }

      void displayInfo() override{
         cout<<"> Serial No.: "<<serialNo<<endl;
         cout<<"> Battery Capacity: "<<this->batteryCapacity<<endl;
         identifyType();
         cout<<"> Battery voltage: "<<batteryVoltage<<endl;
         cout<<"> Motor Efficiency: "<<motorEfficiency<<endl;
      }

      ~InternalCircuitry(){
         cout<<"\n>> Destroying IC with Serial Number: "<<serialNo<<endl;
      }
};

int main(){
   
   Robot* myRobot = new UAV(54);
   Robot* myAgv = new AGV(89.01);
   vector<Robot*> robots(4);
   robots.at(0)= new AGV(90.23);
   robots.at(1) = new AGV(100.00);
   robots[2] = new UAV(18.210564);
   robots[3] = new UAV(24);

   if (myRobot > myAgv) myRobot->displayInfo();
   else myAgv->displayInfo();

   bool check = robots[2] == robots[3];
      if(check) cout<<"\n> Same Robots identified!\n";
      else cout<<"\n > NO same robots identified!\n";


   double testX =40.12;
   double testY = 90.1456;

   for (int i=0; i<robots.size() ;i++)
      robots[i]->calculatePath(testX , testY); //testing coordinates

   myRobot->setSpeed(10)->setTarget(45, 12);
   myRobot->displayInfo();
   emergencyBypass(*myRobot);

   for (int i=0; i<robots.size() ;i++){
      robots[i]->displayInfo();
      delete robots[i];
   }

   delete myRobot;
   delete myAgv;

   return 0;
}
