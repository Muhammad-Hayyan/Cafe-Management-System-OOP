/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
#include "stock.h"

using namespace std;

#ifndef ORDER_H
#define ORDER_H
class Order
{
    string item;
    int amount;

    public:
        Order();
        Order(int a, string i);
        void add();
        void manage();

};

#endif