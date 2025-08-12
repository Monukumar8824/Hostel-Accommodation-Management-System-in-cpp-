#ifndef STUDENTRECORD_H
#define STUDENTRECORD_H

#include <iostream>
using namespace std;
class StudentRecord  { 

    public:
    char StudentId[20]; // only data members in class StudentRecords
    char roll[20];
    char name[50];
    char branch[50];
    char room[10];
    float totalFee;
    float paidFee;
    float dueFee;
};

#endif