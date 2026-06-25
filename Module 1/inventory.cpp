#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Hello Inventory System!\n";
    cout << "\tData Types:\n";
    cout << "Size of int: " << sizeof(int) << " bytes\n";
    cout << "Size of float: " << sizeof(float) << " bytes\n";
    cout << "Size of char: " << sizeof(char) << " bytes\n";
    cout <<"\n"<<string(30,'-')<<"\n\n";
    string itemName;
    int quantity;
    float cost;
    cout << "Enter item name: ";
    cin >> itemName;
    cout << "Enter quantity: ";
    cin >> quantity;
    cout << "Enter cost: ";
    cin >> cost;
    cout << "Total cost for " <<itemName<<": $"<<(quantity*cost)<<endl;
    return 0;
}