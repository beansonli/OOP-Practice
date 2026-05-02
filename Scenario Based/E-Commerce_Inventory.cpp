/******************************************************************************
Design a class Product.

Private members:
- int productID
- string name
- double* monthlySales (dynamic array)
- int months

Requirements:
- Constructor with dynamic initialization
- Copy constructor (deep copy required)
- Destructor to free memory
- Friend function compareSales(Product&, Product&)
- Friend class InventoryManager that can modify product price
- Static object usage
- Demonstrate dynamic array of objects
- Demonstrate pointer to objects

Explain what happens if copy constructor is removed.


*******************************************************************************/

#include <iostream>
using namespace std;
class InventoryManagement; //declaration

class Product{
    int productID, months;
    string name;
    double* monthlySales;
    double totalSales=0;
    
    public:
    Product(int ID, string Name, int Months, double sales[]){
        productID = ID;
        name = Name;
        months = Months;
        montlySales = new double[Months];
        
        for(int i = 0; i < Months ; i++)
            monthlySales[i] = sales[i];
            totalSales += sales[i];
    }
    
    Product(const Product& p){
        productID = p.productID;
        name = p.name;
        monthlySales = p.monthlySales;
        months = p.months;
    }
    
    ~Product(){
        cout<<"Deleting objects.."<<endl;
    };
    
    friend void compareSales(Product& , Product& );
    friend class InventoryManagement;
};

void compareSales(Product& p1, Product& p2 ){
    if(p1.totalSales>= p2.totalSales)
        cout<<"Product with ID "<<p1.productID<<" has greater sales!"<<endl;
    else
        cout<<"Product with ID "<<p2.productID<<" has greater sales!"<<endl;
}

class InventoryManagement{
    double productPrice = 0.00;
    
    public:
    void changePrice(Product& p, double amount){
        productPrice += amount;
    }
};

int main()
{
    int n;
    cout<<"Enter total no. of products: ";
    cin>>n;
    
    Product* products[n];
    static InventoryManagement obj;
    
    for(int i=0 ; i<n ; i++){
        int id, months;
        string name;
        
        cout<<"Enter Product ID: "; cin>>id;
        cout<<"Enter Product Name: "; cin>>name;
        cout<<"Enter total no. of months of sales: "; cin>>months;
        
        double* sales = new double[months];
        
        for(int i=0; i<months; i++){
            cout<<"Enter sales recorded for month "<<i+1;
            cin>>sales[i];
        }
        
        products[i] = new Product(id, name, months, sales);
        
        delete[] sales;
    }
    
    if(n>=2)
        compareSales(*products[0], *products[1]); //for demonstration only here
    else
        cout<<"Not enough products to compare sales!"<<endl;

    for(int i=0 ; i<n ; i++){
        
        
        products[i].displayDetails();
        
        delete products[i];
    }
    return 0;
}
