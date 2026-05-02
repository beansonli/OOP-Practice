#include <iostream>
using namespace std;

class myclass {
    int a, b;

public:
    friend int sum(myclass x);
    void set_ab(int i, int j);
};

void myclass::set_ab(int i, int j) {
    a = i;
    b = j;
}

int sum(myclass x) {
    return x.a + x.b;
}

int main() {
    myclass n, n1, n2;

    n.set_ab(3, 4);
    n1.set_ab(6, 10);
    n2.set_ab(50, 70);

    cout << "First Sum" << endl;
    cout << sum(n) << endl;

    cout << "Second Sum" << endl;
    cout << sum(n1) << endl;

    cout << "Third Sum" << endl;
    cout << sum(n2) << endl;

    return 0;
}



