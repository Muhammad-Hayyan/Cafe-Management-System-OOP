/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"

User::User(string n) 
{
    username = n;
}
User::User()
{

}
void User::init()
{
    ofstream fout;
	fout.open("usercred.dat" , ios::binary);

	for(int i=0; i<5; i++)
	{
		cout<<"\nName : ";
		cin>>username;
        cout<<"\nPassword : ";
        cin>>password;
		
        
			 // Write the strings along with their lengths to the file
    int nlen = strlen(username.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
    fout.write(username.c_str(), nlen);						//storing string

    int plen = strlen(password.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&plen) , sizeof(plen));			//storing size
    fout.write(password.c_str(), plen); 				//storing string
		
	}
	fout.close();
}
void User::temp()
{
    ifstream fin;
    fin.open("usercred.dat" , ios::binary);

     while (!fin.eof()) 
    {
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
        if (fin.eof()) // Break loop if end of file
            break;

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

        cout<<"\033[34;40;1m\n\t---------------------------------------------------\n\033[0m";
		cout<<"\n\t\t\t User ID  : "<<username<<endl;
		cout<<"\t\t\t Password : "<<password<<endl;
    }
    cout<<"\033[34;40;1m\n\t---------------------------------------------------\n\033[0m";
    fin.close();
}
bool User::login()
{
    bool x=0;
    string tempid, temppass;
    


    cout << "\033[93;40;1m\n\n\tEnter your ID: \033[0m";
	cin>>tempid;
	cout << "\033[93;40;1m\n\n\tEnter your Password: \033[0m";
	cin>>temppass;

    

    ifstream fin;
	fin.open("usercred.dat" , ios::in | ios::binary);

    
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

        if(username == tempid && password == temppass)
        {
            cout << "\033[94;40;1m\n\n________________________________________________________________________________\n\n\n\n\033[0m";
				cout << "\033[94;107;1m\t Logged in as  [ "<<username<<"  ]  \t\033[0m"<<endl<<endl<<endl;
            x=1;
            return x;
        }
    

    fin.close();

    return x;
}
void User::disp()
{
    ifstream fin;
    fin.open("usercred.dat" , ios::binary);

     while (!fin.eof()) 
    {
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
        if (fin.eof()) // Break loop if end of file
            break;

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

        cout<<"\033[34;40;1m\n\t---------------------------------------------------\n\033[0m";
		cout<<"\n\t\t\t User ID  : "<<username<<endl;
		cout<<"\t\t\t Password : "<<password<<endl;
    }
    fin.close();
    cout<<"\033[34;40;1m\n\t---------------------------------------------------\n\033[0m";
}
void User::add()
{
    ofstream fout("usercred.dat", ios::out | ios::binary | ios::app); // Open file in append mode
    
    if (!fout.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
    
    string name, password;
    
    cout << "\nEnter User NU ID : ";
    cin>>username;
    cout << "Enter User password: ";
    cin >> password;
    
   	 // Write the strings along with their lengths to the file
    int nlen = strlen(username.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
    fout.write(username.c_str(), nlen);						//storing string

    int plen = strlen(password.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&plen) , sizeof(plen));			//storing size
    fout.write(password.c_str(), plen); 				//storing string
    
    fout.close();
    
    cout<<"\033[92;40;1m\n\n\t User Added Successfully. \n\033[0m"<<endl;
}
void User::rem()
{
    string userID;
	cout<<"\nEnter ID of user to remove : ";
	cin>>userID;
    ifstream fin("usercred.dat", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary); // Temporary file to write updated data
    
    if (!fin.is_open()) {
        cout << "Error: Unable to open file for reading." << endl;
        return;
    }
    
    bool found = false;
    while (!fin.eof()) 
    {
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
        if (fin.eof()) // Break loop if end of file
            break;
        
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);
        username = nameBuffer;
        delete[] nameBuffer;
        
        int plen;
        fin.read(reinterpret_cast<char*>(&plen), sizeof(plen));
        
        char* passwordBuffer = new char[plen];
        fin.read(passwordBuffer, plen);
        password = passwordBuffer;
        delete[] passwordBuffer;
        
        if (username == userID) 
        {
            found = true;
            cout<<"\033[92;40;1m\n\n\t User with ID "<<userID<<" has been removed. \n\033[0m"<<endl;
        } 
        else 
        {
            // Write data of employees with IDs other than empID to the temporary file
            fout.write(reinterpret_cast<char*>(&nlen), sizeof(nlen));
            fout.write(username.c_str(), nlen);
            fout.write(reinterpret_cast<char*>(&plen), sizeof(plen));
            fout.write(password.c_str(), plen);
        }
    }
    
    fin.close();
    fout.close();
    
    // Remove the original file
    remove("usercred.dat");
    // Rename the temporary file to the original file name
    rename("temp.dat", "usercred.dat");
    
    if (!found)
        cout<<"\033[91;40;1m\n\t User with ID " << userID << " not found.\033[0m"<<endl;
}
void User::change()
{
    string userID;
    string password1;

	cout<<"\nEnter ID of user you want to change credentials of : ";
	cin>>userID;

    cout << "Enter new password: ";
    cin >> password1;

    ifstream fin("usercred.dat", ios::in | ios::binary);
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
        username = nameBuffer;
        delete[] nameBuffer;
        
        int plen;
        fin.read(reinterpret_cast<char*>(&plen), sizeof(plen));
        
        char* passwordBuffer = new char[plen];
        fin.read(passwordBuffer, plen);
        password = passwordBuffer;
        delete[] passwordBuffer;
        
        if (username == userID) 
        {
            found = true;

            plen = strlen(password1.c_str()) + 1; // Include null terminator
            fout.write(reinterpret_cast<char*>(&nlen), sizeof(nlen));
            fout.write(username.c_str(), nlen);
            fout.write(reinterpret_cast<char*>(&plen), sizeof(plen));
            fout.write(password1.c_str(), plen);

            cout<<"\033[92;40;1m\n\n\t "<<userID<<" credentials changed successfully ! \n\033[0m"<<endl;
        } 
        else 
        {
            // Write data of employees with IDs other than empID to the temporary file
            fout.write(reinterpret_cast<char*>(&nlen), sizeof(nlen));
            fout.write(username.c_str(), nlen);
            fout.write(reinterpret_cast<char*>(&plen), sizeof(plen));
            fout.write(password.c_str(), plen);
        }
    }
    
    fin.close();
    fout.close();
    
    // Remove the original file
    remove("usercred.dat");
    // Rename the temporary file to the original file name
    rename("temp.dat", "usercred.dat");
    
    if (!found)
        cout<<"\033[91;40;1m\n\n\t User with ID " << userID << " not found. \n\033[0m"<<endl;

}

void User::Compadd()
{
    C.add();
}
void User::notify()
{
    N.notify();
}

void User::stockdisp()
{
    string item;
    int ID, price, amount;
    ifstream fin;
	fin.open("stock.dat" , ios::in | ios::binary);
	if (!fin.is_open()) 
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
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
        item = nameBuffer;
        delete[] nameBuffer;

        fin.read(reinterpret_cast<char*>(&ID) , sizeof(ID));
        fin.read(reinterpret_cast<char*>(&price) , sizeof(price));
        fin.read(reinterpret_cast<char*>(&amount) , sizeof(amount));

        
       
        cout<<"\t\tID\tITEM\tPRICE"<<endl;
        
            cout<<endl;
            cout<<"\t\t"<<ID<<"\t";
            cout<<item<<"\t";
            cout<<price<<"\n";
            cout<<"\t\t_____________________"<<endl;
        
    }
	fin.close();
}
void User::stocksearch()
{
    string item;
    int ID, price, amount;
    bool x=0;
    int Id_search = -1, choice;
    string name_s = "";

    //Asking admin to enter choice
	cout<<"\n\n1. Search Any Item with ID";
	cout<<"\n2. Search An Item with Name";
	cout<<"\n\n Select any Option: ";
	cin>>choice;
	
	switch(choice)
	{
	
	case 1:
			cout<<"\n\n Enter ID of item: ";
			cin>>Id_search;
	case 2:
            if(choice==2)					
            {
                cout<<"\n\n Enter Name of item (First letter capital): ";
                cin>>name_s;
            }
            ifstream fin;
            fin.open("stock.dat" , ios::in | ios::binary);
            //mene ID or name search dono k liye same mechanism banaya hai thats why i used if with switch and no breaks
            cout<<endl<<endl;

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

                if (item == name_s || ID == Id_search)		//check if item if found or not
			    {
                    cout<<"\t\tID\tITEM\tPRICE"<<endl;
                    cout<<"\t\t_____________________"<<endl;
                    cout<<"\t\t"<<ID<<"\t";
                    cout<<item<<"\t";
                    cout<<price<<"\n";
                    x=1;
                    break;
			    }
				
             }
             fin.close();
		
	}
		if (x==0)				//prints if no match found
                cout<<"\033[91;40;1m\n\n No Match Found! \n\n\033[0m"<<endl;
}
void User::sortstock()
{
    S.sort();
}
void User::schedule()
{
    O.add();
}