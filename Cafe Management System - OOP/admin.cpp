/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
#include "stock.h"
#include "order.h"


Admin::Admin()  : S(1, "Burger", 11, 11)    //also initializing stock composed
{
    

}
Admin::Admin(string n, string p)  : S(1, "Burger", 11, 11)
{
    username = n;
    password = p;
   
}
void Admin::init ()					//initializing admin credentials and storing them in file
{
    ofstream fout;
	fout.open("admincred.dat" , ios::binary);


		cout<<"\nName : ";
		cin>>username;
		cout<<"\nPassword : ";
		cin>>password;

        //Encrypting password 
        for(int i=0; i<password.size(); i++)
        {
            password[i] += 37;
        }

	// Write the strings along with their lengths to the file
    int nlen = strlen(username.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
    fout.write(username.c_str(), nlen);						//storing string

    int plen = strlen(password.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&plen) , sizeof(plen));			//storing size
    fout.write(password.c_str(), plen); 				//storing string

	
	fout.close();

}
void Admin::temp()				//for temporary reading credentials for checking
{
    ifstream fin;
	fin.open("admincred.dat" , ios::binary);

        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));

        // Allocate memory for name and read from file
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);
        username = nameBuffer;
        delete[] nameBuffer;

        int plen;
        fin.read(reinterpret_cast<char*>(&plen), sizeof(plen));

        // Allocate memory for password and read from file
        char* passwordBuffer = new char[plen];
        fin.read(passwordBuffer, plen);
        password = passwordBuffer;
        delete[] passwordBuffer;    

    fin.close();

    cout<<"\nName : "<<username<<endl;
	
	cout<<"\nPassword : "<<password<<endl;
}
bool Admin::login()
{
    bool x=0;
    string tempid;
    string tempps;

    //taking input from admin

    cout << "\033[93;40;1m\n\n\tEnter Admin ID: \033[0m";
    cin>>tempid;
    cout << "\033[93;40;1m\n\n\tEnter Admin Password: \033[0m";
    cin>>tempps;

    

    ifstream fin;                                       //opening file
	fin.open("admincred.dat" , ios::in | ios::binary);

    
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
        

        // Allocate memory for name and read from file
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);
        username = nameBuffer;
        delete[] nameBuffer;

        int plen;
        fin.read(reinterpret_cast<char*>(&plen), sizeof(plen));

        // Allocate memory for password and read from file
        char* passwordBuffer = new char[plen];
        fin.read(passwordBuffer, plen);
        password = passwordBuffer;
        delete[] passwordBuffer;

        //Decrypting password 
        for(int i=0; i<password.size(); i++)
        {
            password[i] -= 37;
        }

        if(username == tempid && password == tempps)
        {
            x=1;
            return x;
        }
    

    fin.close();

    return x;
}
void Admin::stockdisp()             //for displaying stock
{
    S.disp();
}
void Admin::stocksearch()           //for searching in stock
{
    S.search();
}
void Admin::stockadd()              //for adding another item in stock
{
    S.add();
}
void Admin::stockrem()              //removing an item from stock
{
    S.rem();
}
void Admin::stockorder()            //ordering more stock
{
    S.order();
}
void Admin::stockupdate()
{
    S.update();
}
void Admin::sortstock()
{
    S.sort();
}


void Admin::Employeedisplay()
{
    E.disp();
}
void Admin::EmpRem()
{
    E.rem();
}
void Admin::EmpAdd()
{
    E.add();
}
void Admin::EmpChange()
{
    E.change();
}

void Admin::Userdisp()
{
    U.disp();
}
void Admin::Useradd()
{
    U.add();
}
void Admin::Userrem()
{
    U.rem();
}
void Admin::Userchange()
{
    U.change();
}
void Admin::Notifdisp()
{
    N.disp();
}
void Admin::Notifrem()
{
    N.rem();
}
void Admin::Notifadd()
{
    N.add();
}

void Admin::Compdisp()
{
    C.disp();
}
void Admin::Compread()
{
    C.read();
}
void Admin::Warning()
{
    S.Warn();
}
void Admin::Schmanage()
{
    O.manage();
}

void Admin::stats()
{
    //calculating best employee

    int s, max_sale=0, ID;
    ifstream fin;
	fin.open("empsales.dat" , ios::in | ios::binary);
	fin.seekg(0);					//starts with the beginning of file

	//Now we will read first the size, then make a temp array to read string then delete that array
	 while (!fin.eof()) 
    {
        fin.read(reinterpret_cast<char*>(&ID) , sizeof(ID));
        if (fin.eof()) // Break loop if end of file
            break;
        fin.read(reinterpret_cast<char*>(&s), sizeof(s));


        if(s > max_sale)                    //checking if sale of this employee is greater
        {
            max_sale = ID;
        }
    }
	fin.close();

    //Now reading the best employee name from empcred file
    string name, password;
    fin.open("empcred.dat" , ios::in | ios::binary);
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
        name = nameBuffer;
        delete[] nameBuffer;

        fin.read(reinterpret_cast<char*>(&ID) , sizeof(ID));

        int plen;
        fin.read(reinterpret_cast<char*>(&plen), sizeof(plen));

        // Allocate memory for password and read from file
        char* passwordBuffer = new char[plen];
        fin.read(passwordBuffer, plen);
        password = passwordBuffer;
        delete[] passwordBuffer;

        if(ID == max_sale)
            break;
    }
	fin.close();
    
    //outputting best employee
    cout<<"\033[93;40;1m\n\n\t - Best Seller Of the Day is : \033[0m";
	cout<<"\033[92;40;1m"<<name<<"\n\n\033[0m"<<endl;


    string item;
    int price, amount, no_of_items=0, stockprice=0, avg=0;

    //now for stocks

    fin.open("stock.dat" , ios::in | ios::binary);
	
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
        item = nameBuffer;
        delete[] nameBuffer;

        fin.read(reinterpret_cast<char*>(&ID) , sizeof(ID));
        fin.read(reinterpret_cast<char*>(&price) , sizeof(price));
        fin.read(reinterpret_cast<char*>(&amount) , sizeof(amount));

        no_of_items = no_of_items + amount;				//this counts number of items in stock
		stockprice = stockprice + (amount*price); 		//this counts total price of stock
        
    }
	fin.close();

    avg = stockprice/no_of_items;                   //calculate average

    //displaying output

	cout<<"********************************************************************\n";
	cout<<"*							           *\n";
	cout<<"*		Total Items in stock : "<<no_of_items<<"	   		   *\n";
	cout<<"*					      			   *\n";
	cout<<"*		Total worth of stock : Rs. "<<stockprice<<"		   *\n";
	cout<<"*					      			   *\n";
	cout<<"*		Average Price per Item : Rs. "<<avg<<"		   *\n";
	cout<<"*							           *\n";
	cout<<"********************************************************************\n\n";

    string best, least;
    int b=0, l=0, tot=0;

    //Now calculating best least sold items

    fin.open("sales.dat" , ios::in | ios::binary);
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
        item = nameBuffer;
        delete[] nameBuffer;

        fin.read(reinterpret_cast<char*>(&s) , sizeof(s));

        if(s > b)                           //finding best sold
        {
            b = s;
            best = item;
        }
        
        if(s <= l)                          //finding least sold
        {
            least = item;
            l = s;
        }

        tot += s;
    }
	fin.close();

    //displaying output
    
    cout<<"\033[93;40;1m\n\t - Most sold item is : \033[0m";
	cout<<"\033[92;40;1m"<<best<<"\n\n\033[0m"<<endl;

    cout<<"\033[93;40;1m\n\t - Least sold item is : \033[0m";
	cout<<"\033[91;40;1m"<<least<<"\n\n\033[0m"<<endl;

    cout<<"\033[94;40;1m\n\t Total Items Sold : "<<tot<<" \033[0m";
}

