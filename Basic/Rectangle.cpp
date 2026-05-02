/******************************************************************************
Create a class Rectangle that represents a rectangle in a 2D space. 
The class should include attributes length (double) and width (double). 
Implement the following functionalities:

a) Implement a default constructor that initializes length and width to 1.0. 
   Implement a parameterized constructor that allows setting custom length 
   and width. Ensure that both dimensions are positive.

b) Implement a friend function calculateArea(Rectangle& rect) 
   that calculates and returns the area of the rectangle.

c) Implement a friend function calculatePerimeter(Rectangle& rect) 
   that calculates and returns the perimeter of the rectangle.

d) Create an array of Rectangle objects (size 3) using dynamic initialization. 
   Use a loop to input the dimensions for each rectangle from the user.

e) Implement a static member function compareArea(Rectangle& rect1, Rectangle& rect2) 
   that compares the area of two rectangles and returns the rectangle with the 
   larger area. If the areas are equal, return either rectangle.

Write a main function that demonstrates the creation of rectangle objects, 
calculation of area and perimeter, comparison of areas, and dynamic memory management.

*******************************************************************************/

#include <iostream>
using namespace std;

class rectangle{
    float length, width;
    
    public:
    rectangle(){
        length=width=1.0;
    }
    
    rectangle(float l, float w){
        if(l>0 && w>0){
            length=l;
            width=w;
        }
    }
    
    friend float calculateArea(rectangle& );
    friend float calculatePerimeter(rectangle& );
    
    static rectangle compareArea(rectangle &rect1 , rectangle &rect2){
        if(calculateArea(rect1) >= calculateArea(rect2))
            return rect1;
        else
            return rect2;  
    }
    
    void display(){
        cout<<length<<", "<<width<<endl;
    }
};

float calculateArea(rectangle &r){
    return r.length * r.width;
    
}

float calculatePerimeter(rectangle &r){
    return 2 * (r.length + r.width);
}

int main()
{
    float len, wid;
    rectangle *r[3];
    for(int i=0; i<3 ;i++){
        cout<<"Enter dimensions of rectangle (len, width): ";
        cin>>len>>wid;
        r[i] = new rectangle(len,wid);
        
        float area = calculateArea(*r[i]);
        float perimeter = calculatePerimeter(*r[i]);
        
        cout<<"Area: "<<area<<endl;
        cout<<"Perimeter: "<<perimeter<<endl;
        
    }
    
    rectangle rect= rectangle::compareArea(*r[0], *r[1]);
    cout<<"Dimensions of larger rectangle: "; rect.display();
    
    for(int i=0; i<3 ;i++)
        delete r[i];
    
    
    return 0;
}



