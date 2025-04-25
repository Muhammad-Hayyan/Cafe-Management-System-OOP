/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
#include<iostream>
using namespace std;

Employee::Employee()
{

}
Employee::Employee(string n, int i, string p)                   //constructor
		{
			name = n; 
			ID = i;
			password  = p;
		}
void Employee::getData ()
		{
			cout<<"\nEnter name of employee : ";
			cin>>name;
			cout<<"\nEnter ID of employee : ";
			cin>>ID;
			cout<<"\nEnter Password : ";
			cin>>password;
		}
void Employee::showData() const
		{
			cout<<"\nName Of Employee : "<<name;
			cout<<"\nID : "<<ID;
		}
void Employee::init()			//This is function for initially storing all employees
{
	
	ofstream fout;
	fout.open("empcred.dat" , ios::out | ios::binary);

	for(int i=0; i<5; i++)				//storing five employees
	{
		cout<<"\nName : ";
		cin>>name;
		cout<<"\nId :";
		cin>>ID;
		cout<<"\nPassword : ";
		cin>>password;

	
		 // Write the strings along with their lengths to the file
    int nlen = strlen(name.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
    fout.write(name.c_str(), nlen);						//storing string

    fout.write(reinterpret_cast<char*>(&ID) , sizeof(ID));

    int plen = strlen(password.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&plen) , sizeof(plen));			//storing size
    fout.write(password.c_str(), plen); 				//storing string


	}

	fout.close();

}
void Employee::temp()
{
	cout<<"\nInside temp emp";
	ifstream fin;
	fin.open("empcred.dat" , ios::binary | ios::in);
	fin.seekg(0, ios::beg);
	while(fin.read(reinterpret_cast<char*>(&name) , sizeof(name)) && fin.read(reinterpret_cast<char*>(&ID) , sizeof(ID)) && fin.read(reinterpret_cast<char*>(&password) , sizeof(password)) )
	{
		
			cout<<"- - - - - - - - - - - - - - - \n";
		cout<<"UserName : "<<name<<endl;
		cout<<"User ID : "<<ID<<endl;
		cout<<"Password: "<<password<<endl;
		cout<<"- - - - - - - - - - - - - - - \n";
		cout<<"\n__________________________________________________\n\n";
		
	}
	fin.close();
}
void Employee::disp()                       //to display employees
{
	
	ifstream fin;
	fin.open("empcred.dat" , ios::in | ios::binary);            //opening file
	if (!fin.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
	fin.seekg(0);					//starts with the beginning of file

	//Now we will read first the size, then make a temp array to read string then delete that array
	 while (!fin.eof()) 
    {
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));         //first reading size
        if (fin.eof()) // Break loop if end of file
            break;

        // Allocate memory for name and read from file
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);
        name = nameBuffer;
        delete[] nameBuffer;

        fin.read(reinterpret_cast<char*>(&ID) , sizeof(ID));

        int plen;
        fin.read(reinterpret_cast<char*>(&plen), sizeof(plen));         //reading size of password

        // Allocate memory for password and read from file
        char* passwordBuffer = new char[plen];
        fin.read(passwordBuffer, plen);
        password = passwordBuffer;
        delete[] passwordBuffer;

        cout << "- - - - - - - - - - - - - - - \n";
        cout << "UserName : " << name << endl;
        cout << "User ID : " << ID << endl;
        cout << "Password: " << password << endl;
        cout << "- - - - - - - - - - - - - - - \n";
        cout << "\n__________________________________________________\n\n";
    }
	fin.close();
	

}
void Employee::rem() {
	int empID;
	cout<<"\nEnter ID of employee to remove : ";        //taking id of employee to remove
	cin>>empID;

    ifstream fin("empcred.dat", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary); // Temporary file to write updated data
    
    if (!fin.is_open()) {
        cout << "Error: Unable to open file for reading." << endl;
        return;
    }
    
    bool found = false;                     //flag to check if employee exists
    while (!fin.eof()) 
    {
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));                 //reading size
        if (fin.eof()) // Break loop if end of file
            break;
        
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);                     //reading name
        string name = nameBuffer;
        delete[] nameBuffer;
        
        int ID;
        fin.read(reinterpret_cast<char*>(&ID), sizeof(ID));             //reading id
        
        int plen;
        fin.read(reinterpret_cast<char*>(&plen), sizeof(plen));             //reading size of password
        
        char* passwordBuffer = new char[plen];
        fin.read(passwordBuffer, plen);                     //reading password
        string password = passwordBuffer;
        delete[] passwordBuffer;
        
        if (ID == empID)                            //when id is found, we dont write data
        {
            found = true;
            cout<<"\033[92;40;1m\n\n\t Employee with ID "<<empID<<" has been removed. \n\033[0m"<<endl;


            //Now updating empsales file
            ifstream fin1;
            ofstream fout1;
            fout1.open("temp2.dat" , ios::out | ios::binary);               //temp file to store new data 
            fin1.open("empsales.dat" , ios::in | ios::binary);
            fin1.seekg(0);					//starts with the beginning of file
            int s, ID1;
            //Now we will read first the size, then make a temp array to read string then delete that array
            while (!fin1.eof()) 
            {
                fin1.read(reinterpret_cast<char*>(&ID1) , sizeof(ID1));
                if (fin1.eof()) // Break loop if end of file
                    break;
                fin1.read(reinterpret_cast<char*>(&s), sizeof(s));

                if(ID1 == ID)                   //when id matches, dont write data
                {

                }
                else
                {
                    fout1.write(reinterpret_cast<char*>(&ID1), sizeof(ID1));
                    fout1.write(reinterpret_cast<char*>(&s), sizeof(s));
                }
            }
            fout1.close();
            fin1.close();

            // Remove the original file
            remove("empsales.dat");
            // Rename the temporary file to the original file name
            rename("temp2.dat", "empsales.dat");
        } 
        else                        //when id is not same, then write data
        {
            // Write data of employees with IDs other than empID to the temporary file
            fout.write(reinterpret_cast<char*>(&nlen), sizeof(nlen));
            fout.write(name.c_str(), nlen);
            fout.write(reinterpret_cast<char*>(&ID), sizeof(ID));
            fout.write(reinterpret_cast<char*>(&plen), sizeof(plen));
            fout.write(password.c_str(), plen);
        }
    }
    
    fin.close();
    fout.close();
    
    // Remove the original file
    remove("empcred.dat");
    // Rename the temporary file to the original file name
    rename("temp.dat", "empcred.dat");
    
    if (!found)
        cout << "Employee with ID " << empID << " not found." << endl;
}
void Employee::add() {
    ofstream fout("empcred.dat", ios::out | ios::binary | ios::app); // Open file in append mode
    
    if (!fout.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
    
    string name, password;
    int ID;
    
    //taking inputs name, id and password
    cin.ignore();
    cout << "\nEnter employee name: ";
    getline(cin, name);
    cout << "Enter employee ID: ";
    cin >> ID;
    cout << "Enter employee password: ";
    cin >> password;
    
   	 // Write the strings along with their lengths to the file
    int nlen = strlen(name.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
    fout.write(name.c_str(), nlen);						//storing string

    fout.write(reinterpret_cast<char*>(&ID) , sizeof(ID));

    int plen = strlen(password.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&plen) , sizeof(plen));			//storing size
    fout.write(password.c_str(), plen); 				//storing string
    
    fout.close();
    
    cout<<"\033[92;40;1m\n\n\t Employee Added Successfully. \n\033[0m"<<endl;

    //updating empsales
    int s=0;
    fout.open("empsales.dat" ,  ios::out | ios::binary | ios::app);
    fout.write(reinterpret_cast<char*>(&ID), sizeof(ID));
    fout.write(reinterpret_cast<char*>(&s), sizeof(s));
    fout.close();

}

bool Employee::login(int& p)
{
    bool x=0;
    int tempid;
    string tempps;

    //taking input id and password
    cout << "\033[93;40;1m\n\n\tEnter your ID: \033[0m";
    cin>>tempid;
    cout << "\033[93;40;1m\n\n\tEnter your Password: \033[0m";
    cin>>tempps;

    ifstream fin;
	fin.open("empcred.dat" , ios::in | ios::binary);
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

        if(ID == tempid && password == tempps)              //when id and password matches, login
        {
            cout << "\033[94;40;1m\n\n________________________________________________________________________________\n\n\n\n\033[0m";
				cout << "\033[94;107;1m\t Logged in as  [ "<<name<<"  ]  \t\033[0m"<<endl<<endl<<endl;
            x=1;
            p = ID;                             //saves id of employee logged in
            return x;
        }
    }

    fin.close();

    return x;
}
void Employee::change()
{
    int empID,ID1;
    string password1;

	cout<<"\nEnter ID of employee you want to change credentials of : ";
	cin>>empID;

    //taking inputs new id and password
    cout << "Enter new ID: ";
    cin >> ID1;
    cout << "Enter new password: ";
    cin >> password1;

    ifstream fin("empcred.dat", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary); // Temporary file to write updated data
    
    if (!fin.is_open()) {
        cout << "Error: Unable to open file for reading." << endl;
        return;
    }
    
    bool found = false;
    while (!fin.eof()) {
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
        if (fin.eof()) // Break loop if end of file
            break;
        
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);
        string name = nameBuffer;
        delete[] nameBuffer;
        
        int ID;
        fin.read(reinterpret_cast<char*>(&ID), sizeof(ID));
        
        int plen;
        fin.read(reinterpret_cast<char*>(&plen), sizeof(plen));
        
        char* passwordBuffer = new char[plen];
        fin.read(passwordBuffer, plen);
        string password = passwordBuffer;
        delete[] passwordBuffer;
        
        if (ID == empID)                    //when id matches, write updated data
        {
            found = true;

            plen = strlen(password1.c_str()) + 1; // Include null terminator
            fout.write(reinterpret_cast<char*>(&nlen), sizeof(nlen));
            fout.write(name.c_str(), nlen);
            fout.write(reinterpret_cast<char*>(&ID1), sizeof(ID1));
            fout.write(reinterpret_cast<char*>(&plen), sizeof(plen));
            fout.write(password1.c_str(), plen);

            cout<<"\033[92;40;1m\n\n\t "<<name<<" credentials changed successfully ! \n\033[0m"<<endl;


            //Now updating empsales file
            ifstream fin1;
            ofstream fout1;
            fout1.open("temp2.dat" , ios::out | ios::binary);
            fin1.open("empsales.dat" , ios::in | ios::binary);
            fin1.seekg(0);					//starts with the beginning of file
            int s, ID2;
            //Now we will read first the size, then make a temp array to read string then delete that array
            while (!fin1.eof()) 
            {
                fin1.read(reinterpret_cast<char*>(&ID2) , sizeof(ID2));
                if (fin1.eof()) // Break loop if end of file
                    break;
                fin1.read(reinterpret_cast<char*>(&s), sizeof(s));

                if(ID2 == ID)
                {
                    fout1.write(reinterpret_cast<char*>(&ID1), sizeof(ID1));
                    fout1.write(reinterpret_cast<char*>(&s), sizeof(s));
                }
                else
                {
                    fout1.write(reinterpret_cast<char*>(&ID2), sizeof(ID2));
                    fout1.write(reinterpret_cast<char*>(&s), sizeof(s));
                }
            }
            fout1.close();
            fin1.close();

            // Remove the original file
            remove("empsales.dat");
            // Rename the temporary file to the original file name
            rename("temp2.dat", "empsales.dat");

        } 
        else                        //when id does not match, write old data
        {
            // Write data of employees with IDs other than empID to the temporary file
            fout.write(reinterpret_cast<char*>(&nlen), sizeof(nlen));
            fout.write(name.c_str(), nlen);
            fout.write(reinterpret_cast<char*>(&ID), sizeof(ID));
            fout.write(reinterpret_cast<char*>(&plen), sizeof(plen));
            fout.write(password.c_str(), plen);
        }
    }
    
    fin.close();
    fout.close();
    
    // Remove the original file
    remove("empcred.dat");
    // Rename the temporary file to the original file name
    rename("temp.dat", "empcred.dat");
    
    if (!found)
        cout<<"\033[91;40;1m\n\n\t Employee with ID " << empID << " not found. \n\033[0m"<<endl;

}

//through aggregation
void Employee::stockdisp()
{
    S.disp();
}
void Employee::stocksearch()
{
    S.search();
}
void Employee::sortstock()
{
    S.sort();
}

int Employee::order()
{
    string item;
    int ID, price, amount;
    //first checking how much items is in file to make dynamic arrays 

    ifstream fin;
	fin.open("stock.dat" , ios::in | ios::binary);
	fin.seekg(0);					//starts with the beginning of file
    int count=0;                        //to count lines

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

        count++;                    //checking how many items in stock
        
    }
	fin.close();

    //dynamically allocating memories

    string *item1 = new string[count];
    int *ID1 = new int[count];
    int *price1 = new int[count];
    int *amount1 = new int[count];

    fin.open("stock.dat" , ios::in | ios::binary);
	fin.seekg(0);					//starts with the beginning of file

	int i=0;

    while (!fin.eof()) 
    {
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
        if (fin.eof()) // Break loop if end of file
            break;

        // Allocate memory for name and read from file
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);
        item1[i] = nameBuffer;
        delete[] nameBuffer;

        //reading items in arrays

        fin.read(reinterpret_cast<char*>(&ID1[i]) , sizeof(ID1[i]));
        fin.read(reinterpret_cast<char*>(&price1[i]) , sizeof(price1[i]));
        fin.read(reinterpret_cast<char*>(&amount1[i]) , sizeof(amount1[i]));

        i++; 
        
    }
    fin.close();


    bool x=0, y=0, z=0, m=0, r=0, n=0;
    int index,choice, total_price=0, total_items=0, rid, ramount, t_it=0;
    string s_item;

    ofstream fout;
    ofstream fout1, fout2;
    ifstream fin1, fin2;
	fout.open("receipt.dat", ios :: out | ios::binary);		//now writing in receipt txt for receipt

    do
    {
    
    do
	{
        x=0;
        cout<<"\n\nEnter the ID of item ordered : ";
        cin>>ID;
        
        for (int k=0; k<count; k++)
        {
            if(ID == ID1[k])		//This condition checks if entered ID item exists or not, if not then it asks to enter again
            {
                x=1;
                break;
            }
            
        }
        if (x==0)
            cout<<"\033[91;40;1m\n\n No items found with this ID. Please enter again. \n\n\033[0m"<<endl;
	
	}while(x==0);			//Loop continues until correct ID is found


    do
	{
        z=0, y=0, m=0;
        
        do                          //to check if qty<1
        {
            r=0;
            cout<<"\n\nEnter quantity of item : ";
            cin>>amount;
            if(amount<1)
            {
                cout<<"\033[91;40;1m\n\n Please Enter quantity greater than 1 \n\n\033[0m"<<endl;
            }
            else
                r=1;
        }while(r==0);			//loop continues until quantity is >1
        
        for (int k=0; k<count; k++)
        {
            if(ID == ID1[k])			//Finding ordered item in stock txt
            {
                if(amount <= amount1[k])	//condition checks if ordered quantity is avalable or not
                {
                    y=1;
                    index = k;
                    break;
                }
            }
        }
        
        if(y==0)			//If quantity is not available
        {
            cout<<"\033[91;40;1m\n\n Sorry! That much quantity is not available. \n\n\033[0m"<<endl;
            do
            {
                cout<<"\n\n\t1. Enter quantity again"<<endl;
                cout<<"\n\t2. Exit Order"<<endl;
                cout<<"\n\n Select any option (1-2) : ";
                cin>>choice;
                
                switch (choice)
                {
                    case 1:
                        m=1;
                        break;
                    case 2:				//setting flags to 1 if exit order
                        m=1;
                        z=1;
                        n=1;
                        break;
                    default:
                        cout<<"\033[91;40;1m\n\n Invalid Input! Please enter between (1-2).\n\n\033[0m"<<endl;
                }
                
            }while(m==0);		//loop continues until valid input
        }
        else
            break;
            
	}while(z==0);				//Main do while loop continues until exit program or if qty is available


    if(y==1)                        //if item and qty available
    {
        cout<<"\n\n-------------------------------------------------------------------------------------------";

        fout.write(reinterpret_cast<char*>(&ID1[index]) , sizeof(ID1[index]));
        fout.write(reinterpret_cast<char*>(&amount) , sizeof(amount));


        for (int k=0; k<count; k++)
		{
			if(ID == ID1[k])			//this counts total price and items ordered
			{
				total_price += (price1[k]*amount);
				total_items += amount;
				break;
			}
		
		}


        do
		{
            m=0, n=0;
            cout<<"\033[93;40;1m\n\n\t1. Confirm and generate receipt \n\033[0m";
            cout<<"\033[93;40;1m\n\n\t2. Order more items\n\033[0m";
            cout<<"\033[91;40;1m\n\n\t3. Dismiss Order\n\033[0m";
            cout<<"\n\n Select any option (1-3) : ";
            cin>>choice;
            
            switch(choice)
            {
                case 1:			//generates receipt 
                    cout<<"\n\n-------------------------------------------------------------------------------------------";
                    m=1, n=1;
                    t_it = total_items;
                    cout<<"\033[34;40;1m\n\n\t Order Confirmed!! \n\033[0m";
                    fout.close();
                    cout<<"\n\n Receipt : \n\n\n";
                    fin.open("receipt.dat", ios :: in | ios::binary);			//Reading from receipt txt 
                   
                    cout<<"\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
                    cout<<"\t\t\tItems\t\tPrice\t\tAmount"<<endl;
                    cout<<"\n\n\t\t\t- - - - - - - - - - - - - - - - - - - - \n";

                    while (!fin.eof())                      //this loop reads every item in receipt txt
                    {

                        fin.read(reinterpret_cast<char*>(&rid) , sizeof(rid));
                        fin.read(reinterpret_cast<char*>(&ramount) , sizeof(ramount));

                        if (fin.eof()) // Break loop if end of file
                            break;
                        else
                        {
                            for(int k=0; k<count ; k++)
                            {
                                if(ID1[k] == rid)               //when receipt item id and stock item id matches
                                {
                                    //displaying receipt
                                    cout<<"\t\t\t"<<item1[k]<<"\t\t"<<price1[k]<<"\t\t  "<<ramount<<endl;
                                    cout<<"\t\t\t- - - - - - - - - - - - - - - - - - - - \n";


                                    //Now updating sales file
                                    fout1.open("temp2.dat" , ios::out | ios::binary);
                                    fin1.open("sales.dat" , ios::in | ios::binary);
                                    fin1.seekg(0);					//starts with the beginning of file
                                    int s;
                                    //Now we will read first the size, then make a temp array to read string then delete that array
                                    while (!fin1.eof()) 
                                    {
                                        int nlen2;
                                        fin1.read(reinterpret_cast<char*>(&nlen2), sizeof(nlen2));
                                        if (fin1.eof()) // Break loop if end of file
                                            break;

                                        // Allocate memory for name and read from file
                                        char* nameBuffer = new char[nlen2];
                                        fin1.read(nameBuffer, nlen2);
                                        s_item = nameBuffer;
                                        delete[] nameBuffer;

                                        fin1.read(reinterpret_cast<char*>(&s) , sizeof(s));

                                        if(s_item == item1[k])
                                        {
                                                s += ramount;
                                                //writing in sales file
                                                nlen2 = strlen(s_item.c_str()) + 1; // Include null terminator
                                                fout1.write(reinterpret_cast<char*>(&nlen2) , sizeof(nlen2));				//storing size
                                                fout1.write(s_item.c_str(), nlen2);						//storing string
                                                fout1.write(reinterpret_cast<char*>(&s) , sizeof(s));
                                        }
                                        else
                                        {
                                                //writing in sales file
                                                nlen2 = strlen(s_item.c_str()) + 1; // Include null terminator
                                                fout1.write(reinterpret_cast<char*>(&nlen2) , sizeof(nlen2));				//storing size
                                                fout1.write(s_item.c_str(), nlen2);						//storing string
                                                fout1.write(reinterpret_cast<char*>(&s) , sizeof(s));
                                        }
                                    }
                                    fout1.close();
                                    fin1.close();

                                    // Remove the original file
                                    remove("sales.dat");
                                    // Rename the temporary file to the original file name
                                    rename("temp2.dat", "sales.dat");



                                    //now updating stocks
                                    ifstream fin2("stock.dat" , ios::in | ios::binary);
                                    ofstream fout2("temp3.dat", ios::out | ios::binary); // Temporary file to write updated data
                                
                                    //Now we will read first the size, then make a temp array to read string then delete that array
                                    while (!fin2.eof()) 
                                    {
                                        int nlen;
                                        fin2.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
                                        if (fin2.eof()) // Break loop if end of file
                                            break;

                                        // Allocate memory for name and read from file
                                        char* nameBuffer = new char[nlen];
                                        fin2.read(nameBuffer, nlen);
                                        item = nameBuffer;
                                        delete[] nameBuffer;

                                        fin2.read(reinterpret_cast<char*>(&ID) , sizeof(ID));
                                        fin2.read(reinterpret_cast<char*>(&price) , sizeof(price));
                                        fin2.read(reinterpret_cast<char*>(&amount) , sizeof(amount));

                                        if (ID == ID1[k])       //when id matches, write updates quantity
                                        {
                                            amount = amount - ramount;
                                            // Write the strings along with their lengths to the file
                                            int nlen = strlen(item.c_str()) + 1; // Include null terminator
                                            fout2.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
                                            fout2.write(item.c_str(), nlen);						//storing string

                                            fout2.write(reinterpret_cast<char*>(&ID) , sizeof(ID));
                                            fout2.write(reinterpret_cast<char*>(&price) , sizeof(price));
                                            fout2.write(reinterpret_cast<char*>(&amount) , sizeof(amount));
                                        } 
                                        else 
                                        {
                                            // Write the strings along with their lengths to the file
                                            int nlen = strlen(item.c_str()) + 1; // Include null terminator
                                            fout2.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
                                            fout2.write(item.c_str(), nlen);						//storing string

                                            fout2.write(reinterpret_cast<char*>(&ID) , sizeof(ID));
                                            fout2.write(reinterpret_cast<char*>(&price) , sizeof(price));
                                            fout2.write(reinterpret_cast<char*>(&amount) , sizeof(amount));
                                        }

                                    }


                                    fin2.close();
                                    fout2.close();
                                    
                                    // Remove the original file
                                    remove("stock.dat");
                                    // Rename the temporary file to the original file name
                                    rename("temp3.dat", "stock.dat");
                                }
                            }
                        }
                    }
                    fin.close();

                    //displaying total amount
                    cout<<"\n\t\t\t------------------------------------------\n";
                    cout<<"\t\t\t\tTotal Amount :  Rs."<<total_price<<endl;
                    cout<<"\t\t\t------------------------------------------\n";
                    cout<<"\n\n\t\t- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
                    
                    break;
                case 2:				//if order more items, it will go back to loop
                    m=1;
                    break;
                case 3:
                    fout.close();
                    m=1, n=1;
                    break;
                    
                default:
                    cout<<"\033[91;40;1m\n\n Invalid Input! Please enter between (1-2).\n\n\033[0m"<<endl;
            }
		
		}while(m==0);


    }

    }while(n==0);

    

    //deallocating arrays
    delete [] item1;
    item1 = NULL;
    delete [] ID1;
    ID1 = NULL;
    delete [] price1;
    price1 = NULL;
    delete [] amount1;
    amount1 = NULL;

    return t_it;

}

void Employee::salesinit()
{
    int s=0;
    ifstream fin;
    ofstream fout;
	fin.open("empcred.dat" , ios::in | ios::binary);
    fout.open("empsales.dat" , ios::out | ios::binary);
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



        fout.write(reinterpret_cast<char*>(&ID), sizeof(ID));
        fout.write(reinterpret_cast<char*>(&s), sizeof(s));

    }
	fin.close();
    fout.close();
}
void Employee::salesdisp()              //for displaying employees sales
{
    int s;
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


        cout<<"\t\t"<<ID<<"\t\t"<<s<<endl<<endl;
    }
	fin.close();
}
void Employee::Updsales(int p, int sales)               //updates employees sales
{
    ifstream fin;
    ofstream fout;
    fin.open("empsales.dat" , ios::in | ios::binary);
    fout.open("temp.dat" , ios::out | ios::binary);

    int s;
    while (!fin.eof()) 
    {
        fin.read(reinterpret_cast<char*>(&ID) , sizeof(ID));
        if (fin.eof()) // Break loop if end of file
            break;
        fin.read(reinterpret_cast<char*>(&s), sizeof(s));

        if(p == ID)                 //updates sales
        {
            sales = sales+s;
            fout.write(reinterpret_cast<char*>(&ID), sizeof(ID));
            fout.write(reinterpret_cast<char*>(&sales), sizeof(sales));
        }
        else
        {
            fout.write(reinterpret_cast<char*>(&ID), sizeof(ID));
            fout.write(reinterpret_cast<char*>(&s), sizeof(s));
        }

    }
	fin.close();
    fout.close();

    // Remove the original file
    remove("empsales.dat");
     // Rename the temporary file to the original file name
     rename("temp.dat", "empsales.dat");
}

//Through aggregation
void Employee::notify()
{
    N.notify();
}
void Employee::schmanage()
{
    O.manage();
}