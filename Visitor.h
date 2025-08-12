#ifndef VISITOR_H
#define VISITOR_H


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <iomanip>

#include "Student.h"

#define n 40
using namespace std;

class Visitor  {
    char id[20];
    char name[50];
    char phone_No[100];
    char whom_To_meet[100];
    char Entry_time[50];
    char Exit_time[50];
    public:
    
    void input() {
        cin.ignore(); 
        cout << "Enter Visitor Id: ";
        cin.getline(id, 20);
         
        cout << "Enter Visitor Name: " ;
        cin.getline(name, 50);
        cout << "Enter Visitor Phone Number: ";
        cin.getline(phone_No, 100);
        cout << "Whom To Meet: ";
        cin.getline(whom_To_meet, 100);
        cout << "Enter Entry Time: ";
        cin.getline(Entry_time, 50);
        cout << "Enter Exit Time: ";
        cin.getline(Exit_time, 50);


    }

    void display() {
    
    cout << "| "
         << left << setw(10) << id << " | "
         << left << setw(22) << name << " | "
         << left << setw(17) << phone_No << " | "
         << left << setw(22) << whom_To_meet << " | "
         << left << setw(19) << Entry_time << " | "
         << left << setw(19) << Exit_time << " |\n";

    
       }
static  bool studentexists(const char* id) {
    fstream f;
    StudentRecord rec;
    f.open("students.dat", ios::in | ios::binary);
    if (!f)
      return false;
   
    while (f.read((char*)&rec, sizeof(rec))) {
      if (strcmp(rec.StudentId, id) == 0) {
          f.close();
          return true;
      }
   }
   f.close();
   return false;
   }

       void addVisitor() {
        Visitor v;
        fstream f;
        cout << "Add Visitor\n";
        v.input();
    if (!studentexists(v.id)) {
    cout << "Student ID not found. so you can not meet from Student.\n";
    return;
    }

        f.open("Visitor_test.dat", ios::app | ios::binary );
        f.write((char*)&v, sizeof(v));
        f.close();
        cout <<"Visitor ID:-  "<< v.id << "  Now yo can meet from student..\n";

    }

    void viewVisitor() {
        Visitor v;
        fstream f;
        f.open("Visitor_test.dat", ios::in | ios::binary);
        if(!f) {
            cout << "No Visitor found.\n";
            f.close();
            return;
        }
        
        cout << "+------------+------------------------+-------------------+------------------------+---------------------+---------------------+\n";
        cout << "| Visitor ID | Visitor Name           | Phone Number      | Whom To Meet          | Entry Time          | Exit Time            |\n";
        cout << "+------------+------------------------+-------------------+------------------------+---------------------+---------------------+\n";

        while(f.read((char*)&v,sizeof(v))) {
            v.display();
        }
        cout << "+------------+------------------------+-------------------+------------------------+---------------------+---------------------+\n";
     f.close();
    }

    void updateVisitor() {
    fstream f;
    Visitor v;
    char id[20];
    bool found = false;

    cout << "Enter Visitor Id To Update: ";
    cin >> id;
    cin.ignore();

    f.open("Visitor_test.dat", ios::in | ios::out | ios::binary);
    if (!f) {
        cout << "Can not open file.\n";
        f.close();
        return;
    }

    while (f.read((char*)&v, sizeof(v))) {
        if (strcmp (v.id, id) == 0) {
            
            cout << "\nExisting Record:\n";
            cout << "+------------+------------------------+-------------------+------------------------+---------------------+---------------------+\n";
            cout << "| Visitor ID | Visitor Name           | Phone Number      | Whom To Meet          | Entry Time          | Exit Time           |\n";
            cout << "+------------+------------------------+-------------------+------------------------+---------------------+---------------------+\n";
            v.display();
            cout << "+------------+------------------------+-------------------+------------------------+---------------------+---------------------+\n";
            cout << "\nEnter new details:\n";
            v.input();
            
            streampos pos = f.tellg();
         f.seekp(pos - static_cast<std::streamoff>(sizeof(v)), ios::beg);


            f.write((char*)&v, sizeof(v));

            cout <<"Visitor ID:-  " << v.id << " Visitor Record Successfully Updated.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Visitor Id not found.\n";
    }

    f.close();
}

void deleteVisitor()  {
    Visitor v;
    char id[20];
    bool found = false;

    cout << "Enter Visitor ID to delete: ";
    cin >> id;
    cin.ignore();
    fstream f1, f2;
    f1.open("Visitor_test.dat", ios::in | ios::binary);
    f2.open("temp.dat", ios::out | ios::binary );
    if (!f1 || !f2 ) {
        cout << "Error opening file.\n";
        return;
    }
    while(f1.read((char*)&v, sizeof(v))) {
        if (strcmp(v.id, id) == 0)  {
           found = true;
        } else {
        f2.write((char*)&v, sizeof(v));
        }
    }
        f1.close();
        f2.close();
        remove("Visitor_test.dat");
        rename("temp.dat", "Visitor_test.dat");

        if (found) 
         cout << "Visitor ID:-  " << id << " Deleted Successfully..\n";
        else 
          cout << "Visitor Id Not Found.\n"; 

    
}

void visitorManagementMenu() {
    int choice;
    Visitor v;
    do {
        system("cls");
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n                                                                    VISITOR  MANAGEMENT                                                                                        \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "1. ADD VISITOR INFORMATION\n";
                cout << "2. SHOW VISITOR RECORDS\n";
                cout << "3. MODIFY EXISTING VISITORS DETAILS\n";
                cout << "4. REMOVE VISITOR ENTRY FROM RECORDS\n";
                cout << "5. BACK TO MAIN MENU\n";
                cout << "\033[1;36m\n===============================================================================================================================================================\033[0m\n";
                cout << "ENTER YOUR CHOICE: ";
                cin >> choice;

        switch(choice) {
            system("cls");
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n                                                                    VISITOR  MANAGEMENT                                                                                        \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
    case 1:     cout << "1.  *********************  ADD VISITOR INFORMATION    ********************* \n";
                v.addVisitor(); 
                break;
                system("cls");
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n                                                                    VISITOR  MANAGEMENT                                                                                        \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
    case 2:     cout << "2.  *********************  SHOW VIISITOR RECORDS    ********************* \n";
                v.viewVisitor(); 
                break;
                system("cls");
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n                                                                    VISITOR  MANAGEMENT                                                                                        \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
    case 3:     cout << "3.  *********************  MODIFY EXISTING VISITORS DETAILS     *********************\n ";
                v.updateVisitor(); 
                break;
                system("cls");
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n                                                                    VISITOR  MANAGEMENT                                                                                        \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
    case 4:     cout << "4.  ********************* REMOVE VISITOR ENTRY FROM RECORDS   ********************* \n";
                v.deleteVisitor(); 
                break;
    case 5:     return;

    default:    cout << "Invalid choice.\n";
       
                }
        system("pause");
    } while(choice!=5);
}
};

#endif

