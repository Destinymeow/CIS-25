#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

//Define the Patient structure
struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string diagnosis;
};

// Function prototypes
void addPatient(Patient*& patients, int& count, int& capacity);
void displayPatients(const Patient* patients, int count);
int binarySearch(const Patient* patients, int count, int searchID);
void updatePatient(Patient* patients, int count);
void savePatientsToFile(const Patient* patients, int count);
void loadPatientsFromFile(Patient*& patients, int& count, int& capacity);
void displayMenu();
void sortPatients(Patient* patients, int count);

int main() {
    // Dynamic array using pointers
    int capacity = 100;
    int count = 0;
    Patient* patients = new Patient[capacity];
    
    // Load existing patients from file (if any)
    loadPatientsFromFile(patients, count, capacity);
    
    int choice;
    
    do {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                // Add Patient
                addPatient(patients, count, capacity);
                break;
                
            case 2:
                // Display Patients
                displayPatients(patients, count);
                break;
                
            case 3:
                // Search Patient (using binary search)
                if (count > 0) {
                    // Sort patients by ID before binary search
                    sortPatients(patients, count);
                    
                    int searchID;
                    cout << "Enter Patient ID to search: ";
                    cin >> searchID;
                    
                    int result = binarySearch(patients, count, searchID);
                    
                    if (result != -1) {
                        cout << "\nPatient Found:" << endl;
                        cout << "ID: " << patients[result].id << endl;
                        cout << "Name: " << patients[result].name << endl;
                        cout << "Age: " << patients[result].age << endl;
                        cout << "Gender: " << patients[result].gender << endl;
                        cout << "Diagnosis: " << patients[result].diagnosis << endl;
                        cout << endl;
                    } else {
                        cout << "\nPatient not found\n" << endl;
                    }
                } else {
                    cout << "\nNo patients in the system.\n" << endl;
                }
                break;
                
            case 4:
                // Update Patient
                updatePatient(patients, count);
                break;
                
            case 5:
                // Save Patients to file
                savePatientsToFile(patients, count);
                break;
                
            case 6:
                // Exit program
                cout << "Good Bye!" << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
    
    // Clean up dynamic memory
    delete[] patients;
    
    return 0;
}

// Add Patient
void addPatient(Patient*& patients, int& count, int& capacity) {
    if (count >= capacity) {
        // Expand array if needed
        int newCapacity = capacity * 2;
        Patient* newPatients = new Patient[newCapacity];
        
        // Copy existing patients
        for (int i = 0; i < count; i++) {
            newPatients[i] = patients[i];
        }
        
        delete[] patients;
        patients = newPatients;
        capacity = newCapacity;
        cout << "Array expanded to capacity: " << capacity << endl;
    }
    
    Patient newPatient;
    
    cout << "\nEnter Patient ID: ";
    cin >> newPatient.id;
    
    // Check for duplicate ID
    for (int i = 0; i < count; i++) {
        if (patients[i].id == newPatient.id) {
            cout << "Patient ID already exists. Please try again." << endl;
            return;
        }
    }
    
    cout << "Enter Patient Name: ";
    cin.ignore();
    getline(cin, newPatient.name);
    
    cout << "Enter Patient Age: ";
    cin >> newPatient.age;
    
    cout << "Enter Patient Gender: ";
    cin >> newPatient.gender;
    
    cout << "Enter Patient Diagnosis: ";
    cin.ignore();
    getline(cin, newPatient.diagnosis);
    
    patients[count] = newPatient;
    count++;
    
    cout << "\nPatient added successfully!\n" << endl;
    
    // Auto-save after adding
    savePatientsToFile(patients, count);
}

// Display Patients
void displayPatients(const Patient* patients, int count) {
    if (count == 0) {
        cout << "\nNo patients to display.\n" << endl;
        return;
    }
    
    cout << "\nPatient Records\n";
    cout << "==================================================" << endl;
    
    for (int i = 0; i < count; i++) {
        cout << "ID: " << patients[i].id << "  "
             << "Name: " << patients[i].name << "  "
             << "Age: " << patients[i].age << "  "
             << "Gender: " << patients[i].gender << "  "
             << "Diagnosis: " << patients[i].diagnosis << endl;
    }
    
    cout << "==================================================\n" << endl;
}

// Binary Search
int binarySearch(const Patient* patients, int count, int searchID) {
    int left = 0;
    int right = count - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        
        if (patients[mid].id == searchID)
            return mid;
        if (patients[mid].id < searchID)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return -1;
}

// Helper function to sort patients by ID
void sortPatients(Patient* patients, int count) {
    // Simple bubble sort for illustration
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (patients[j].id > patients[j + 1].id) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }
}

// Update Patient
void updatePatient(Patient* patients, int count) {
    if (count == 0) {
        cout << "\nNo patients in the system.\n" << endl;
        return;
    }
    
    int searchID;
    cout << "\nEnter patient ID to update: ";
    cin >> searchID;
    
    // Sort before searching
    sortPatients(patients, count);
    int index = binarySearch(patients, count, searchID);
    
    if (index != -1) {
        cout << "\nCurrent Patient Information:" << endl;
        cout << "ID: " << patients[index].id << endl;
        cout << "Name: " << patients[index].name << endl;
        cout << "Age: " << patients[index].age << endl;
        cout << "Gender: " << patients[index].gender << endl;
        cout << "Diagnosis: " << patients[index].diagnosis << endl;
        
        cout << "\nEnter new diagnosis: ";
        cin.ignore();
        getline(cin, patients[index].diagnosis);
        
        cout << "\nPatient information updated successfully!\n" << endl;
        
        // Auto-save after update
        savePatientsToFile(patients, count);
    } else {
        cout << "\nPatient not found.\n" << endl;
    }
}

// Save Patients to File
void savePatientsToFile(const Patient* patients, int count) {
    ofstream outFile("patients.txt");
    
    if (!outFile) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }
    
    for (int i = 0; i < count; i++) {
        outFile << patients[i].id << " "
                << patients[i].name << " "
                << patients[i].age << " "
                << patients[i].gender << " "
                << patients[i].diagnosis << endl;
    }
    
    outFile.close();
    cout << "Patients saved to patients.txt successfully.\n" << endl;
}

// Load Patients from File
void loadPatientsFromFile(Patient*& patients, int& count, int& capacity) {
    ifstream inFile("patients.txt");
    
    if (!inFile) {
        // File doesn't exist yet, that's okay
        return;
    }
    
    count = 0;
    Patient temp;
    
    while (inFile >> temp.id >> temp.name >> temp.age >> temp.gender >> temp.diagnosis) {
        if (count >= capacity) {
            // Expand array if needed
            int newCapacity = capacity * 2;
            Patient* newPatients = new Patient[newCapacity];
            
            for (int i = 0; i < count; i++) {
                newPatients[i] = patients[i];
            }
            
            delete[] patients;
            patients = newPatients;
            capacity = newCapacity;
        }
        
        patients[count] = temp;
        count++;
    }
    
    inFile.close();
    cout << "Loaded " << count << " patients from file.\n" << endl;
}

// Display Menu
void displayMenu() {
    cout << "\nHospital Patient System" << endl;
    cout << "1. Add Patient" << endl;
    cout << "2. Display Patients" << endl;
    cout << "3. Search Patient" << endl;
    cout << "4. Update Patient" << endl;
    cout << "5. Save Patients" << endl;
    cout << "6. Exit" << endl;
}