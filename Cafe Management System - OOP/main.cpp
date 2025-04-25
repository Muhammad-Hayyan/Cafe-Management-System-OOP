/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
using namespace std;


/*					Project Classes Map: 

					-> Person = Base class
					-> Admin , Employee, User are inherited from Person
					-> Applied polymorphism to mutual functions like login, stock display, stock search etc
					-> Stock class is composed in Admin, employee and user
					-> Notification class is composed in Admin, Employee and user
					-> Order class is composed in Admin, Employee and User
					-> Complaints class is composed in Admin and User								*/


//operator overloading
ostream& operator<<(ostream& out , Stock&s)
{
	 ifstream fin;
	fin.open("stock.dat" , ios::in | ios::binary);
	fin.seekg(0);					//starts with the beginning of file
    

	//Now we will read first the size, then make a temp array to read string then delete that array
	 while (!fin.eof()) 
     {
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
        if (fin.eof()) // Break loop if end of file
            break;

        // Allocate memory for name and read from file
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);
        s.item = nameBuffer;
        delete[] nameBuffer;

        fin.read(reinterpret_cast<char*>(&s.ID) , sizeof(s.ID));
        fin.read(reinterpret_cast<char*>(&s.price) , sizeof(s.price));
        fin.read(reinterpret_cast<char*>(&s.amount) , sizeof(s.amount));

        
        //Now displaying stock

        cout<<"\t\tID\tITEM\tPRICE\tAMOUNT\tTOTAL_WORTH"<<endl;
        if(s.amount == 0)		//yellow color if item is zero
		{
			cout<<endl;
			cout<<"\033[93;40;1m\t\t"<<s.ID<<"\t"<<s.item<<"\t"<<s.price<<"\t"<<s.amount<<"\t"<<s.amount*s.price<<"\n\033[0m";
		}
        else if(s.amount < 10)		//red color if item is less than 10
		{
			cout<<endl;
            cout<<"\033[91;40;1m\t\t"<<s.ID<<"\t"<<s.item<<"\t"<<s.price<<"\t"<<s.amount<<"\t"<<s.amount*s.price<<"\n\033[0m";
        }
        
        else
        {
            cout<<endl;
            cout<<"\t\t"<<s.ID<<"\t";
            cout<<s.item<<"\t";
            cout<<s.price<<"\t";
            cout<<s.amount<<"\t";
            cout<<s.amount*s.price<<"\n";
        }
            cout<<"\t\t___________________________________________"<<endl;
        
    }
	fin.close();

	return out;

}
int main()
{
	
	
	Person *P[4];								//For complete polymorphism
	
	P[0] = new Person;
 	P[1] = new Admin;
	P[2] = new Employee;
	P[3] = new User;

	Stock S1;
	Admin A1;
	Employee E1;
	User U1;
	Order O1;
	
	
	bool x=0, x1=0, x3=0, stock=0, emp=0, main=0, logout=0;
	int c1, c2, c3, c4, c5, a=0, item_sold=0;
	
	
	do
	{
	//Printing Menu
	
	cout<<endl<<endl;
	cout<<"\033[97;104;1\t\t\tm  --------------------------------------------------------------------------------------------------------------   \033[0m\n\n\n";
    	cout<<"\033[94;40;1\t\t\tm   _       __________    __________  __  _________   __________     _________   ___________   __________  _____   \033[0m\n";
    	cout<<"\033[94;40;1\t\t\tm  | |     / / ____/ /   / ____/ __ \\/  |/  / ____/  /_  __/ __ \\   / ____/   | / ___/_  __/  / ____/ __ \\/ ___/   \033[0m\n";
    	cout<<"\033[94;40;1\t\t\tm  | | /| / / __/ / /   / /   / / / / /|_/ / __/      / / / / / /  / /_  / /| | \\__ \\ / /    / /   / / / /\\__ \\    \033[0m\n";
    	cout<<"\033[94;40;1\t\t\tm  | |/ |/ / /___/ /___/ /___/ /_/ / /  / / /___     / / / /_/ /  / __/ / ___ |___/ // /    / /___/ /_/ /___/ /    \033[0m\n";
    	cout<<"\033[94;40;1\t\t\tm  |__/|__/_____/_____/\\____/\\____/_/  /_/_____/    /_/  \\____/  /_/   /_/  |_/____//_/     \\____/_____//____/     \033[0m\n\n\n";  
    	cout<<"\033[97;104;1\t\t\tm  --------------------------------------------------------------------------------------------------------------  \033[0m\n";
    
    	cout<<endl<<endl;
	cout<<"\033[93;40;1m\n\t1.\033[0m";
	cout<<" Admin\n";
	cout<<"\033[93;40;1m\n\t2.\033[0m";
	cout<<" Employee\n";
	cout<<"\033[93;40;1m\n\t3.\033[0m";
	cout<<" Student / Staff\n";
	cout<<"\033[93;40;1m\n\t4.\033[0m";
	cout<<" Exit CDS\n";
	cout<<"\n Select one of the options to login (1 - 4) : ";
	cin>>c1;
	
	switch (c1)
	{
		case 1:
			do
			{
			
			//cout << "\033[93;40;1m\n\n\tEnter Admin ID: \033[0m";
			x = P[1]->login();
			
			if (x==1)
			{
				cout << "\033[94;40;1m\n\n________________________________________________________________________________\n\n\n\n\033[0m";
				cout << "\033[94;107;1m\t   [  Welcome! Admin  ]  \t\033[0m"<<endl<<endl<<endl;
				
				do
				{
				
				cout<<"\n\t1. Manage Stock"<<endl;
				cout<<"\n\t2. Manage Employees / Users credentials"<<endl;
				cout<<"\n\t3. Manage Notifications"<<endl;
				cout<<"\n\t4. Manage Online / Scheduled orders"<<endl;
				cout<<"\n\t5. Manage Complaints"<<endl;
				cout<<"\n\t6. See Statistics"<<endl;
				cout<<"\n\t7. Logout"<<endl;
				A1.Warning();
				cout<<"\n\n Select any Option (1-7) : ";
				cin>>c2;
				
				switch (c2)
				{
					//case for stock
					
					case 1:
						do
						{
							cout<<"\n\t1. Display all Items"<<endl;
							cout<<"\n\t2. Search an Item"<<endl;
							cout<<"\n\t3. Remove an Item"<<endl;
							cout<<"\n\t4. Add an Item"<<endl;
							cout<<"\n\t5. Order Items"<<endl;
							cout<<"\n\t6. Update stock"<<endl;
							cout<<"\n\t7. Sort Stock"<<endl;
							cout<<"\n\t8. Go Back to main menu"<<endl;
							cout<<"\n\n Select Any Option (1-8) : ";
							cin>>c3;
							cout<<endl;
							switch (c3)
							{
								case 1:
									P[1]->stockdisp();
									cout<<"\033[34;40;1m\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 2:
									P[1]->stocksearch();
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 3:
									A1.stockrem();
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 4:
									A1.stockadd();
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 5:
									A1.stockorder();
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 6:
									A1.stockupdate();
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 7:
									P[1]->sortstock();
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 8:
									stock=1;
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
									break;
									
								default:
								cout<<"\033[91;40;1m\n\nInvalid Input! Please enter a number between 1 and 8\n\n\033[0m"<<endl;
									cin.clear();			//this is too validate input if alphaet is entered
									cin.ignore(100, '\n');
									break;
							}
						} while (stock==0);
						break;
						
					//case for employees and users credentials
					
					case 2:
						do
						{
							cout<<"\n\t1. See employees information and credentials"<<endl;
							cout<<"\n\t2. Manage employees credentials"<<endl;
							cout<<"\n\t3. Manage Users credentials"<<endl;
							cout<<"\n\t4. Go back to main menu"<<endl;
							cout<<"\n\n Select Any Option (1-3) : ";
							cin>>c3;
							
							switch(c3)
							{
								case 1:
									cout<<"\n__________________________________________________\n";
									A1.Employeedisplay();
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 2:
								
								do
								{
									cout<<"\n\t1. Change Credentials"<<endl;
									cout<<"\n\t2. Remove Credentials"<<endl;
									cout<<"\n\t3. Add New Employee Credentials"<<endl;
									cout<<"\n\t4. Go back"<<endl;
									cout<<"\n\n Select Any Option (1-4) : ";
									cin>>c4;
									
									switch(c4)
									{
										case 1:
											cout<<"\n__________________________________________________\n";
											A1.Employeedisplay();
											A1.EmpChange();
								cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
											// E1.salesdisp();
											break;
											
										case 2:
											cout<<"\n__________________________________________________\n";
											A1.Employeedisplay();
											A1.EmpRem();
								cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
											// E1.salesdisp();
											break;
										case 3:
											cout<<"\n__________________________________________________\n";
											A1.EmpAdd();
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
											// E1.salesdisp();
											break;
										case 4:
											emp=1;
											break;
										default:
											cout<<"\n\nInvalid Input! Please Enter a number between 1 and 4\n\n";
											cin.clear();
											cin.ignore(100, '\n');
									}
								} while (x==0); 
								break;
								
								case 3:
									do
									{
									
									x=0;
									cout<<"\n\t1. See All Users Credentials"<<endl;
									cout<<"\n\t2. Change Users Credentials"<<endl;
									cout<<"\n\t3. Remove Credentials"<<endl;
									cout<<"\n\t4. Add New Credentials"<<endl;
									cout<<"\n\t5. Go back"<<endl;
									cout<<"\n\n Select Any Option (1-5) : ";
									cin>>c4;
									
									switch (c4)
									{
										case 1:
											A1.Userdisp();
									cout<<"\033[34;40;1m\n\n--------------------------------------------------------------------------\n\n\033[0m";
											break;
											
										case 2:
											A1.Userdisp();
									cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
											A1.Userchange();
											break;
											
										case 3:
											A1.Userdisp();
								cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
											A1.Userrem();
											cout<<"\n-------------------------------------------------------------\n";
											break;
										case 4:
											A1.Useradd();
											break;
											
										case 5:
											
											x=1;
											break;
										default:
											cout<<"\033[91;40;1m\n\tInvalid Input! Enter Between (1-5).\033[0m"<<endl;
											cin.clear();
											cin.ignore(100, '\n');
											
						
											
									}
									
									}while(x==0);
									break;
								case 4:
									x3=1;
									break;
							}
						}while (x3==0);
						break;
						
						case 3:			//For notif
							
							do
							{
							
							x=0;
							cout<<"\n\t1. View Notifications"<<endl;
							cout<<"\n\t2. Add a Notifcation"<<endl;
							cout<<"\n\t3. Delete a Notifcation"<<endl;
							cout<<"\n\t4. Go Back"<<endl;
							cout<<"\n\n Select Any Option (1-4) : ";
							cin>>c4;
							
							switch(c4)
							{		
								case 1:
									A1.Notifdisp();
									cout<<"\033[34;40;1m\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 2:
									cout<<"\033[34;40;1m\n-------------------------------------------------------\n\n\033[0m";
									A1.Notifadd();
									break;
								case 3:
									A1.Notifdisp();
									cout<<"\033[34;40;1m\n-------------------------------------------------------\n\n\033[0m";
									A1.Notifrem();
									break;
								case 4:
									x=1;
									break;
								default:
									cout<<"\033[91;40;1m\n\tInvalid Input! Enter Between (1-4).\033[0m"<<endl;
									cin.clear();
									cin.ignore(100, '\n');
							
							}
							
							}while(x==0);
							break;
						case 4:			//For schedule orders
							A1.Schmanage();
							break;
						case 5:			//For complaints
							do
							{
							
							x=0;
							cout<<"\n\t1. View Complaints"<<endl;
							cout<<"\n\t2. Respond to a complaint"<<endl;
							cout<<"\n\t3. Go Back"<<endl;
							cout<<"\n\n Select Any Option (1-3) : ";
							cin>>c4;
							
							switch(c4)
							{		
								case 1:
									A1.Compdisp();
									cout<<"\033[34;40;1m\n-------------------------------------------------------\n\n\033[0m";
									break;
								case 2:
									A1.Compdisp();
									cout<<"\033[34;40;1m\n-------------------------------------------------------\n\n\033[0m";
									A1.Compread();
									break;
								case 3:
									x=1;
									break;
								default:
									cout<<"\033[91;40;1m\n\tInvalid Input! Enter Between (1-3).\033[0m"<<endl;
									cin.clear();
									cin.ignore(100, '\n');
							
							}
							
							}while(x==0);
							break;
						case 6:			//Statistics
						cout<<"\033[34;40;1m\n\n\n---------------------------------------------------------------------\n\n\n\033[0m";
							A1.stats();
							cout<<"\033[34;40;1m\n\n\n---------------------------------------------------------------------\n\n\033[0m";
							break;
						case 7:			//logout
							main=1;
							break;
						default:
							cout<<"\033[91;40;1m\n\tInvalid Input! Enter Between (1-8).\033[0m"<<endl;
							cin.clear();
							cin.ignore(100, '\n');
							break;
				}
				
				} while (main==0);		
				
			}
			else
			{
				cout<<"\033[91;40;1m\n\tWrong Admin ID or Password! Please Try Again.\033[0m"<<endl;
				a++;
			}
			if (a>5)		//This will break loop if more than 5 wrong attempts
			{
				cout<<"\033[91;40;1m\n\tToo many wrong attempts! Please try again later.\033[0m"<<endl;
				break;
			}
			
			}while(x==0);		//loop will continue until correct id and password is entered
			
			break;	
			
		case 2:			//for employee login
		
		x=0;
		int p;
		bool y;
		
		cin.ignore();
		do
		{
		
		y = E1.login(p);		//returns 1 if login successfull
		
		if (y==1)
		{
		
			do
			{
			
			cout<<"\n\n\t1. See Items in Stock"<<endl;
			cout<<"\n\t2. Search Items"<<endl;
			cout<<"\n\t3. Take Order"<<endl;
			cout<<"\n\t4. Manage Online/Scheduled Order"<<endl;
			cout<<"\n\t5. Sort Items"<<endl;
			cout<<"\n\t6. Logout"<<endl;
			E1.notify();
			cout<<"\n\n Select Any Option (1-6) : ";
			cin>>c1;
			
			switch(c1)
			{
				case 1:			//to see items
					cout<<endl<<endl;
					P[2]->stockdisp();
					cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
					break;
					
				case 2:			//search items
					cout<<endl<<endl;
					P[2]->stocksearch();
					cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
					break;
					
				case 3:			//take order
					item_sold=0;
					E1.stockdisp();
					cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
					item_sold= E1.order();
					cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
					E1.Updsales(p, item_sold);
					break;
					
				case 4:			//see online orders
					E1.schmanage();
					break;
				case 5:
					P[2]->sortstock();
					cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
					break;
				case 6:
					x=1;
					break;
					
				default:
					cout<<"\033[91;40;1m\n\n Invalid Input! Please enter between (1 - 6). \n\n\033[0m"<<endl;
					cin.clear();
					cin.ignore(100, '\n');
					break;
			
			}
			
			}while(x==0);
			
		}
		else
			cout<<"\033[91;40;1m\n\tWrong ID or Password! Please enter again!\n\033[0m"<<endl;
			
		}while(y==0);
			
			
			break;
			
			
		case 3:			//for student login
			x=0;
			p=0;
			y=0;
			
			cin.ignore();
			do
			{
			
			y = P[3]->login();			//returns 1 if login successfull
			
			if(y==1)
			{
			
				do
				{
				
				cout<<"\n\n\t1. See Menu"<<endl;
				cout<<"\n\t2. Search Items"<<endl;
				cout<<"\n\t3. Schedule an Order"<<endl;
				cout<<"\n\t4. Submit complaint"<<endl;
				cout<<"\n\t5. Sort items in menu"<<endl;
				cout<<"\n\t6. Logout"<<endl;
				U1.notify();
				cout<<"\n\n Select Any Option (1-6) : ";
				cin>>c1;
				
				switch(c1)
				{
					case 1:
						P[3]->stockdisp();
						cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
						break;
					
					case 2:
						P[3]->stocksearch();
						cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
						break;
					case 3:
						U1.stockdisp();
						cout<<"\033[34;40;1m\n\n-------------------------------------------------------\n\n\033[0m";
						U1.schedule();
						break;
					case 4:
					U1.Compadd();
						break;
					case 5:
						P[3]->sortstock();
						break;
					case 6:
						x=1;
						break;
					default:
						cout<<"\033[91;40;1m\n\n Invalid Input! Please enter between (1 - 6). \n\n\033[0m"<<endl;
						cin.clear();
						cin.ignore(100, '\n');
						break;
						
				
				
				}
				
				}while(x==0);
			
			}
			else
				cout<<"\033[91;40;1m\n\tWrong ID or Password! Please enter again!\n\033[0m"<<endl;
			
			}while(x==0);
			break;
		case 4:			//for exit program
			logout=1;
			break;
		default:
			cout<<"\033[91;40;1m\n\tInvalid Input! Please Enter between (1-4)\n\033[0m"<<endl;
			cin.clear();
			cin.ignore(100, '\n');
			break;
	}
	
	}while(logout==0);

} 
