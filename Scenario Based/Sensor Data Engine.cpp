/*******************************
**Domain Scenario:** Embedded IoT Sensor Data Processing

You are building a generic driver to process incoming data from various IoT sensors.
1. Write a template class `SensorStream<T>` where `T` represents the data type of the sensor reading 
(e.g., `int` for raw ADC values, `float` for processed temperature).
2. Use an STL `std::vector<T>` to store the incoming data stream.
3. Provide an inline member function `void addReading(T val)` to push data into the vector.
4. Implement a function `T calculateAverage()`. 
5. **The Challenge:** Inside `calculateAverage()`, throw a custom exception object (of a class `NoDataException` 
   derived from `std::exception`) if the vector is empty. Catch this exception in `main()` and print "Error: Sensor offline."
6. Overload the template class for `char*` to handle string-based status messages differently 
(e.g., `calculateAverage` on a string stream should throw a `LogicError` exception).
******************************************************/

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class SensorStream{
    private:
     vector<T> readings;
    
    public:
     inline void addReading(const T val){
        readings.push_back(val);
     }

     T calculateAverage(){
        vector<T>::iterator i;

        for(i=readings.start(); i<=readings.end(); i++){
            
        }
        
     }
};

class SensorStream<char*>{
   private:
      vector<char*> readings;

   public:
     inline void addReading(const char* val){
        readings.push_back(val);
     }

     char* calculateAverage(){
        vector<char*>::iterator i;

        for(i=readings.start(); i<=readings.end(); i++){
            
        }
        
     }


};

int main(){

    return 0;
}