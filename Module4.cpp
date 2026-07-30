#include <iostream>
using namespace std;

int main() {
    float n1, n2, n3;
    
    cout << "Enter three numbers: ";
    cin >> n1 >> n2 >> n3;
    //I got rid of => and fixed it by puting >=
    if (n1 >= n2) {

        if (n1 >= n3) {
            cout << "Largest number: " << n1;
        } else {
            cout << "Largest number: " << n3;
        } //fixed }{ alignment, made the code stop executing
    } else {
        
        if (n2 >= n3) {
            //Added the Semicolon at the end
            cout << "Largest number: " << n2;
            // added other else statment
        } else {
            cout << "Largest number: " << n3;
        }
    }
    
    return 0;
}