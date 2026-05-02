/******************************************************************************
Design a class Triangle with private attributes: base and height.
Implement a public function compareArea(Triangle &t1, Triangle
&t2) that compares the areas of two triangles passed as arguments
and returns the triangle with the larger area.

*******************************************************************************/

#include <iostream>
using namespace std;

class triangle{
    float base, height;
    
    double Area(){
        double area= 0.5*base*height;
        return area;
    }
    
    public:
    
    triangle(){ //default constructor
        base=1.0;
        height=1.0;
    }
    
    triangle(float b, float h){ // parameterized constructor to intitalise 
        base=b;
        height=h;
    }
    
    triangle compareArea(triangle &t1, triangle &t2){ //the function
        
       if(t1.Area() >t2.Area())
        return t1;
       else
        return t2;
    }
    
    void get(){
        cout<<"Base: "<<base<<" | Height: "<<height<<endl;
    }
    
};

int main() {

   
    triangle t1(0.125, 4);
    triangle t2{};
    triangle t3(3, 4);
    
    //Cant figure how to just call the function without a object
    triangle result= t3.compareArea(t1,t2); 
    
    cout << "Features of the greater triangle is-> " ;
    result.get();
    
    return 0;
}
