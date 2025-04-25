/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"

Complaints::Complaints()
{

}
Complaints::Complaints(string c)
{
    comp = c;
}
void Complaints::init()
{
    ofstream fout;
	fout.open("comp.dat" , ios::binary);


    //cin.ignore();
    cout<<"\nComplaint : ";
	getline(cin, comp);
		

	// Write the strings along with their lengths to the file
    int nlen = strlen(comp.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
    fout.write(comp.c_str(), nlen);						//storing string

	fout.close();
}
void Complaints::disp()
{
    ifstream fin;
	fin.open("comp.dat" , ios::in | ios::binary);
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
        comp = nameBuffer;
        delete[] nameBuffer;

       cout<<"\n"<<i<<". "<<comp<<endl;                     //displaying notifications with sr number (i)
       i++;
    }
	fin.close();
}
void Complaints::add()
{
    ofstream fout;
	fout.open("comp.dat" , ios::out | ios::binary | ios::app);         //opening in append mode


    cin.ignore();
    cout<<"\nEnter the Complaint : ";
	getline(cin, comp);
		

	// Write the strings along with their lengths to the file
    int nlen = strlen(comp.c_str()) + 1; // Include null terminator
    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
    fout.write(comp.c_str(), nlen);						//storing string

	fout.close();                   //closing file
    cout << "\033[34;40;1m\n\n Complaint Added successfully and will be acknowledged soon ! \n\033[0m\n"<<endl;
}
void Complaints::read()
{
    int i=1,i2=1,n;
    bool x=0;

    ifstream fin;
	fin.open("comp.dat" , ios::in | ios::binary);
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
        comp = nameBuffer;
        delete[] nameBuffer;
 
       i++;
    }
	fin.close();

    do
    {
        cout<<"\nEnter the no. of complaint you want to mark as read : ";
        cin>>n;

        if(n<=0 || n>=i)                        //validating input
        {
            cout<<"\033[91;40;1m\n\nInvalid Input! Please enter a number within range \n\n\033[0m"<<endl;
            x=0;
        }
        else
            x=1;
    }while(x==0);

    fin.open("comp.dat" , ios::in | ios::binary);
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
        comp = nameBuffer;
        delete[] nameBuffer;

        if (n==i) 
        {
            cout<<"\033[92;40;1m\n\n\t Complaint marked as read successfully \n\033[0m"<<endl;
        } 
        else                    //writing in temp file
        {
            fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
            fout.write(comp.c_str(), nlen);	
        }

        i++;
    }
    
    fin.close();
    fout.close();
    
    // Removing the original file
    remove("comp.dat");
    // Renaming the temporary file to the original file name
    rename("temp.dat", "comp.dat");
    
}