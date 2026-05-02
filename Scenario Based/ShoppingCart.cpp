/******************************************************************************
Develop a class Order that manages customer orders for an online store. 
The Order class should have attributes like: 
- orderID (static int) - customerName (string)
- itemList (array of strings) - totalAmount (double) 
Implement the following features:
a. Implement a constructor that initializes the orderID using a static counter, customerName to the given value, and itemList using an array. The totalAmount should be calculated based on the items in the itemList.
b. Implement a friend function applyDiscount(Order& order, double discountPercentage) that reduces the totalAmount by the given discount percentage. 
d. Implement a method displayOrderDetails() that displays all details of the order, including the order ID, customer name, item list, and total amount.
e. Implement a static member function getNextOrderID() that returns the next available order ID. 

Write a main function to create and manage multiple orders, apply discounts, display order details, 
and show the next available order ID using the static function.

*******************************************************************************/

#include <iostream>
using namespace std;

class Order{
    static int counter;
    int orderID, itemcount=0;
    string customerName, itemList[20];
    double totalAmount=0;
    
    public:
    
    Order(string name, string items[], int size, double cost[]){
            customerName=name;
            
            for(int i=0 ; i<size ; i++){
                itemList[i]=items[i];
                totalAmount += cost[i];
                itemcount++;
            }
            counter++;
            orderID = counter;
    }
    
    
    void displayOrderDetails(){
        cout<<"Order ID: "<<orderID<<endl;
        cout<<"Customer Name: "<<customerName<<endl;
        cout<<"Total Amount: "<<totalAmount<<endl;
        
        cout<<"Items: "<<endl;
        for(int i=0 ; i<itemcount ; i++)
               cout<<"- "<< itemList[i]<<endl;
          
    }
    
    static int getNextOrderID(){
        return counter+1;
    }
    
    friend void applyDiscount(Order&, double);
    
};

int Order::counter=0;

void applyDiscount(Order& o, double discountPercentage){
    o.totalAmount -= o.totalAmount*(discountPercentage/100.0);
    cout<<"Post Dicount Total Amount: "<<o.totalAmount<<endl;
}

int main()
{
    int n;
    cout<<"Enter total no. of orders: ";
    cin>>n;
    
    Order *o[n];
    
    for(int i = 0 ; i<n ; i++){
        string name;
        int size;
        
        cout<<"\nEnter customer name: ";
        cin>>name;
        cout<<"Enter no. of items: ";
        cin>>size;
        
        if(size<=0 || size>20){
            cout<<"Invalid no. of items!" <<endl;
            break;
        }
        
        string *items= new string[size];
        double *cost= new double[size];
        
        for(int j= 0; j<size; j++){
            cout<<"Enter item "<<j+1<<": ";
            cin>>items[j];
            cout<<"Enter cost of item: ";
            cin>>cost[j];
        }
        
        o[i]= new Order(name, items, size , cost );
        
        delete[] items;
        delete[] cost;
    }
    
    for(int i=0; i<n ; i++){
        o[i]->displayOrderDetails();
        
        double discount;
        
        cout<<"Enter discount (in percentage): ";
        cin>>discount;
        
        if(discount<100 && discount>0)
            applyDiscount(*o[i], discount);
        else{
            cout<<"Invalid discount!"<<endl;
            break;
        }
        
        delete o[i];
    }
    
    cout<<"\nNext Available Order ID: "<<Order::getNextOrderID()<<endl;
    
    return 0;
}
