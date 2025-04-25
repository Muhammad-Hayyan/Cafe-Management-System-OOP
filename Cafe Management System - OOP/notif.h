/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
#include "stock.h"

using namespace std;

#ifndef NOTIFICATION_H
#define NOTIFICATION_H
class Notification
{
    string notif;

    public:
        Notification();
        Notification(string n);
        void init();
        void disp();
        void add();
        void rem();
        void notify();

};

#endif