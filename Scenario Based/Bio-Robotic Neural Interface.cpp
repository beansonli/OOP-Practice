/******************************************************************************
# CHALLENGE 01: The Bio-Robotic Neural Interface

## Scenario
You are developing the control firmware for a high-precision robotic limb. The system must process sensor data in real-time while managing power across multiple joints.

## Core Requirements
1. **The Architecture (Inheritance & Diamond Problem):**
   - Create an abstract base class `HardwareComponent` with a pure virtual function `void initialize()`.
   - Use **Virtual Inheritance** to create two classes: `Sensor` and `Actuator`, both inheriting from `HardwareComponent`.
   - Create a derived class `NeuralJoint` that inherits from both `Sensor` and `Actuator`.

2. **Memory & Life Cycle:**
   - `NeuralJoint` must manage a dynamic array of `float` called `signalBuffer`.
   - Implement a **Parameterized Constructor** using the `this` pointer for initialization.
   - Implement a **Deep Copy Constructor** to ensure safe object duplication.
   - Implement a **Destructor** to prevent memory leaks.

3. **Static Logic & Protection:**
   - Use a `static` data member `totalPowerConsumption` to track power across all instances.
   - Implement a `static` member function to retrieve this value.
   - Use `const` member functions for any method that displays joint status.

4. **Operator Overloading & Friendship:**
   - Overload the `+` operator (Binary) to merge the `signalBuffer` of two `NeuralJoint` objects.
   - Overload the `[]` operator (Subscript) to access specific indices of the `signalBuffer`.
   - Create a **Friend Class** `Calibrator` that can access and modify the private `calibrationOffset` of `NeuralJoint`.

## The Implementation Task
Write a `main()` function that:
1. Creates an **Array of Pointers** to the base class `HardwareComponent`.
2. Dynamically allocates several `NeuralJoint` objects and stores them in the array.
3. Demonstrates **Runtime Polymorphism** by calling `initialize()` through the base pointers.
4. Returns a `NeuralJoint` object from a standalone function to test if your **Copy Constructor** correctly handles the return-by-value mechanism.

*******************************************************************************/

#include <iostream>
#define MAX_BUFFER 100
using namespace std;

class HardwareComponent{
   virtual void initialize()=0;
};

class Sensor : virtual public HardwareComponent{

};

class Actuator: virtual public HardwareComponent{

};

class Calibrator;

class NeuralJoint: public Sensor, public Actuator{
   private:
   float *signalBuffer = new float[MAX_BUFFER];
   int calibrationOffset, bufferSize;
   static double totalPowerConsumption;

   public:
   void initialize() override{

   }

   NeuralJoint(float buffer[],int bufferSize, int offset){
      this->bufferSize=bufferSize;
      calibrationOffset=offset;

      for(int i=0; i < bufferSize; i++){
         signalBuffer[i] = buffer[i];
      }

      totalPowerConsumption++;
   }

   NeuralJoint operator+(NeuralJoint& obj){
      int newBufferSize = bufferSize + obj.bufferSize ;
      float *newBuffer= new float[newBufferSize];

      for(int i=0; i < newBufferSize; i++){
         newBuffer[i] = signalBuffer[i] + obj.signalBuffer[i];
      }
      return NeuralJoint(newBuffer, newBufferSize, calibrationOffset + obj.calibrationOffset);

      delete[] newBuffer;
   }

   float operator [](const int& index){
      return signalBuffer[index];
   }

   const void status() const{
      cout<<"\n-----STATUS-------\n";
      cout<<"JOINT STATE: ";
   }

   static void getPowerConsumption(){
      cout<<"POWER CONSUMED: "<<totalPowerConsumption<<endl;
   }

   friend class Calibrator;

   ~NeuralJoint(){
      delete[] signalBuffer;
      cout<<"Freed memory by deleting obj ID: "<<endl;
   }
};

class Calibrator{
   public:
      void modifyCalibrationOffset(const int& newOffset, NeuralJoint& obj){
         obj.calibrationOffset+= newOffset;
      }
};

double NeuralJoint::totalPowerConsumption=0;

int main(){
    
    return 0;
}
