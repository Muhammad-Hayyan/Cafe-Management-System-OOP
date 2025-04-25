/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"

Notification::Notification()
{

}
Notification::Notification(string n)
{
    notif = n;
}
void Notification::init()
{
    ofstream fout;
	fout.open("notif.dat" , ios::binary);


    //cin.ignore();
    cout<<"\nNotification : ";
	getline(cin, notif);
		

	// Write the strings along with their lengths to the file
    int nlen = strlen(notif.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
    fout.write(notif.c_str(), nlen);						//storing string

	fout.close();
}
void Notification::disp()                   //for displaying notification
{
    ifstream fin;
	fin.open("notif.dat" , ios::in | ios::binary);
	if (!fin.is_open()) 
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
	fin.seekg(0);					//starts with the beginning of file
    
    int i=1;
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
        notif = nameBuffer;
        delete[] nameBuffer;

       cout<<"\n"<<i<<". "<<notif<<endl;                    //displaying notification along with serial number
       i++;
    }
	fin.close();
}
void Notification::add()
{
    ofstream fout;
	fout.open("notif.dat" , ios::out | ios::binary | ios::app);         //opening in append mode


    cin.ignore();
    cout<<"\nEnter the Notification : ";
	getline(cin, notif);
		
    //Writing new notification
	// Write the strings along with their lengths to the file
    int nlen = strlen(notif.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
    fout.write(notif.c_str(), nlen);						//storing string

	fout.close();
    cout << "\033[34;40;1m\n\n Notification Added successfully! \n\033[0m\n"<<endl;
}
void Notification::rem()
{
    int i=1,i2=1,n;
    bool x=0;

    ifstream fin;
	fin.open("notif.dat" , ios::in | ios::binary);
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
        notif = nameBuffer;
        delete[] nameBuffer;
 
       i++;
    }
	fin.close();

    do
    {
        cout<<"\nEnter the no. of notification you want to remove : ";
        cin>>n;

        if(n<=0 || n>=i)            //validating input
        {
            cout<<"\033[91;40;1m\n\nInvalid Input! Please enter a number within range \n\n\033[0m"<<endl;
            x=0;
        }
        else
            x=1;
    }while(x==0);

    fin.open("notif.dat" , ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary); // Temporary file to write updated data
    i=1;
    while (!fin.eof()) 
    {
       
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
        if (fin.eof()) // Break loop if end of file
            break;

        // Allocate memory for name and read from file
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);
        notif = nameBuffer;
        delete[] nameBuffer;

        if (n==i)                       //when no matches, dont write notification
        {
            cout<<"\033[92;40;1m\n\n\t Notification has been removed successfully \n\033[0m"<<endl;
        } 
        else 
        {
            fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
            fout.write(notif.c_str(), nlen);	
        }

        i++;
    }
    
    fin.close();
    fout.close();
    
    // Remove the original file
    remove("notif.dat");
    // Rename the temporary file to the original file name
    rename("temp.dat", "notif.dat");
    
}
void Notification::notify()                     //to display notifications to user and employee
{
    ifstream fin;
	fin.open("notif.dat" , ios::in | ios::binary);
	if (!fin.is_open()) 
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
	fin.seekg(0);					//starts with the beginning of file
    
    int i=1;
    cout<<"\033[93;40;1m\n\n - - - - - - - - - - - - - - - - - - - -\n\033[0m";
	cout<<"\033[92;40;1m\nNotifications : \n\n\033[0m";
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
        notif = nameBuffer;
        delete[] nameBuffer;

   
	cout << "\033[94;40;1;5m - "<<notif<<"\n\033[0m";
       i++;
    }
    cout<<"\033[93;40;1m\n - - - - - - - - - - - - - - - - - - - -\n\n\033[0m";
	fin.close();
}