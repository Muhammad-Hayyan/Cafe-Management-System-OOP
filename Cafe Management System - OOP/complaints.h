/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
#include "stock.h"

using namespace std;

#ifndef COMPLAINTS_H
#define COMPLAINTS_H
class Complaints
{
    string comp;

    public:
        Complaints();
        Complaints(string c);
        void init();
        void disp();
        void add();
        void read();

};

#endif