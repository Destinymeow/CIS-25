#include <iostream>
#include <string>
using namespace std;


struct Patient {
    int id;
    string name;
    int age;
};

int main() {
    
    Patient patient1;
    
    
    patient1.id = 101;
    patient1.name = "John";
    patient1.age = 40;
    
    
    Patient* p = &patient1;
    

    cout << "Patient Information:" << endl;
    cout << "ID: " << p->id << endl;
    cout << "Name: " << p->name << endl;
    cout << "Age: " << p->age << endl;
    
    cout << "\nMemory address of patient 1: " << &patient1 << endl;
    cout << "Value stored in pointer p: " << p << endl;
    
    return 0;
}
/*
    KNOWLEDGE CHECK
1. WHat is a pointer, and how did you use it in your program?
    - A pointer is a variable that stores memory addresses of another variable.
    - How I used it in my program is that first I declared Patient* p=&patient1; which makes a pointer p that stores the address of patient 1.
2. What does the & operator do in your program?
    - The & operator returns the memory address of a variable. Like &patient1 retrieves the memory address where patient1 is stored.
3. Write the output of your program.
    - Patient Information:
    ID: 101
    Name: John
    Age: 40
    Memory address of patient 1: 0x7ffd3cc1bff0
    Value stored in pointer p: 07ffd3cc1bff0
*/