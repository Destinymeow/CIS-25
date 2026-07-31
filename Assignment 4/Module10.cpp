#include <iostream>
using namespace std;

class Product {
    int id;
    string name;
    float price;
public:
    
    Product(int i, string n, float p) {
        id = i;
        name = n;
        price = p;
        cout << "Constructor called\n";
    }

    
    ~Product() {
        cout << "Destructor called\n";
    }

    void printDetails() {
        cout << "ID: " << id << ", Name: " << name << ", Price: $" << price << endl;
    }
};

int main() {
    Product p(101, "Notebook", 4.99);
    p.printDetails();
    return 0;
}

/*
KNOWLEDGE CHECK:

1. Explain how constructors and destructors can be used in your project:
   - Destructors and constructors can be used in my project by setting up a database that will close it without complication.
   - I'd use them to also make the code cleaner and less complex.
2. What similarities do the class, constructor, and destructor share?
   - They all belong to the class definition and work together to manage object behavior.
   - The constructor and destructor have the same name as the class.
   - Both are special member functions that are called automatically.
   - Neither has a return type.
3. Expected output of the progran:
   - Constructor called
     ID: 101, Name: Notebook, Price: $4.99
     Destructor called
*/