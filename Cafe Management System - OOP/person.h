/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include<iostream>
using namespace std;

#include "main.h"

#ifndef PERSON_H
#define PERSON_H
class Person
{
	string username, password;
	
	public:
		Person();
		Person(string u, string p);
		virtual bool login();
		virtual void init();
		virtual void temp();
		virtual void stockdisp();
		virtual void stocksearch();
		virtual void sortstock();
		

};
#endif 
