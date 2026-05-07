/******************************************************************************
# CHALLENGE 02: The Quantum Metrology Signal Engine

## Scenario
You are building a generic Metrology library designed to handle high-precision measurement streams (integers, doubles, or complex numbers) using advanced C++ templates.

## Core Requirements
1. **Generics (Templates):**
   - Wrap your entire library in a `namespace` called `MetrologyCore`.
   - Create a **Class Template** `DataStream<T, int BufferSize>` where `BufferSize` is a **non-type template parameter**.
   - Implement a **Function Template** `applyGain<T>(T value)` that is overloaded specifically for `char*` to handle string-based error flags differently.

2. **Advanced Overloading:**
   - Overload the `()` operator (Function Call) so a `DataStream` object can be used to apply a mathematical filter to its internal buffer.
   - Overload the `<<` operator as a **Friend Function** to allow printing the entire `DataStream` object directly to `cout`.

3. **Data Conversion & Logic:**
   - Implement a **Conversion Operator** that allows a `DataStream` object to be explicitly or implicitly cast to a `double`, returning the average of the current buffer.
   - Use **Inline Functions** for high-frequency calculations inside the template.

4. **Array of Objects:**
   - Create an **Array of Objects** of type `DataStream<int, 5>`.
   - Pass one of these objects to a function by **Reference** and another by **Value** to observe the difference in behavior (specifically how the copy constructor and `this` pointer interact).

## The Implementation Task
Write a program that:
1. Instantiates `DataStream<double, 10>` and `DataStream<int, 5>`.
2. Populates them with data, uses the `()` operator to filter the data, and then uses the cast operator to find the average.
3. Shows that `DataStream<double, 10>` and `DataStream<double, 20>` are treated as **distinct types** by the compiler.

*******************************************************************************/

#include <iostream>
using namespace std;

namespace MetrologyCore{

   template<typename T>
   void applyGain(T value){

   }

   void applyGain(char* value){

   }

   template<typename T, int BufferSize>
   class DataStream{
      private:
         T data[BufferSize];

      public:
         DataStream(T data[]){
            for(int i=0; i<BufferSize ; i++)
               this->data[i] = data[i];
         }

         DataStream(const DataStream& obj){
            for(int i=0; i<BufferSize ; i++)
               this->data[i] = obj.data[i];
         }

         void operator () (T value){
         }

         operator double(){
            double sum=0;
            for(int i=0; i<BufferSize ; i++)
               sum += data[i];
            return double(sum)/double(BufferSize);
         }

         friend ostream& operator << ( ostream&, const DataStream& ); 
   };

   ostream& operator << ( ostream& stream, const DataStream& obj){
      stream << obj.data;
      return stream;
   }


}

int main()
{

    return 0;
}
