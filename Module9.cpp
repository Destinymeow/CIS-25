#include <iostream>
#include <string>
#include <vector>
using namespace std;

class User {
protected: 
    string username; 
    
public: 
    User(const string& name = "Unknown") :  username(name) {}
    
    
    virtual void accessLevel() {
        cout << "General Access" << endl;
    }
    
    string getUsername() const {
        return username;
    }
    
    virtual ~User() {}
};

class Employee :  public User {
public: 
    Employee(const string& name) :  User(name) {}
    
    void accessLevel() override {
        cout << "Username:  " << username << endl;
        cout << "Access Level:  Employee" << endl;
        cout << "Permissions:  View inventory" << endl;
        cout << "------------------------" << endl;
    }
};

class Manager :  public User {
public: 
    Manager(const string& name) :  User(name) {}
    
    void accessLevel() override {
        cout << "Username:  " << username << endl;
        cout << "Access Level:  Manager" << endl;
        cout << "Permissions:  View and update inventory" << endl;
        cout << "------------------------" << endl;
    }
};

class Admin :  public User {
public: 
    Admin(const string& name) :  User(name) {}
    
    void accessLevel() override {
        cout << "Username:  " << username << endl;
        cout << "Access Level:  Administrator" << endl;
        cout << "Permissions:  Full access - add,  update,  delete inventory" << endl;
        cout << "------------------------" << endl;
    }
};

class InventoryManager :  public Employee {
public: 
    InventoryManager(const string& name) :  Employee(name) {}
    
    void accessLevel() override {
        cout << "Username:  " << username << endl;
        cout << "Access Level:  Inventory Manager" << endl;
        cout << "Permissions:  Full inventory management access" << endl;
        cout << "------------------------" << endl;
    }
};

class InventorySystem {
private: 
    vector<string> inventory;
    
public: 
    void viewInventory() {
        cout << "\n===== INVENTORY LIST =====" << endl;
        if (inventory.empty()) {
            cout << "Inventory is empty." << endl;
        } else {
            for (size_t i = 0; i < inventory.size(); i++) {
                cout << i + 1 << ". " << inventory[i] << endl;
            }
        }
        cout << "==========================\n" << endl;
    }
    
    void addItem(const string& item) {
        inventory.push_back(item);
        cout << "Added:  " << item << endl;
    }
    
    void updateItem(int index,  const string& newItem) {
        if (index >= 1 && index <= inventory.size()) {
            cout << "Updated:  " << inventory[index - 1] << " -> " << newItem << endl;
            inventory[index - 1] = newItem;
        } else {
            cout << "Invalid index!" << endl;
        }
    }
    
    void deleteItem(int index) {
        if (index >= 1 && index <= inventory.size()) {
            cout << "Deleted:  " << inventory[index - 1] << endl;
            inventory.erase(inventory.begin() + (index - 1));
        } else {
            cout << "Invalid index!" << endl;
        }
    }
};

int main() {
    InventorySystem system;
    User* currentUser = nullptr;
    string username;
    int roleChoice;
    
    cout << "========================================" << endl;
    cout << "   ROLE-BASED INVENTORY SYSTEM" << endl;
    cout << "========================================" << endl;
    
    Employee emp;
    Manager mgr;
    Admin admin;
    InventoryManager invMgr;
    
    vector<User*> users = { &emp,  &mgr,  &admin,  &invMgr };
    
    do {
        cout << "\nSelect your role: " << endl;
        cout << "1. Employee " << endl;
        cout << "2. Manager " << endl;
        cout << "3. Administrator " << endl;
        cout << "4. Inventory Manager " << endl;
        cout << "Enter choice (1-4):  ";
        cin >> roleChoice;
        
        if (roleChoice >= 1 && roleChoice <= 4) {
            currentUser = users[roleChoice - 1];
            cout << "\n--- LOGIN SUCCESSFUL ---" << endl;
            currentUser->accessLevel();
            break; 
        } else {
            cout << "Please try to enter within the range of numbers!" << endl;
        }
    } while (true); 
    
    int menuChoice;
    do {
        cout << "\nINVENTORY MENU: " << endl;
        
        if (dynamic_cast<Employee*>(currentUser)) {
            cout << "1. View Inventory" << endl;
            cout << "2. Logout" << endl;
        }
        if (dynamic_cast<Manager*>(currentUser)) {
            cout << "1. View Inventory" << endl;
            cout << "2. Add Item" << endl;
            cout << "3. Update Item" << endl;
            cout << "4. Logout" << endl;
        }
        if (dynamic_cast<Admin*>(currentUser)) {
            cout << "1. View Inventory" << endl;
            cout << "2. Add Item" << endl;
            cout << "3. Update Item" << endl;
            cout << "4. Delete Item" << endl;
            cout << "5. Logout" << endl;
        }
        if (dynamic_cast<InventoryManager*>(currentUser)) {
            cout << "1. View Inventory" << endl;
            cout << "2. Add Item" << endl;
            cout << "3. Update Item" << endl;
            cout << "4. Delete Item" << endl;
            cout << "5. Logout" << endl;
        }
        
        cout << "Enter choice:  ";
        cin >> menuChoice;
        
        if (dynamic_cast<Employee*>(currentUser)) {
            if (menuChoice == 1) {
                system.viewInventory();
            } else if (menuChoice == 2) {
                cout << "Logging out..." << endl;
                break;
            } else {
                cout << "Invalid choice!" << endl;
            }
        }
        
        if (dynamic_cast<Manager*>(currentUser)) {
            string item,  newItem;
            int index;
            
            switch(menuChoice) {
                case 1: 
                    system.viewInventory();
                    break;
                case 2: 
                    cout << "Enter item name to add:  ";
                    cin.ignore();
                    getline(cin,  item);
                    system.addItem(item);
                    break;
                case 3: 
                    system.viewInventory();
                    cout << "Enter item number to update:  ";
                    cin >> index;
                    cout << "Enter new item name:  ";
                    cin.ignore();
                    getline(cin,  newItem);
                    system.updateItem(index,  newItem);
                    break;
                case 4: 
                    cout << "Logging out..." << endl;
                    break;
                default: 
                    cout << "Invalid choice!" << endl;
                    continue;  
            }
        }
        
        if (dynamic_cast<Admin*>(currentUser) || dynamic_cast<InventoryManager*>(currentUser)) {
            string item,  newItem;
            int index;
            
            switch(menuChoice) {
                case 1: 
                    system.viewInventory();
                    break;
                case 2: 
                    cout << "Enter item name to add:  ";
                    cin.ignore();
                    getline(cin,  item);
                    system.addItem(item);
                    break;
                case 3: 
                    system.viewInventory();
                    cout << "Enter item number to update:  ";
                    cin >> index;
                    cout << "Enter item name:  ";
                    cin.ignore();
                    getline(cin,  newItem);
                    system.updateItem(index,  newItem);
                    break;
                case 4: 
                    system.viewInventory();
                    cout << "Enter item number to remove:  ";
                    cin >> index;
                    system.deleteItem(index);
                    break;
                case 5: 
                    cout << "Logging you out..." << endl;
                    break;
                default: 
                    cout << "Invalid choice!" << endl;
                    continue; 
            }
        }
        
    } while (menuChoice != 2 && menuChoice != 4 && menuChoice != 5);
    
    cout << "\nBye Bye!" << endl;
    return 0;
}
