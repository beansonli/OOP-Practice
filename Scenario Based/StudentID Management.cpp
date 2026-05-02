/******************************************************************************
Design a class StudentID for a smart campus system.
Private data members:
- static int idCounter
- int studentID
- string name
- string department
- double walletBalance

Implement:
- Default constructor
- Parameterized constructor
- Constructor with default arguments
- Copy constructor
- const member function displayDetails() const
- Inline function addBalance(double)
- Static member function getNextID()
- Destructor that prints when a card is deactivated

Demonstrate:
- Array of objects
- Passing object as argument to a function transferBalance(StudentID&, StudentID&, double)
- Use of this pointer
- Dynamic memory allocation (new)
 -Array of pointers to objects

You must also use a namespace Campus.

*******************************************************************************/

#include <iostream>
using namespace std;

namespace Campus{

    class StudentID{
        private:
        static int idCounter;
        int studentID;
        string name, department;
        double walletBalance;
        
        public:
        
        StudentID(string Name= "Student" ,string dept="None", double bal=0.00){
            this->name = Name;
            this->department = dept;
            this->walletBalance = bal;
        
            studentID = ++idCounter;
        };
        
        
        StudentID(const StudentID &s){ //copy constructor
            name=s.name;
            department=s.department;
            studentID= ++idCounter;
            walletBalance= s.walletBalance;
        }
        
    
        
        void displayDetails() const{
            cout<<"\nStudent ID: "<<studentID<<endl;
            cout<<"Student Name: "<<name<<endl;
            cout<<"Department: "<<department<<endl;
            cout<<"Balance: "<<walletBalance<<endl;
        }
        
        inline void addBalance(double amount){
            walletBalance += amount;
        }
        
        static int getNextID(){
            return idCounter+1;
        }
        
        ~StudentID(){
            cout<<"Deactivating "<<studentID<<endl;
        }
        
        friend void transferBalance(StudentID& ,StudentID& , double);
    };
    
    int StudentID::idCounter=0;
    
    void transferBalance(StudentID& s1, StudentID& s2, double balance){
        s1.walletBalance -= balance;
        s2.addBalance(balance);
        cout<<"\nTransfer completed for amount: "<<balance<<endl;
    }
    
}



int main(){
    using namespace Campus;
    
    int n;
    cout<<"Enter number of students: ";
    cin>>n;
    
    StudentID s1; //for demonstration purposes of the question, these were created.
    StudentID s2(s1);
    
    s2.addBalance(2000);
    
    StudentID *students[n];
    
    for(int i=0; i<n ;i++){
        string name, dept;
        double amount;
        
        cout<<"\nEnter Student Name: "; cin>>name;
        cout<<"Enter Studnet Department: "; cin>>dept;
        cout<<"Enter Student Balance: "; cin>>amount;
        
        students[i]= new StudentID(name, dept, amount);
        
    }
    
    transferBalance(s2, *students[0], 200); //only an implementation example
    
    s1.displayDetails();
    s2.displayDetails();
    
    for(int i=0; i<n ;i++){
        students[i]->displayDetails();
        delete students[i];
    }
    
    cout<<"\nNext available Student ID: "<<StudentID::getNextID()<<endl;
    
    return 0;
}
