#include <iostream>
using namespace std;

int main() {
    int choice;
    
    cout << "===== MAIN MENU =====" << endl;
    cout << "1. Say Hello" << endl;
    cout << "2. Say Goodbye" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    
    if (choice == 1) {
        cout << "Hello! Welcome :)." << endl;
    }
    
    if (choice == 2) {
        cout << "Goodbye! Have a nice day." << endl;
    }
    
    if (choice == 3) {
        cout << "Closing program..." << endl;
    }
    
    if (choice < 1 || choice > 3) {
        cout << "Please enter 1, 2, or 3." << endl;
    }
    
    return 0;
}