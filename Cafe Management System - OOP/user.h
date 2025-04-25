/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
#include "complaints.h"
#include "notif.h"
#include "stock.h"
#include "order.h"

using namespace std;

#ifndef USER_H
#define USER_H
class User : public Person
{
    string username, password;
    Complaints C;
    Notification N;
    Stock S;
    Order O;

    public:
    User();
    User(string n);
    bool login();
    void init();
    void temp();
    void disp();
    void add();
    void rem();
    void change();

    void Compadd();

    void notify();

    void stockdisp();
    void stocksearch();
    void sortstock();

    void schedule();


};


#endif