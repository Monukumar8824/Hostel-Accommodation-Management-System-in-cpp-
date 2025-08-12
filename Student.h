#ifndef STUDENT_H
#define STUDENT_H

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
#define n 40
using namespace std;
class Student {
    char StudentId[20];
    char roll[20];
    char name[50];
    char branch[50];
    char room[10];
    float totalFee, paidFee, dueFee;

public:
        Student() {
        strcpy(room, "NA");
        totalFee = paidFee = dueFee = 0.0f;
    }
 
    void input() {
        cin.ignore();
        cout << "Enter Student ID: ";
        cin.getline(StudentId, 20);

        cout << "Enter Roll No: ";
        cin.getline(roll, 20);

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Branch: ";
        cin.getline(branch, 50);

        cin.ignore(); 
    }

 void display() const {

    cout << "| "
         << left << setw(8) << StudentId << " | "
         << left << setw(12) << roll << " | "
         << left << setw(20) << name << " | "
         << left << setw(20) << branch << " | "
         << left << setw(6) << room << " | "
         << left << fixed << setw(18) << setprecision(2) << totalFee << " | "
         << left << fixed << setw(18) << setprecision(2) << paidFee << " | "
         << left << fixed << setw(18) << setprecision(2) << dueFee << " |\n";

    }

      void addStudent() {
        Student s;
        fstream f;
        s.input();

        f.open("students.dat", ios::in | ios::binary);
        if (f) {
        Student temp;
        while (f.read((char*)&temp, sizeof(temp))) {
            if (strcmp(temp.StudentId, s.StudentId) == 0) {
                cout << "\nStudent Id already exists.\n";
                f.close();
                return;
            }
        }
        f.close();
    }
        f.open("students.dat", ios::app | ios::binary);
        if (!f) {
            cerr << "Could not open file.\n";
            return;
        }
        f.write((char*)&s, sizeof(s));
        f.close();

        cout <<"Student ID:-  " << s.StudentId << "  added successfully.\n";
        cin.ignore();
    }


    void viewStudents() {
        Student s;
        fstream f;
        f.open("students.dat", ios::in | ios::binary);
        if (!f) {
            cout << "\nNo student records found.\n";
            cin.ignore();
            return;
        }
        cout << "\n======================================= All Students ===============================================\n";
        cout << "+----------+--------------+----------------------+----------------------+--------+--------------------+--------------------+--------------------+\n";
        cout << "| ID       | Roll         | Name                 | Branch               | Room   | Total Fee          | Paid Fee           | Due Fee            |\n";
        cout << "+----------+--------------+----------------------+----------------------+--------+--------------------+--------------------+--------------------+\n";
        while (f.read((char*)&s, sizeof(s))) {
            s.display();
        }
        cout << "+----------+--------------+----------------------+----------------------+--------+--------------------+--------------------+--------------------+\n";
        f.close();
        cin.ignore();
    }


    void updateStudent() {
        fstream f;
        f.open("students.dat", ios::in | ios::out | ios::binary);
        if (!f) {
            cerr << "could not open file.\n";
            return;
        }

        char target[20];
        cin.ignore();
        cout << "Enter Student Id to update: ";
        cin.getline(target, 20);

        Student s;
        bool found = false;
        while (f.read((char*)&s, sizeof(s))) {
            if (strcmp(s.StudentId, target) == 0) {
                cout << "\nExisting Record:\n";
                cout << "+----------+--------------+----------------------+----------------------+--------+--------------------+--------------------+--------------------+\n";
                cout << "| ID       | Roll         | Name                 | Branch               | Room   | Total Fee          | Paid Fee           | Due Fee            |\n";
                cout << "+----------+--------------+----------------------+----------------------+--------+--------------------+--------------------+--------------------+\n";
                s.display();
                cout << "+----------+--------------+----------------------+----------------------+--------+--------------------+--------------------+--------------------+\n";


                cout << "\nEnter new Roll No: ";
                cin.getline(s.roll, 20);

                cout << "Enter new Name   : ";
                cin.getline(s.name, 50);

                cout << "Enter new Branch : ";
                cin.getline(s.branch, 50);

                int pos = f.tellg();
                f.seekp(pos - sizeof(s), ios::beg);
                f.write((char*)&s, sizeof(s));
                f.close();

                cout <<"Student Id:-  "<< s.StudentId << "  Record updated successfully .\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\nStudent Id not found.\n";
        }
        
       cin.ignore();
    }



    void deleteStudent() {
        Student s;
        fstream f1,f2;
        char delId[20];
        cin.ignore();
        cout << "Enter Student Id to delete: ";
        cin.getline(delId, 20);

        f1.open("students.dat", ios::in | ios::binary);
        f2.open("temp.dat", ios::out| ios::binary);
        if (!f1 || !f2) {
            cerr << "could not open file.\n";
            return;
        }

        bool found = false;
        while (f1.read((char*)&s, sizeof(s))) {
            if (strcmp(s.StudentId, delId) != 0) {
                f2.write((char*)&s, sizeof(s));
            } else {
                found = true;
            }
        }
        f1.close(); 
        f2.close();

        remove("students.dat");
        rename("temp.dat", "students.dat");

        if (found)
            cout <<"Student ID:-  "<< s.StudentId << "  Record deleted successfully.\n";
        else
            cout << "\nStudent Id not found.\n";
        cin.ignore();
    }



void studentManagementMenu() {
    int choice;
    do {
        system("cls");
        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
        cout << "\033[1;34m\n                                                                 STUDENT MANAGEMENT                                                                                            \033[0m\n";
        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
        cout << "1. ADD STUDENT\n";
        cout << "2. VIEW STUDENTS\n";
        cout << "3. UPDATE STUDENT\n";
        cout << "4. DELETE STUDENT\n";
        cout << "5. BACK TO MAIN MENU\n";
        cout << "\033[1;36m\n===============================================================================================================================================================================\033[0m\n";
        cout << "ENTER YOUR CHOICE: " << endl;
        cin >> choice;

        switch(choice) {
            system("cls");
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;34m\n                                                                 STUDENT MANAGEMENT                                                                                            \033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
            case 1: cout << "1.  *********************  ADD STUDENT    *********************\n ";
                    addStudent(); 
                    break;
                    system("cls");
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;34m\n                                                                 STUDENT MANAGEMENT                                                                                            \033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
            case 2: cout << "2.  *********************  VIEW  STUDENT    *********************\n ";
                    viewStudents(); 
                    break;
                    system("cls");
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;34m\n                                                                 STUDENT MANAGEMENT                                                                                            \033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
            case 3: cout << "3.  *********************  UPDATE  STUDENT    *********************\n ";
                    updateStudent(); 
                    break;
                    system("cls");
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                    cout << "\033[1;34m\n                                                                 STUDENT MANAGEMENT                                                                                            \033[0m\n";
                    cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
            case 4: cout << "4.  *********************  DELETE  STUDENT    *********************\n ";
                    deleteStudent(); 
                    break;
            case 5: return;
            default: cout << "Invalid choice.\n";
        }
        system("pause");
    } while(choice!=5);
}
};

#endif
