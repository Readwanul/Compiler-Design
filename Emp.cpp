#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    string name;
    string employeeID;
    string department;
    string position;
    double salary;
};


void Filewrite(const Employee &employee) {
    ofstream outFile("employees.txt", ios::ate); // Append mode
        outFile << "Employee Information\n";
        outFile << "Name: " << employee.name << endl;
        outFile << "Employee ID: " << employee.employeeID << endl;
        outFile << "Department: " << employee.department << endl;
        outFile << "Position: " << employee.position << endl;
        outFile << "Salary: " << employee.salary << endl;
        outFile << "-----------------------\n";
        outFile.close();
        cout << "Employee information written to file successfully." << endl;

}

void readFile() {
    ifstream inFile("employees.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cerr << "Unable to open file" << endl;
    }
}

int main() {
    char choice;

    do {
        Employee employee;
        cout << "Enter employee name: ";
        getline(cin, employee.name);
        cout << "Enter employee ID: ";
        getline(cin, employee.employeeID);
        cout << "Enter department: ";
        getline(cin, employee.department);
        cout << "Enter position: ";
        getline(cin, employee.position);
        cout << "Enter salary: ";
        cin >> employee.salary;
        cin.ignore();
        Filewrite(employee);

        cout << "Add another employee? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');

    cout << "\nEmployee information from file:\n";
    readFile();

    return 0;
}
