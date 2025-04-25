/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"

using namespace std;

#ifndef STOCK_H
#define STOCK_H
class Stock 
{
    string item;
    int ID;
    int price;
    int amount;

    public:
        Stock();
        Stock(int i, string n, int p, int a);
        void init();
        void disp();
        void search();
        void rem();
        void add();
        void order();
        void update();
        void sort();
        void Warn();

        void salesinit();
        void salesdisp();

        friend ostream& operator<<(ostream& , Stock&);              //operator overloading <<


};

#endif