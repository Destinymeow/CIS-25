#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Item {
public:  
    string name;
    double price;
    int quantity;
    
    double getTotalPrice() {
        return price * quantity;
    }
};

const string FILENAME = "cart.txt";

void addItem() {
    Item item;
    
    cout << "\nEnter item name: ";
    cin.ignore(); 
    getline(cin, item.name);
    
    cout << "Enter item price: ";
    cin >> item.price;
    
    cout << "Enter item quantity: ";
    cin >> item.quantity;
    
    ofstream outFile;
    outFile.open(FILENAME.c_str(), ios::app);
    
    if (outFile.is_open()) {
        outFile << item.name << " " << item.price << " " << item.quantity << endl;
        outFile.close();
        cout << "Item added to cart.\n" << endl;
    } else {
        cout << "Error: Could not open file.\n" << endl;
    }
}

void viewCheckout() {
    ifstream inFile;
    inFile.open(FILENAME.c_str());
    
    if (!inFile.is_open()) {
        cout << "\nNo items in cart.\n" << endl;
        return;
    }
    
    cout << "\nCHECKOUT" << endl;
    
    string name;
    double price;
    int quantity;
    double total = 0.0;
    
    while (inFile >> name >> price >> quantity) {
        double itemTotal = price * quantity;
        total = total + itemTotal;
        
        cout << name << " = $" << price << " x " << quantity << " = $" << itemTotal << endl;
    }
    
    inFile.close();
    
    cout << "\nTotal: $" << total << "\n" << endl;
}

int main() {
    int choice;
    
    do {
        
        cout << "===== SHOPPING CART MENU =====" << endl;
        cout << "1. Add item to cart" << endl;
        cout << "2. View checkout" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        
        if (choice == 1) {
            addItem();
        }
        else if (choice == 2) {
            viewCheckout();
        }
        else if (choice == 3) {
            cout << "\nThank you for shopping!" << endl;
        }
        else {
            cout << "\nInvalid option. Please try again.\n" << endl;
        }
        
    } while (choice != 3);
    
    return 0;
}