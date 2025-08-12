#ifndef ROOM_H
#define ROOM_H


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
#include "StudentRecord.h"
#define n 40
using namespace std;


class Room {
    static int arr[n];  // 0 = free, 1 = occupied

    void pause() {   // only print one message sothat press the enter button then move to forward
        cout << "\nPress Enter to continue...";
        
    }
    void syncOccupancy() {
        fstream f;
        f.open("students.dat", ios::in | ios::binary);
        if (!f) 
          return;
        StudentRecord rec;
        while (f.read((char*)&rec, sizeof(rec))) {
            if (strcmp(rec.room, "NA") != 0) { // student room not NA so room found
                int idx = atoi(rec.room) - 1; // convert room string into integer ("3" - 3) // (-1 means index array start from 0)
                if (idx >= 0 && idx < n) 
                arr[idx] = 1;  // if index valid so occupied mark
            }
        }
        f.close();
    }

public:
    Room() { 
        static bool initialized = false;
        if (!initialized) {
            for (int i = 0; i < n; ++i) arr[i] = 0;
            syncOccupancy();
            initialized = true;
        }
    }

    bool checkAvailability() const {
        for (int i = 0; i < n; ++i) 
        if (arr[i] == 0) 
        return true;
        return false;
    }

    void allocateRoom() {
        if (!checkAvailability()) { // if any room not free then print the message all rooms are allocated and return.
            cout << "All rooms are allocated.\n";
            return;
        }

        char id[20];
        cin.ignore();
        cout << "Enter Student Id: ";
        cin.getline(id, 20);

        fstream f1,f2;
        f1.open("students.dat", ios::in | ios::binary); //for read the old data from f1 file open
        f2.open("temp.dat",  ios::out | ios::binary);   // open the f2 file for write the updated data
        if (!f1 || !f2) {
            cout << "No open file.\n";  //if no file open then return
            return;
        }

        StudentRecord rec;
        bool found = false;
        while (f1.read((char*)&rec, sizeof(rec))) { // check the every student record
            if (!found && strcmp(rec.StudentId, id) == 0) { // if match the id and before not room NA means already allocated room and return
                 if(strcmp(rec.room,"NA")!=0){
                cout<<"Room Already Allocated "<<endl;
                return;
            }
                found = true;  
                for (int i = 0; i < n; ++i) {
                    if (arr[i] == 0) { //otherwise find the first free room
                        arr[i] = 1;  
                        sprintf(rec.room, "%d", i + 1); // save in string instead of print on console because we cannot assign direct integer into string because i have to store in string
                        cout << "Allocated Room " << (i + 1)  
                             << " to " << rec.name << "\n";// Assign the room number
                        break;
                    }      // print the message to User
                }
            }
            f2.write((char*)&rec, sizeof(rec));  
        }
        f1.close();
        f2.close();

        remove("students.dat");  // delete the old file then rename to temp file
        rename("temp.dat", "students.dat");

        if (!found)   // if student didnot found then print the message
            cout << "Student not found.\n";
    }

    void deallocateRoom() {
        int r;
        cout << "Enter Room number to free: ";  // take the room number from user
        cin >> r;
        cin.ignore();

        if (r < 1 || r > n || arr[r - 1] == 0) {  // first do the validation then if invalid or already free room so then return 
            cout << "Invalid or already free room.\n";
            return;
        }
        arr[r - 1] = 0; // does Room free mark 

        fstream f1,f2;
        f1.open("students.dat", ios::in | ios::binary);
        f2.open("temp.dat",  ios::out | ios::binary);
        if (!f1 || !f2) {
            cout << "Not open file.\n";
            return;
        }

        StudentRecord rec;
        while (f1.read((char*)&rec, sizeof(rec))) {
            if (atoi(rec.room) == r) {
                strcpy(rec.room, "NA"); // if student room same so done the 'NA'
            }                             // and all remaining unchanged
            f2.write((char*)&rec, sizeof(rec));
        }
        f1.close();
        f2.close();

        remove("students.dat");
        rename("temp.dat", "students.dat");

        cout << "Room " << r << " deallocated.\n";   // does the file updated and confirm the message
    }

    void showAllocatedRooms() const {
        cout << "Allocated Rooms:\n";
        for (int i = 0; i < n; ++i)
            if (arr[i] == 1)  // occupied room printed
                cout << "Room " << (i + 1) << "\n";
    }

    void showFreeRooms() const {
        cout << "\n+-----------------+\n";
        cout << "|   Free Rooms      |\n";
        cout << "+-------------------+\n";
        for (int i = 0; i < n; ++i)
            if (arr[i] == 0)
               cout << "| Room " << setw(2) << (i + 1) << "        |\n";
               cout << "+-----------------+\n";
    }

    void showAllInfo() const {
        fstream f;
        f.open("students.dat", ios::in | ios::binary);
        if (!f) {
            cout << "not open file.\n";
            return;
        }

        StudentRecord rec;
        cout << "All Students:\n";
    cout << "+------------+----------------------+--------+\n";
    cout << "| Student ID | Name                 | Room   |\n";
    cout << "+------------+----------------------+--------+\n";
        while (f.read((char*)&rec, sizeof(rec))) {
    cout << "| "
         << left << setw(10) << rec.StudentId << " | "
         << left << setw(20) << rec.name      << " | "
         << left << setw(6)  << rec.room      << " |\n";
        }
    cout << "+------------+----------------------+--------+\n";   
        f.close();
    }

    void roomManagementMenu() {
        int choice;
        // system("cls");
        // while (true) 
        do 
        {
            system("cls");
            cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
            cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
            cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
            cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
            cout << "\033[1;34m\n                                                                    ROOM MANAGEMENT                                                                                            \033[0m\n";
            cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
            cout << "1. ALLOCATE ROOM\n";
            cout << "2. DEALLOCATE ROOM\n";
            cout << "3. SHOW ALLOCATED ROOM\n";
            cout << "4. SHOW FREE ROOMS\n" ;
            cout << "5. SHOW ALL STUDENT ROOM INFORMATION\n";
            cout << "6. EXIT\n";
            cout << "\033[1;36m\n==============================================================================================================================================================================\033[0m\n";
            cout << "ENTER YOUR CHOICE: ";
            cin >> choice;

            switch (choice) {
                         system("cls");
                         cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                         cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                         cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                         cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                         cout << "\033[1;34m\n                                                                    ROOM MANAGEMENT                                                                                            \033[0m\n";
                         cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 1:  cout << "1.  *********************  ALLOCATE  ROOM    *********************\n ";
                         allocateRoom(); 
                         break;
                         system("cls");
                         cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                         cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                         cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                         cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                         cout << "\033[1;34m\n                                                                    ROOM MANAGEMENT                                                                                            \033[0m\n";
                         cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 2:  cout << "2.  *********************  DELLOCATE  ROOM    *********************\n ";
                        {
                         deallocateRoom();
                         break;
                        }
                        system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                    ROOM MANAGEMENT                                                                                            \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 3: cout << "3.  *********************  SHOW ALLOCATED  ROOM    *********************\n ";
                        showAllocatedRooms(); 
                        break;
                        system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                    ROOM MANAGEMENT                                                                                            \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 4: cout << "4.  *********************  SHOW  FREE  ROOMS    *********************\n ";
                        showFreeRooms(); 
                        break;
                        system("cls");
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                        cout << "\033[1;34m\n                                                                    ROOM MANAGEMENT                                                                                            \033[0m\n";
                        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 5: cout << "5.  *********************  SHOW ALL ROOM INFORMATION    *********************\n ";
                        showAllInfo(); 
                        break;
                case 6: return;
                default: cout << "Invalid choice. Try again.\n";
            } system("pause");
        }while(choice!=6);
    } 
};

#endif