#include<iostream> 
using namespace std; 
 class Test 
 { 
 public : 
 int x; 
//  int  *ptr;
 void show_data(); 
}; 

 void Test::show_data()
 { 
 cout<<"\n x="<<x; 
 } 
 int main() 
 { Test t; 
int Test :: *ptr= &Test::x; 
 t.*ptr=20; 
 t.show_data(); 
Test *tp = new Test; 
 tp->*ptr=80; 
 tp->show_data(); 
 
 delete[]tp;
 return 0;}
