#ifndef FEE_H
#define FEE_H


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

#include "StudentRecord.h"
#include "Student.h"
#include "Room.h"


#define n 40 // n is defined as number of rooms in the hostel and we can change it accordingly
using namespace std;

int Room::arr[n];
class Fee {
    public:


    void addFee() {
        fstream f;
        char target[20];
        cout << "Enter Student ID to initialize fees: ";
        cin >> target;
        cin.ignore();

        f.open("students.dat", ios::in | ios::out | ios::binary);
        if (!f) { 
            cerr << "Cannot open file\n"; 
            return; 
        }

        StudentRecord rec;
        bool found = false;
        while (f.read((char*)&rec, sizeof(rec))) {
            if (strcmp(rec.StudentId, target) == 0) {
                found = true;
                if (rec.totalFee != 0.0f || rec.paidFee != 0.0f) {
                    cout << "Fees already Added for this student.\n";
                } else {
                    cout << "\nAdd fees for " << rec.name
                         << " [" << rec.StudentId << "]\n";
                    cout << "Enter Total Fee: ";
                    cin  >> rec.totalFee;
                    cout << "Enter Paid Fee: ";
                    cin  >> rec.paidFee;
                    cin.ignore();

                    rec.dueFee = rec.totalFee - rec.paidFee;
                    if (rec.dueFee < 0) {
                        cout << "Paid More total due = 0\n";
                        rec.dueFee = 0;
                    }

                    int pos = f.tellg();
                    f.seekp(pos - sizeof(rec), ios::beg);
                    f.write((char*)&rec, sizeof(rec));
                    cout << "Student ID:-  "<<rec.StudentId << " Fees Added.\n";
                }
                break;
            }
        }
        if (!found) 
        cout << "Student ID not found.\n";
        f.close();
        cin.ignore();
    }


    void updatePaidFee() {
        fstream f;
        cout << "Enter Student ID to update paid fee: ";
        char target[20];
        cin >> target;
        cin.ignore();

        f.open("students.dat", ios::in|ios::out|ios::binary);
        if (!f) { cout << "Cannot open file\n"; 
            return; 
        }

        StudentRecord rec;
        float addFee;
        bool found = false;
        while (f.read((char*)&rec, sizeof(rec))) {
            if (strcmp(rec.StudentId, target) == 0) {
                found = true;
       cout << "+----------------------+---------------+---------------+---------------+\n";
       cout << "| Student Name         | Total Fee     | Paid Fee      | Due Fee       |\n";
       cout << "+----------------------+---------------+---------------+---------------+\n";

       cout << "| "
            << left << setw(20) << rec.name << " | "
            << left << setw(13) << fixed << setprecision(2) << rec.totalFee << " | "
            << left << setw(13) << fixed << setprecision(2) << rec.paidFee << " | "
            << left << setw(13) << fixed << setprecision(2) << rec.dueFee << " |\n";

       cout << "+----------------------+---------------+---------------+---------------+\n";
                cout << "Enter New Paid Fee: ";
                cin  >> addFee;
                cin.ignore();

                rec.paidFee += addFee;
                rec.dueFee = rec.totalFee - rec.paidFee;
                if (rec.dueFee < 0) {
                    cout << "Paid More total  due = 0\n";
                    rec.dueFee = 0;
                }
               
                int pos = f.tellg();
                f.seekp(pos - sizeof(rec), ios::beg);
                f.write((char*)&rec, sizeof(rec));
                cout <<"Student ID:- " << rec.StudentId << " Paid fee updated.\n";
                break;
            }
        }
        if (!found) cout << "Student ID not found.\n";
        f.close();
       cin.ignore();
    }



    void viewAllFees() {
        fstream f;
        f.open("students.dat", ios::in|ios::binary);
        if (!f) { cout << "No records.\n"; 
            return; 
        }

        StudentRecord rec;
        cout << "\n=================================== All Fee Records ===================================\n";
        cout << "+------------+----------------------+---------------+---------------+---------------+\n";
        cout << "| Student ID | Name                 | Total Fee     | Paid Fee      | Due Fee       |\n";
        cout << "+------------+----------------------+---------------+---------------+---------------+\n";
        while (f.read((char*)&rec, sizeof(rec))) {
    cout << "| "
         << left << setw(10) << rec.StudentId << " | "
         << left << setw(20) << rec.name << " | "
         << left << setw(13) << fixed << setprecision(2) << rec.totalFee << " | "
         << left << setw(13) << fixed << setprecision(2) << rec.paidFee << " | "
         << left << setw(13) << fixed << setprecision(2) << rec.dueFee << " |\n";

        }
        cout << "+------------+----------------------+---------------+---------------+---------------+\n";
        f.close();
        cin.ignore();
    }


    void searchFee() {
        fstream f;
        cout << "Enter Student ID to search: ";
        char target[20];
        cin.getline(target, 20);
        cin.ignore();

        f.open("students.dat", ios::in | ios::binary);
        if (!f) { cout << "No records.\n"; return; }

        StudentRecord rec;
        bool found = false;
        while (f.read((char*)&rec, sizeof(rec))) {
            if (strcmp(rec.StudentId, target) == 0) {
                found = true;
    cout << "+------------+----------------------+---------------+---------------+---------------+\n";
    cout << "| Student ID | Name                 | Total Fee     | Paid Fee      | Due Fee       |\n";
    cout << "+------------+----------------------+---------------+---------------+---------------+\n";


    cout << "| "
         << left << setw(10) << rec.StudentId << " | "
         << left << setw(20) << rec.name << " | "
         << left << setw(13) << fixed << setprecision(2) << rec.totalFee << " | "
         << left << setw(13) << fixed << setprecision(2) << rec.paidFee << " | "
         << left << setw(13) << fixed << setprecision(2) << rec.dueFee << " |\n";

    cout << "+------------+----------------------+---------------+---------------+---------------+\n";
            }
        }
        if (!found) cout << "Record not found.\n";
        f.close();
        cin.ignore();
    }

    
   void checkFullyPaid() {
    char target[20];
    cout << "Enter Student ID to check: ";
    cin.getline(target, 20);
    fstream f;
    f.open("students.dat", ios::in | ios::binary);
    if(!f) {
        cerr << "can not open\n";
        return;
    }

    
    StudentRecord rec;
    bool found = false;
    while (f.read((char*)&rec, sizeof(rec))) {
        if (strcmp(rec.StudentId, target) == 0) {
            found = true;
            if (rec.dueFee == 0) {
                cout << " Yes, Student ID " << rec.StudentId 
                     << " (" << rec.name << ") has fully paid the fee.\n";
            } else {
                cout << " No, Student ID " << rec.StudentId 
                     << " (" << rec.name << ") still has due fee: " 
                     << rec.dueFee << "\n";
            }
            break;
            }
        }
        if (!found) {
            cout << "No record found for Student ID: " << target << "\n";
        }
        f.close();
    

   }


    void generateReport() {
        fstream f;
        f.open("students.dat", ios::in|ios::binary);
        if (!f) { cout<<"No records.\n"; 
            return; 
        }

        int   countPaid=0, countDue=0;
        float sumPaid=0,  sumDue=0;
        StudentRecord rec;
        while (f.read((char*)&rec, sizeof(rec))) {
            if (rec.dueFee == 0) { 
                countPaid++; 
                sumPaid += rec.paidFee;
             }
            else { 
                countDue++;  
                sumDue  += rec.dueFee; 
            }
        }
        f.close();

        cout << "\n============================ Fee Summary ============================\n";
        cout <<"\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "Fully Paid   : " << countPaid   << " | "
             << "With Due     : " << countDue    << " | "
             << "Total Paid   : Rs. " << sumPaid << " | "
             << "Total Due    : Rs. " << sumDue  << endl;
        cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cin.ignore();
    }

    void feeManagementMenu() {
        int choice;
        char target;
        do {
            system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                FEE  MANAGEMENT                                                                                                \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
            cout << "1. ADD(INITIALIZE) FEE\n"
                 << "2. UPDATE PAID FEE\n"
                 << "3. VIEW ALL FEES\n"
                 << "4. SEARCH FEE\n"
                 << "5. CHECK FULLY-PAID\n"
                 << "6. SUMMARY REPORT\n"
                 << "7. BACK TO MAIN MENU\n";
            cout << "\033[1;36m\n===============================================================================================================================================================================\033[0m\n";  
            cout << "ENTER YOUR CHOICE: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                        system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                FEE  MANAGEMENT                                                                                                \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 1: cout << "1.  *********************  ADD FEE    *********************\n ";
                        addFee();         
                        break;
                        system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                FEE  MANAGEMENT                                                                                                \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 2: cout << "2.  *********************  UPDATE  PAID FEE    *********************\n ";
                        updatePaidFee();  
                        break;
                        system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                FEE  MANAGEMENT                                                                                                \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 3: cout << "3.  *********************  VIEW ALL FEES    *********************\n ";
                        viewAllFees();    
                        break;
                        system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                FEE  MANAGEMENT                                                                                                \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 4: cout << "4.  *********************  SEARCH  FEE    *********************\n ";
                        searchFee();      
                        break;
                        system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                FEE  MANAGEMENT                                                                                                \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 5: cout << "5.  *********************  CHECK FULLY PAID FEE RECORDS    *********************\n ";
                        checkFullyPaid(); 
                        break;
                        system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                FEE  MANAGEMENT                                                                                                \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 6: cout << "6.  *********************  GENERATE FEE REPORT   *********************\n ";
                        generateReport(); 
                        break;
                case 7: return;
                default: cout<<"Invalid choice.\n";
                cin.ignore();
            } system("pause");
        } while (true);
    }
};

#endif

