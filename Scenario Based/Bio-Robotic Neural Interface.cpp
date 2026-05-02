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
   public:
      virtual void initialize()=0;
      virtual ~HardwareComponent() { cout<<"Destroyed Component!\n"; }
};

class Sensor : virtual public HardwareComponent{
   private:
      float sensitivity;
      int samplingRate;

   public:

      inline void setSamplingRate(const int rate){
         samplingRate = rate;
      }

      inline void initialize() override{
         sensitivity = 0.00;
         samplingRate = 5;
      }
};

class Actuator: virtual public HardwareComponent{
   private:
      float maxTorque;
      int currentAngle;
      bool isEngaged=0;

   public:

      inline void rotate(int angle){
         currentAngle += angle;
      }

      inline void applyResistance(float force){
         maxTorque += force;
      }
      
      inline void initialize() override{
         currentAngle = 0;
         isEngaged = 1;
         maxTorque = 0.00;
      }
};

class Calibrator;

class NeuralJoint: public Sensor, public Actuator{
   private:
   float *signalBuffer = new float[MAX_BUFFER];
   int calibrationOffset, bufferSize;
   static double totalPowerConsumption;
   bool state=0;

   public:
      inline void initialize() override{
         bufferSize = 0;
         state = 1;
         calibrationOffset = 0;
         signalBuffer = NULL;

      }

      NeuralJoint(float buffer[], int bufferSize){
         this->bufferSize=bufferSize;

         for(int i=0; i < bufferSize; i++){
            this->signalBuffer[i] = buffer[i];
         }
         this->state = 1;
         totalPowerConsumption++;
      }

      NeuralJoint(NeuralJoint& obj){
         this->bufferSize = obj.bufferSize;

         for(int i=0; i < obj.bufferSize; i++){
            this->signalBuffer[i] = obj.signalBuffer[i];
         }
         this->state = obj.state;
         totalPowerConsumption++;
      }

      NeuralJoint operator +(NeuralJoint& obj){
         int newBufferSize = bufferSize + obj.bufferSize ;
         float *newBuffer= new float[newBufferSize];

         for(int i=0; i < newBufferSize; i++){
            newBuffer[i] = signalBuffer[i] + obj.signalBuffer[i];
         }
         return NeuralJoint(newBuffer, newBufferSize);

         delete[] newBuffer;
      }

      float operator [](const int& index){
         return signalBuffer[index];
      }

      const void status() const{
         cout<<"\n-----STATUS-------\n";
         cout<<"BUFFER SIZE: "<<bufferSize;
         cout<<"\nCALIBRATION OFFSET: "<<calibrationOffset;

         if(state) cout<<"\nJOINT STATE: ON\n";
         else cout<<"\nJOINT STATE: OFF\n";
      }

      inline static void getPowerConsumption(){
         cout<<"POWER CONSUMED: "<<totalPowerConsumption<<" units."<<endl;
      }

      ~NeuralJoint(){
         state=0;
         delete[] signalBuffer;
         cout<<"\nFreed memory by deleting object! \n";
      }
   
      friend class Calibrator;

};

class Calibrator{
   public:
      inline void setCalibrationOffset(const int& offset, NeuralJoint& obj){
         obj.calibrationOffset= offset;
      }
};

double NeuralJoint::totalPowerConsumption=0;

int main(){

   float buffer[MAX_BUFFER];
   int size, number;

   cout<<"Enter no. of components: "; cin>>number;

   NeuralJoint *components[number];
   
   for(int i=0; i<number; i++){
      cout<<"Enter buffer size: ";
      cin>>size;

      cout<<"Enter buffer constituents (decimal values): \n";
      for(int j=0; j<size; j++) cin>>buffer[j];

      components[i] = new NeuralJoint(buffer, size);
   }

   components[1]->initialize(); //using intialize
   components[1]->status();

   NeuralJoint::getPowerConsumption(); // totalPowerConsumption display

   if(number>2){
      number++;
      components[number-1] = components[0] ; //copy constructor
      components[number-1]->status();
   }

   //float valueAt0 = components[0]; //overloaded []
   for(int i=0; i< number; i++) {
      delete components[i];
   }
    

   return 0;
}
