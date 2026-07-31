#include <iostream>
#include <cmath>     
#include <string>    
using namespace std;

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
void showMenu();

int main() {
    int option;
    int num1, num2;
    
    do {
        showMenu();
        cin >> option;
        
        if (option == 1) {
            cout << "Enter two numbers to add: ";
            cin >> num1 >> num2;
            cout << "Sum: " << add(num1, num2) << endl;
        }
        else if (option == 2) {
            cout << "Enter two numbers to subtract: ";
            cin >> num1 >> num2;
            cout << "Difference: " << subtract(num1, num2) << endl;
        }
        else if (option == 3) {
            cout << "Enter two numbers to multiply: ";
            cin >> num1 >> num2;
            cout << "Product: " << multiply(num1, num2) << endl;
        }
        else if (option == 4) {
            cout << "Bye bye!" << endl;
        }
        else {
            cout << "Invalid, please select a number between 1-4!" << endl;
        }
        
    } while (option != 4);
    
    return 0;
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

void showMenu() {
    cout << "\n1. Add\n2. Subtract\n3. Multiply\n4. Exit\nChoice: ";
}
