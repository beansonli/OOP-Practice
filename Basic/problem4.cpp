#include <iostream>
using namespace std;

class Number {
    int a, b, c, d;
    
    public:
        // default constructor
    Number() {
        a = b = c = d = 0;
    }

    // two-parameter constructor
    Number(int x, int y) {
        a = x;
        b = y;
        c = d = 0;
    }

    // four-parameter constructor
    Number(int x, int y, int z, int w) {
        a = x;
        b = y;
        c = z;
        d = w;
    }

    // copy constructor
    Number(const Number &n) {
        a = n.a;
        b = n.b;
        c = n.c;
        d = n.d;
    }

    void showdata() {
        cout << a << " " << b << " " << c << " " << d << endl;
    }
	
};
int main()
{
    Number n1;
    Number n2(10, 20);
    Number n3(30,40, 50, 60);
    Number n4(n2);
    Number n5= n1;
    
    n1.showdata();
    n2.showdata();
    n3.showdata();
    n4.showdata();
    n5.showdata();


	return 0;
}


