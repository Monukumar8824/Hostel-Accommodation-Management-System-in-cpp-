#ifndef SECURITY_H
#define SECURITY_H

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
class Security{      
    int Id;
    char Full_name[100];
    char phone_number[100];
    char Adhaar_no[100];
    char Address[100];
    public:
       void input() {   // take the data from user
        cout << "Enter Guard Id: ";
        cin >> Id;
        cin.ignore();  
        cout << "Enter Full Name: ";
        cin.getline(Full_name, 100);
        cout << "Enter Phone Number: ";
        cin.getline(phone_number, 100);
        cout << "Enter Adhaar Number: ";
        cin.getline(Adhaar_no, 100);
        cout << "Enter Address: ";
        cin.getline(Address, 100);
    
    }
    
    void display() {
   

    cout << "| "
         << left << setw(8)  << Id << " | "
         << left << setw(24) << Full_name << " | "
         << left << setw(17) << phone_number << " | "
         << left << setw(22) << Adhaar_no << " | "
         << left << setw(27) << Address << " |\n";

    
}

    void addGuard(){
       Security s;
       fstream f;
       f.open("Security_test.dat",ios::app | ios::binary);
       cin.ignore();
       s.input();
       f.write((char*)&s, sizeof(s));
       f.close();
       cout <<"Guard ID:-  "<< s.Id << "  Security Guard Added Successfully..\n";

    }
    void viewGuard() {
        Security s;
        fstream f;
        f.open("Security_test.dat", ios::in | ios::binary);
        if(!f) {
            cout << "No Guard found.\n";
            f.close();
            return;
        }
         cout << "+----------+--------------------------+-------------------+------------------------+-----------------------------+\n";
         cout << "| Guard ID | Full Name                | Phone Number      | Adhaar Number         | Address                      |\n";
         cout << "+----------+--------------------------+-------------------+------------------------+-----------------------------+\n";
        while(f.read((char*)&s,sizeof(s))) {
            s.display();
        }
        cout << "+----------+--------------------------+-------------------+------------------------+-----------------------------+\n";
     f.close();
    }
void updateGuard() {
    fstream f;
     Security s;
    int id;
    bool found = false;

    cout << "Enter Security Guard Id To Update: ";
    cin >> id;

    f.open("Security_test.dat", ios::in | ios::out | ios::binary);
    if (!f) {
        cout << "Can not open file.\n";
        f.close();
        return;
    }

    while (f.read((char*)&s, sizeof(s))) {
        if (s.Id == id) {
            
            cout << "\nExisting Record:\n";
            cout << "+----------+--------------------------+-------------------+------------------------+-----------------------------+\n";
            cout << "| Guard ID | Full Name                | Phone Number      | Adhaar Number         | Address                      |\n";
            cout << "+----------+--------------------------+-------------------+------------------------+-----------------------------+\n";
            s.display();
            cout << "+----------+--------------------------+-------------------+------------------------+-----------------------------+\n";
            cout << "\nEnter new details:\n";
            s.input();
            
            int pos = f.tellg();
            f.seekp (pos - sizeof(s), ios::beg);

            f.write((char*)&s, sizeof(s));

            cout <<"Guard ID: " <<s.Id << " Record Successfully Updated.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Guard Id not found.\n";
    }

    f.close();
}
void deleteGuard() {
    Security s;
    int id;
    bool found = false;

    cout << "Enter Guard ID to delete: ";
    cin >> id;

    fstream f1, f2;
    f1.open("Security_test.dat", ios::in | ios::binary);  
    f2.open("temp.dat", ios::out | ios::binary);

    if (!f1 || !f2) {
        cout << "Can not open file.\n";
        f1.close();
        f2.close();

        return;
    }

    while (f1.read((char*)&s, sizeof(s))) {
        if (s.Id != id) {
            f2.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    f1.close();
    f2.close();

    remove("Security_test.dat");                 
    rename("temp.dat", "Security_test.dat");   

    if (found)
        cout << "Guard ID " << id << " Deleted Successfully..\n";
    else
        cout << "Guard Id Not Found.\n";
}

void securityManagementMenu() {
    Security s;
    int choice;
    do {
        system("cls");
        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
        cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
        cout << "\033[1;34m\n                                                              SECURITY  MANAGEMENT                                                                                             \033[0m\n";
        cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
        cout << "1. ADD GUARD\n";
        cout << "2. VIEW GUARD\n";
        cout << "3. UPDATE GUARD\n";
        cout << "4. DELETE GUARD\n";
        cout << "5. BACK TO MAIN MENU\n";
        cout << "\033[1;36m\n==============================================================================================================================================================================\033[0m\n";
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;
        cin.ignore();
                
                switch (choice) {
                         system("cls");
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n                                                              SECURITY  MANAGEMENT                                                                                             \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";          
                case 1: cout << "1.  *********************  ADD GUARD    ********************* \n";
                        s.addGuard();
                        break;
                        system("cls");
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n                                                              SECURITY  MANAGEMENT                                                                                             \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";        
                case 2: cout << "2.  *********************  VIEW GUARD    *********************\n ";
                        s.viewGuard(); 
                        break;
                        system("cls");
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n                                                              SECURITY  MANAGEMENT                                                                                             \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";                
                case 3: cout << "3.  *********************  UPDATE GUARD   *********************\n ";
                        s.updateGuard(); 
                        break;
                        system("cls");
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n\n                                                        HOSTEL ACCOMMODATION MANAGEMENT SYSTEM                                                                               \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                cout << "\033[1;34m\n                                                              SECURITY  MANAGEMENT                                                                                             \033[0m\n";
                cout << "\033[1;33m\n===============================================================================================================================================================================\033[0m\n";
                case 4: cout << "4.  *********************  DELETE GUARD    *********************\n ";
                        s.deleteGuard();
                        break;
                case 5: return;
                
                default: cout << "Invalid choice.\n";

        }
        system("pause");
    } while(choice!=5);
}

};


#endif
