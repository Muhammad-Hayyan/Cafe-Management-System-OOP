/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include<iostream>
#include<cstring>
#include "main.h"
#include "stock.h"
#include "notif.h"
#include "order.h"

using namespace std;

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
class Employee : public Person
{
	string name;
	int ID;
	string password;
	Stock S;
	Notification N;
	Order O;
	
	public:
		Employee();
		Employee(string n, int i, string p);
		bool login(int&);
		void getData ();
		void showData() const;	
		void init();
		void temp();
		void disp();
		void rem();
		void add();
		void change();
		int order();

		void stockdisp();
		void stocksearch();
		void sortstock();

		void salesinit();
		void salesdisp();
		void Updsales(int, int);

		void notify();

		void schmanage();
};


#endif
