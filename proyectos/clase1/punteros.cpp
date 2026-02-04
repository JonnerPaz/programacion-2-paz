#include <iostream>

using namespace std;

void formatter_function(int* a) {
    // It is possible to change the value of the pointer outside
    // original var scope
    *a = 20;
}

int main() {
    int a = 10;
    int* a_ptr = &a;
    cout << "reference of a: " << &a << endl;
    cout << "dereference of a: " << *(&a) << endl;

    cout << "before: " << a << endl;
    formatter_function(a_ptr);
    cout << "after: " << a << endl;
    return 0;
}
