/******************************************************************************
You are provided with the ShoppingCart class, as shown above. Write the
main() function for the given class. Your task is to:
Take input from the user for the number of shopping carts (n) and
dynamically create an array of n ShoppingCart objects. Initialize the objects
using the parameterized constructor by taking the input at run-time. Display the details.Finally, release the dynamically allocated memory for the shopping carts before the program terminates.


*******************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class ShoppingCart{
    private:
    int cart_id;
    string customer_name;
    int item_count;
    
    public:
    
    ShoppingCart() {}
    
    ShoppingCart(int id, string name, int count){
        cart_id=id;
        customer_name=name;
        item_count=count;
    }
    
    ~ShoppingCart(){
        cout<<"Thank You, "<<customer_name<<endl;
    }
    
    void display_cart(){
        cout<< "Cart ID: "<<cart_id<<endl;
        cout<< "Customer name: "<<customer_name<<endl;
        cout<< "Number of Items in Cart: "<<item_count<<endl;
    }
    
};

int main() {
    int n;
    cout<<"Enter  no. of shopping carts: ";
    cin>>n;
    
    ShoppingCart* cart=  new ShoppingCart[n];
    
    for(int i=0; i<n; i++){
        int id, count;
        string name;
        cout<<"Enter details of the cart (ID, Customer name, Number of Items in Cart):\n";
        cin>>id>>name>>count;
        
        cart[i]= new ShoppingCart(id, name, count);
    }
    
    cout << "\nCart Details:\n";
    for(int i=0; i<n; i++){
        cart[i].display_cart();
    }
    
    delete cart[];
    return 0;
}

