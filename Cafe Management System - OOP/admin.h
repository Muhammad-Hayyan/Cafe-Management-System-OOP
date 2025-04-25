/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
#include "stock.h"
#include "notif.h"
#include "order.h"
#include "complaints.h"

using namespace std;

#ifndef ADMIN_H
#define ADMIN_H
class Admin : public Person
{
    string username, password;
    Stock S;                    //composed object of class stock
    Employee E;                 //composed object of class employee
    User U;                     //composed object of class user
    Notification N;             //composed object of class notification
    Complaints C;               //composed object of class complaints
    Order O;                    //composed object of class order

    public:
    Admin();
    Admin(string n, string p);
    bool login();                          //For Login
    void init();                           //For initialization
    void temp();                           //For temporary disp
    void stockdisp();                      //For stock disp
    void stocksearch();                    //For stock search
    void stockrem();                       //For stock remove
    void stockadd();                       //For stock add
    void stockorder();                     //For stock order
    void stockupdate();                    //For stock update
    void sortstock();                      //For sort stock

    void Employeedisplay();                //to display employees
    void EmpRem();                         //to remove employee
    void EmpAdd();                         //to add employee
    void EmpChange();                      //to change credentials of employee

    void Userdisp();                        //to display user
    void Useradd();                         //to add users
    void Userrem();                         //to remove user
    void Userchange();                      //to change credentials

    void Notifadd();                        //to add notification      
    void Notifrem();                        //to remove notification
    void Notifdisp();                       //to display notification

    void Compdisp();                        //to display complaints
    void Compread();                        //to read complaints

    void Warning();                         //to warn

    void Schmanage();                       //to manage schedule order
    
    void stats();                           //to display stats

};


#endif