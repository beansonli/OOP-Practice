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
#include <exception>
using namespace std;

class NoDataException : public exception{
   string message;

   public:
      NoDataException(string msg) : message(msg){}
      
      const char* getException(){
         return message.c_str();
      }
};

class LogicError : public exception{
   string message;

   public:
      LogicError(string msg) : message(msg){}
      
      const char* what() const noexcept override{
         return message.c_str();
      }
};

template<typename T> class SensorStream;

template<> class SensorStream<const char*>{
   private:
      vector<const char*> readings;

   public:
      inline void addReading(const char* val){
         readings.push_back(val);
      }

      void calculateAverage(){
         throw LogicError("Stream Messages cannot be averaged!");
      }


};

template <typename T>
class SensorStream{
    private:
     vector<T> readings;
    
    public:
     inline void addReading(const T val){
        readings.push_back(val);
     }

     T calculateAverage(){
         if(readings.empty())
            throw NoDataException("Sensor offline");

         typename vector<T>::iterator i;
         T avg = 0;

         for(i=readings.begin(); i!=readings.end(); ++i){
            avg += *i;
         }
        
         return avg;
     }
};


int main(){

   SensorStream<int> ADC;

   SensorStream<float> temperatureSensor;
   temperatureSensor.addReading(41.5);
   temperatureSensor.addReading(30.7);

   SensorStream<const char*> recorder;
   recorder.addReading("Active Recorder");
   recorder.addReading("How can i forget, Hello World!");

   try{
      float tempAvg = temperatureSensor.calculateAverage();
      cout<<"Avg temp: "<<tempAvg<<endl;

      /* exception blobs
      int adcAvg = ADC.calculateAverage();
      cout<<"Avg ADC data: "<<adcAvg<<endl;
      */
      recorder.calculateAverage();
      
   }
   catch(NoDataException e){
      cout<<"Error: "<<e.getException()<<endl;
   }
   catch(LogicError strExp){
      cout<<"Error: "<<strExp.what()<<endl;
   }
   return 0;
}