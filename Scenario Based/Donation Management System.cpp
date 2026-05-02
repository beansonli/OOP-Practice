/******************************************************************************
Develop a Donation Management System in C++ that efficiently manages
the transfer of donations between accounts utilizing classes. The system
consists of the following components: Donor Class contains private data
members: string donor_name, double balance. Write the following
functions in public section:
- set_details(string name, double amount)
- display()
- double get_balance()
Recipient Class contains the private data member: string recipient_name,
double account_balance, double amount_required needed by the recipient
and the following functions in public section:
- set_details(string name, double balance, double amount)
- display()
- double get_balance()
Additionally, the program includes the following function:
transfer (Donor &donor, Recipient &recipient, double
amount)
This function facilitates the transfer of funds between a donor and a
recipient. This function will verify whether the donor has sufficient funds
for the transfer. If the donor has adequate funds, both the donor's and
recipient's balances will be updated accordingly. Complete the program
using the above-mentioned conditions.

*******************************************************************************/

#include <iostream>
using namespace std;

class Donor {
	string donor_name;
	double balance;

public:

	void set_details(string name, double amount) {
		donor_name=name;
		balance=amount;
	}

	double get_balance() {
		return balance;
	}
	
	void update_balance(double new_balance) {
        balance = new_balance;
    }

	void display()
	{
		cout<<"Donor Name: "<<donor_name<<"\nBalance: "<<balance<<"\n";
	}

};

class Recipient: public Donor {
	string recipient_name;
	double account_balance;

public:

	void set_details(string name, double amount) {
		recipient_name=name;
		account_balance=amount;
	}

	void display()
	{
		cout<<"Recipient Name: "<<recipient_name<<"\nBalance: "<<account_balance<<"\n";
	}

	void transfer(Donor &donor, Recipient &recipient, double amount) {
		double check = donor.get_balance();
		if(check>amount) {
			check-=amount;
			
			donor.update_balance(check);
			recipient.account_balance+=amount;

		}
		else
			cout<<"INSUFFICIENT FUNDS!\nCannot make transfers.\n";
	}

};


int main()
{
	Donor d1;
	d1.set_details("Park", 25000);
	Recipient r1;
	r1.set_details("Lara",50);
	r1.transfer(d1,r1, 200000);
	d1.display();
	r1.display();


	return 0;
}
