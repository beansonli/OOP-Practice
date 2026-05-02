/******************************************************************************
Patient–Doctor Management System

## Patient Class
Define a **Patient** class with private data members:
- patientID (static int)
- name (string)
- assignedDoctor (pointer to a Doctor object)

### Requirements
- Implement a constructor that initializes **name**.
- The **patientID** should be assigned automatically using a **static counter**.
- Include a **friend class Doctor** that can access and modify the **assignedDoctor pointer**.

---

## Doctor Class
Define a **Doctor** class with private data members:
- doctorID (static int)
- name (string)
- patients (dynamic array of Patient pointers)

### Requirements
- Implement a constructor that initializes **name** and allocates memory for the **patients array**.
- The **doctorID** should be assigned automatically using a **static counter**.
- Implement a **destructor** to deallocate the memory used by **patients**.
- Include a member function  
  **addPatient(Patient* patient)**  
  that:
  - adds a patient to the **patients array**
  - sets the patient's **assignedDoctor pointer** to the current **Doctor object**.

---

## Main Function Requirements
Write the **main()** function to:

- Dynamically create **arrays of Patient and Doctor objects**.
- Assign patients to doctors using the **addPatient()** function.
- Display the **details of each doctor and their assigned patients**.

*******************************************************************************/

#include <iostream>
using namespace std;
class Doctor;

class Patient{
  private:
  static int counter;
  int patientID;
  string name;
  Doctor *assignedDoctor;
  
  public:
  
  Patient(string Name){
      name=Name;
      ++counter;
      patientID=counter;
  }
  
  friend class Doctor;
  
};

int Patient::counter=0;


class Doctor{
    private:
    static int counter;
    int doctorID;
    string name;
    Patient *patients[20];
    int size=0;
    
    public:
    
    Doctor(string Name){
        name= Name;
        ++counter;
        doctorID=counter;
        
    }
    
    ~Doctor(){
        for(int i=0; i<size; i++){
            cout<<"Destructing Patient ID: "<<patients[i]->patientID<<endl;
            delete patients[i];
        }
    }
    
    void addPatient(Patient *patient){
        patients[size]= patient;
        patient->assignedDoctor= this;
        size++;
    }
    
    void display(){
        cout<<"\nDoctor ID: "<<doctorID<<endl;
        cout<<"Doctor name: "<<name<<endl;
        cout<<"-----Assigned Patients-------"<<endl;
        for(int i=0; i<size; i++){
            cout<<"Patient ID: "<<patients[i]->patientID<<endl;
            cout<<"Patient Name: "<<patients[i]->name<<endl;
        }
    }
    
};

int Doctor::counter=0;

int main(){
    int p, d;
    cout<<"Enter total no. of patients: ";
    cin>>p;
    cout<<"Enter total no. of doctors: ";
    cin>>d;
    
    Patient *patients[p];
    Doctor *doctors[d];
    string doctorName, patientName;
    char choice;
    
    for(int i=0; i<d; i++){
        cout<<"\nEnter Doctor name: ";
        cin>>doctorName;
        doctors[i]= new Doctor(doctorName);
    }
    
    for(int j=0; j<p; j++){
        cout<<"\nEnter Patient name: ";
        cin>>patientName;
        patients[j]= new Patient(patientName);
        
        cout<<"Do you want the current doctor assigned? (Y/N): ";
        cin>>choice;
        int i=0;
        if(i<d){
            if(choice=='Y' || choice=='y')
                doctors[i]->addPatient(patients[j]);
            else{
                cout<<"Assigning next available doctor!"<<endl;
                doctors[i+1]->addPatient(patients[j]);
            }
        }
        else
            cout<<"Not enough doctors!"<<endl;
    }

   
    for(int i=0; i<d; i++){
        doctors[i]->display();
        delete doctors[i];
    }
    
    
    return 0;
}
