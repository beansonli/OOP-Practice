/******************************************************************************
University Management System

Create:
> Base Class: Person
> Derived Classes:
- Student
- Faculty
> Create a class TeachingAssistant that inherits from both Student and Faculty.

Requirements:
- Use virtual base class to avoid diamond problem
- Demonstrate constructor call order
- Override a function in derived class
- Use const member function
- Demonstrate abstract class (make one base class abstract with pure virtual function)
- Show array of objects of base class pointers
- Demonstrate dynamic binding

*******************************************************************************/

#include <iostream>
using namespace std;

class Person{
    public:
    virtual void Details() const=0;
    virtual ~Person(){};
};

class Student: virtual public Person{
    protected:
    int studentID;
    string studentName, department;
    
    public:
    Student(int id, string name, string dept ){
        studentID=id;
        studentName=name;
        department=dept;
        cout<<"\nStudent "<<studentID<<" created!"<<endl;
    }
    
    ~Student(){
        cout<<"\nStudent "<<studentID<<" deleted!"<<endl;
    }
    
    void Details() const{
        cout<<"\nStudent ID: "<<studentID<<endl;
        cout<<"Student Name: "<<studentName<<endl;
        cout<<"Student Dept: "<<department<<endl;
    }
    
};

class Faculty: virtual public Person{
    protected:
    int facultyID;
    string facultyName, teaching;
    
    public:
    Faculty(int id, string name, string dept ){
        facultyID=id;
        facultyName=name;
        teaching=dept;
        cout<<"\nFaculty "<<id<<" created!"<<endl;
    }
    
    ~Faculty(){
        cout<<"\nFaculty "<<facultyID<<" deleted!"<<endl;
    }
    
    void Details() const{
        cout<<"\nFaculty ID: "<<facultyID<<endl;
        cout<<"Faculty Name: "<<facultyName<<endl;
        cout<<"Faculty Dept: "<<teaching<<endl;
    }
    
    
};

class TeachingAssistant: public Student, public Faculty{
    public:
    TeachingAssistant(int sid, int fid, string name, string dept, string subject): Person(), Student(sid, name, dept), Faculty(fid, name, subject){
        cout<<"\nTeaching Assistant "<<name<<" created!"<<endl;
    }
    
    ~TeachingAssistant(){
        cout<<"\nTeaching Assistant "<<facultyID<<" deleted!"<<endl;
    }
    
    void Details() const{
        cout<<"\nTA ID: "<<studentID<<endl;
        cout<<"TA Name: "<<studentName<<endl;
        cout<<"TA Dept: "<<teaching<<endl;
    }
};




int main()
{
    Person* arr[3];

    arr[0] = new Student(1001,"sahil", "mech");
    arr[1] = new Faculty(140, "jagbir","maths");
    arr[2] = new TeachingAssistant(1005, 145, "deven", "mech", "physics");
    
    for(int i = 0; i < 3; i++)
        arr[i]->Details();   // Dynamic binding
    
    for(int i = 0; i < 3; i++)
        delete arr[i];

    return 0;
}
