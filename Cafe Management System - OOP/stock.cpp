/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
Stock::Stock()
{

}
Stock::Stock(int i, string n, int p, int a)
{
    ID = i;
    item = n;
    price = p;
    amount = a;
}
void Stock::init()
{
    ofstream fout;
	fout.open("stock.dat" , ios::out | ios::binary);

	for(int i=0; i<10; i++)				//storing five employees
	{
		cout<<"\nItem : ";
		cin>>item;
		cout<<"\nId :";
		cin>>ID;
		cout<<"\nPrice : ";
		cin>>price;
        cout<<"\nAmount : ";
        cin>>amount;

	
		 // Write the strings along with their lengths to the file
        int nlen = strlen(item.c_str()) + 1; // Include null terminator
        fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
        fout.write(item.c_str(), nlen);						//storing string

        fout.write(reinterpret_cast<char*>(&ID) , sizeof(ID));
        fout.write(reinterpret_cast<char*>(&price) , sizeof(price));
        fout.write(reinterpret_cast<char*>(&amount) , sizeof(amount));

    }


	fout.close();
}
void Stock::disp()                  //to display stock
{
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

        
        //Now displaying stock

        cout<<"\t\tID\tITEM\tPRICE\tAMOUNT\tTOTAL_WORTH"<<endl;
        if(amount == 0)		//yellow color if item is zero
		{
			cout<<endl;
			cout<<"\033[93;40;1m\t\t"<<ID<<"\t"<<item<<"\t"<<price<<"\t"<<amount<<"\t"<<amount*price<<"\n\033[0m";
		}
        else if(amount < 10)		//red color if item is less than 10
		{
			cout<<endl;
            cout<<"\033[91;40;1m\t\t"<<ID<<"\t"<<item<<"\t"<<price<<"\t"<<amount<<"\t"<<amount*price<<"\n\033[0m";
        }
        
        else
        {
            cout<<endl;
            cout<<"\t\t"<<ID<<"\t";
            cout<<item<<"\t";
            cout<<price<<"\t";
            cout<<amount<<"\t";
            cout<<amount*price<<"\n";
        }
            cout<<"\t\t___________________________________________"<<endl;
        
    }
	fin.close();

   
}
void Stock::search()
{
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
                    cout<<"\t\tID\tITEM\tPRICE\tAMOUNT\tTOTAL_WORTH"<<endl;
                     cout<<"\t\t___________________________________________"<<endl;
                    cout<<"\t\t"<<ID<<"\t";
                    cout<<item<<"\t";
                    cout<<price<<"\t";
                    cout<<amount<<"\t";
                    cout<<amount*price<<"\n";
                    x=1;
                    break;
			    }
				
             }
             fin.close();
		
	}
		if (x==0)				//prints if no match found
				cout<<"\033[91;40;1m\n\n No Match Found! \n\n\033[0m"<<endl;
}
void Stock::rem()
{
    string s_item;
    int s;
    int tempID;
	cout<<"\nEnter ID of item you want to remove : ";
	cin>>tempID;

    ifstream fin("stock.dat" , ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary); // Temporary file to write updated data

	if (!fin.is_open()) 
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
	
    bool x = false;
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

        if (ID == tempID)               //when id matches then do not write 
        {
            cout<<endl<<endl;
			cout<<"\033[34;40;1m"<<item<<" deleted from stock successfully!\n\033[0m";
			x=1;
            

            //Now updating sales file
            ifstream fin1;
            ofstream fout1;
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

                if(s_item == item)
                {

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


        } 
        else 
        {
             // Write the strings along with their lengths to the file
            int nlen = strlen(item.c_str()) + 1; // Include null terminator
            fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
            fout.write(item.c_str(), nlen);						//storing string

            fout.write(reinterpret_cast<char*>(&ID) , sizeof(ID));
            fout.write(reinterpret_cast<char*>(&price) , sizeof(price));
            fout.write(reinterpret_cast<char*>(&amount) , sizeof(amount));
        }

     }


    fin.close();
    fout.close();
    
    // Remove the original file
    remove("stock.dat");
    // Rename the temporary file to the original file name
    rename("temp.dat", "stock.dat");
    
    if(x==0)				//error message if no ID matches
		cout<<"\033[91;40;1m\nNo Items found with this ID. Please Enter again.\033[0m"<<endl;
}
void Stock::add()
{
    bool x=0;

    string item1;
    int ID1,price1,amount1;

    cout<<"\nEnter New Item Name (first letter capital): ";
	cin>>item1;

    do          //checking in item with same id exists or not
    {
        cout<<"\nEnter ID for new Item:";
	    cin>>ID1;

        ifstream fin;
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

            if(ID==ID1)             //checking if that id already exists or not
            {
                cout<<"\033[91;40;1m\n\nAn item with this ID already exists! Please enter a new ID\n\n\033[0m"<<endl;
				x=1;
				break;
            }
            x=0;
        }

        fin.close();
        
    } while (x==1);
    
	
	cout<<"\nEnter Price for new Item: ";
	cin>>price1;
    cout<<"\nEnter Amount for new Item: ";
    cin>>amount1;

    ofstream fout;
	fout.open("stock.dat" , ios::out | ios::binary | ios::app);             //writing in append mode

    // Write the strings along with their lengths to the file
        int nlen = strlen(item1.c_str()) + 1; // Include null terminator
        fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
        fout.write(item1.c_str(), nlen);						//storing string
        fout.write(reinterpret_cast<char*>(&ID1) , sizeof(ID1));
        fout.write(reinterpret_cast<char*>(&price1) , sizeof(price1));
        fout.write(reinterpret_cast<char*>(&amount1) , sizeof(amount1));

        cout<<"\033[34;40;1m\n\n" <<item1<<" added successfully in stock !\n\033[0m"<<endl;

    fout.close();
    
    int s=0;
    //writing in sales files
	fout.open("sales.dat" , ios::out | ios::binary | ios::app);

        nlen = strlen(item1.c_str()) + 1; // Include null terminator
        fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
        fout.write(item1.c_str(), nlen);						//storing string
        fout.write(reinterpret_cast<char*>(&s) , sizeof(s));


    fout.close();

}

void Stock::order()
{
    bool x=0,y=0;
    int tempID, qty;

    //taking input from admin
	cout<<"\nEnter ID of item you want to order : ";
	cin>>tempID;

    do
	{
        cout<<"\n\n How much quantity you want to order? : ";
        cin>>qty;
        
        if(qty<1 || qty>998)				//condition to check if quantity is greater than 1000
        {
            cout<<"\033[91;40;1m\n\nPlease Enter quantity between 1 to 1000\n\n\033[0m"<<endl;
        }
        else
            y=1;
	}while (y==0);
    
    

    ifstream fin("stock.dat" , ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary); // Temporary file to write updated data

	if (!fin.is_open()) 
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
	
  
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

        if (ID == tempID)       //when id matches, write updates quantity
        {
            qty = qty + amount;

             // Write the strings along with their lengths to the file
            int nlen = strlen(item.c_str()) + 1; // Include null terminator
            fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
            fout.write(item.c_str(), nlen);						//storing string

            fout.write(reinterpret_cast<char*>(&ID) , sizeof(ID));
            fout.write(reinterpret_cast<char*>(&price) , sizeof(price));
            fout.write(reinterpret_cast<char*>(&qty) , sizeof(qty));
            cout<<"\033[34;40;1m\n\n"<<(qty-amount)<<" "<<item<<" ordered and will be added to the stock soon.\n\n\033[0m"<<endl;
			x=1;
        } 
        else 
        {
             // Write the strings along with their lengths to the file
            int nlen = strlen(item.c_str()) + 1; // Include null terminator
            fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
            fout.write(item.c_str(), nlen);						//storing string

            fout.write(reinterpret_cast<char*>(&ID) , sizeof(ID));
            fout.write(reinterpret_cast<char*>(&price) , sizeof(price));
            fout.write(reinterpret_cast<char*>(&amount) , sizeof(amount));
        }

     }


    fin.close();
    fout.close();
    
    // Remove the original file
    remove("stock.dat");
    // Rename the temporary file to the original file name
    rename("temp.dat", "stock.dat");
    
    if(x==0)				//error message if no ID matches
		cout<<"\033[91;40;1m\nNo Items found with this ID. Please Enter again.\033[0m"<<endl;
}

void Stock::update()
{
    bool x=0,y=0;
    int tempID, new_price;
	cout<<"\nEnter the ID of item you want to change price of : ";
	cin>>tempID;
    cout<<"\n\nSet a new price : Rs.";
    cin>>new_price;


    ifstream fin("stock.dat" , ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary); // Temporary file to write updated data

	if (!fin.is_open()) 
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
	
  
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

        if (ID == tempID)       //when id matches, write updated stock
        {

             // Write the strings along with their lengths to the file
            int nlen = strlen(item.c_str()) + 1; // Include null terminator
            fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
            fout.write(item.c_str(), nlen);						//storing string

            fout.write(reinterpret_cast<char*>(&ID) , sizeof(ID));
            fout.write(reinterpret_cast<char*>(&new_price) , sizeof(new_price));
            fout.write(reinterpret_cast<char*>(&amount) , sizeof(amount));

            cout<<"\033[34;40;1m\n\n Price Of "<<item<<" has been updated !\n\n\033[0m"<<endl;

			x=1;
        } 
        else 
        {
             // Write the strings along with their lengths to the file
            int nlen = strlen(item.c_str()) + 1; // Include null terminator
            fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
            fout.write(item.c_str(), nlen);						//storing string

            fout.write(reinterpret_cast<char*>(&ID) , sizeof(ID));
            fout.write(reinterpret_cast<char*>(&price) , sizeof(price));
            fout.write(reinterpret_cast<char*>(&amount) , sizeof(amount));
        }

     }


    fin.close();
    fout.close();
    
    // Remove the original file
    remove("stock.dat");
    // Rename the temporary file to the original file name
    rename("temp.dat", "stock.dat");
    
    if(x==0)				//error message if no ID matches
		cout<<"\033[91;40;1m\nNo Items found with this ID. Please Enter again.\033[0m"<<endl;
}

void Stock::sort()
{
    //first checking how much items is in file to make dynamic arrays 

    ifstream fin;
	fin.open("stock.dat" , ios::in | ios::binary);
	if (!fin.is_open()) 
    {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
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

        count++;
        
    }
	fin.close();

    //dynamically allocating memories

    string *item1 = new string[count];
    int *ID1 = new int[count];
    int *price1 = new int[count];
    int *amount1 = new int[count];

    string item2;
    int ID2, price2, amount2;


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
        item2 = nameBuffer;
        delete[] nameBuffer;

        fin.read(reinterpret_cast<char*>(&ID2) , sizeof(ID2));
        fin.read(reinterpret_cast<char*>(&price2) , sizeof(price2));
        fin.read(reinterpret_cast<char*>(&amount2) , sizeof(amount2));


        //storing in arrays
        item1[i] = item2;
        ID1[i] = ID2;
        price1[i] = price2;
        amount1[i] = amount2;

        i++;
        
        
    }
    fin.close();
    int choice, choice1;
    bool x=0;

    cout<<"\n\n\t1. Sort by Name"<<endl;
	cout<<"\n\t2. Sort by Price"<<endl;
	cout<<"\n\t3. Sort by Id"<<endl;
	cout<<"\n\t4. Sort by Quantity"<<endl;
	cout<<"\n\t5. Go Back"<<endl;
	cout<<"\n\n Select any option (1-5) : ";
	cin>>choice;
	
	switch (choice)
	{
		case 1:
			cout<<"\n\t1. Ascending"<<endl;
			cout<<"\n\t2. Descedning"<<endl;
			cout<<"\n\n Select any option : ";
			cin>>choice1;
				
			switch (choice1)
			{
				case 1:
					do
					{
					x=0;
					for (int k=0; k<count-1; k++)		
					{
						if(item1[k][0]>item1[k+1][0])		//checks first alphabet of two adjacent indexes and swaps
						{
							swap(item1[k], item1[k+1]);
							swap(ID1[k], ID1[k+1]);
							swap(price1[k], price1[k+1]);
							swap(amount1[k], amount1[k+1]);
							x=1;
						}
					}
					
					}while(x==1);			//loop continues until sorted
					
					cout<<"\033[92;40;1m\n\n\t Items Sorted by Name in Ascending order. \n\033[0m"<<endl;
					break;
					
				case 2:
					do
					{
					x=0;
					for (int k=0; k<count-1; k++)
					{
						if(item1[k][0]<item1[k+1][0])
						{
							swap(item1[k], item1[k+1]);
							swap(ID1[k], ID1[k+1]);
							swap(price1[k], price1[k+1]);
							swap(amount1[k], amount1[k+1]);
							x=1;
						}
					}
					
					}while(x==1);
					
					cout<<"\033[92;40;1m\n\n\t Items Sorted by Name in Descending order. \n\033[0m"<<endl;
					break;
				default:
					cout<<"\033[91;40;1m\n\n\tInvalid Input! Please Enter between (1-2)\n\033[0m"<<endl;
					break;
			
			}	
			break;
		case 2:
			cout<<"\n\t1. Ascending"<<endl;
			cout<<"\n\t2. Descedning"<<endl;
			cout<<"\n\n Select any option : ";
			cin>>choice1;
				
			switch (choice1)
			{
				case 1:
					do
					{
					x=0;
					for (int k=0; k<count-1; k++)
					{
						if(price1[k]>price1[k+1])
						{
							swap(item1[k], item1[k+1]);
							swap(ID1[k], ID1[k+1]);
							swap(price1[k], price1[k+1]);
							swap(amount1[k], amount1[k+1]);
							x=1;
						}
					}
					
					}while(x==1);
					
					cout<<"\033[92;40;1m\n\n\t Items Sorted by Price in Ascending order. \n\033[0m"<<endl;
					break;
					
				case 2:
					do
					{
					x=0;
					for (int k=0; k<count-1; k++)
					{
						if(price1[k]<price1[k+1])
						{
							swap(item1[k], item1[k+1]);
							swap(ID1[k], ID1[k+1]);
							swap(price1[k], price1[k+1]);
							swap(amount1[k], amount1[k+1]);
							x=1;
						}
					}
					
					}while(x==1);
					
					cout<<"\033[92;40;1m\n\n\t Items Sorted by Price in Descending order. \n\033[0m"<<endl;
					break;
					
				default:
					cout<<"\033[91;40;1m\n\n\tInvalid Input! Please Enter between (1-2)\n\033[0m"<<endl;
					break;
			
			}	
			break;
		case 3:
			cout<<"\n\t1. Ascending"<<endl;
			cout<<"\n\t2. Descedning"<<endl;
			cout<<"\n\n Select any option : ";
			cin>>choice1;
				
			switch (choice1)
			{
				case 1:
					do
					{
					x=0;
					for (int k=0; k<count-1; k++)
					{
						if(ID1[k]>ID1[k+1])
						{
							swap(item1[k], item1[k+1]);
							swap(ID1[k], ID1[k+1]);
							swap(price1[k], price1[k+1]);
							swap(amount1[k], amount1[k+1]);
							x=1;
						}
					}
					
					}while(x==1);
					
					cout<<"\033[92;40;1m\n\n\t Items Sorted by ID in Ascending order. \n\033[0m"<<endl;
					break;
					
				case 2:
					do
					{
					x=0;
					for (int k=0; k<count-1; k++)
					{
						if(ID1[k]<ID1[k+1])
						{
							swap(item1[k], item1[k+1]);
							swap(ID1[k], ID1[k+1]);
							swap(price1[k], price1[k+1]);
							swap(amount1[k], amount1[k+1]);
							x=1;
						}
					}
					
					}while(x==1);
					
					cout<<"\033[92;40;1m\n\n\t Items Sorted by ID in Descending order. \n\033[0m"<<endl;
					break;
					
				default:
					cout<<"\033[91;40;1m\n\n\tInvalid Input! Please Enter between (1-2)\n\033[0m"<<endl;
					break;
			
			}	
			break;
		case 4:
			cout<<"\n\t1. Ascending"<<endl;
			cout<<"\n\t2. Descedning"<<endl;
			cout<<"\n\n Select any option : ";
			cin>>choice1;
				
			switch (choice1)
			{
				case 1:
					do
					{
					x=0;
					for (int k=0; k<count-1; k++)
					{
						if(amount1[k]>amount1[k+1])
						{
							swap(item1[k], item1[k+1]);
							swap(ID1[k], ID1[k+1]);
							swap(price1[k], price1[k+1]);
							swap(amount1[k], amount1[k+1]);
							x=1;
						}
					}
					
					}while(x==1);
					
					cout<<"\033[92;40;1m\n\n\t Items Sorted by Quantity in Ascending order. \n\033[0m"<<endl;
					break;
					
				case 2:
					do
					{
					x=0;
					for (int k=0; k<count-1; k++)
					{
						if(amount1[k]<amount1[k+1])
						{
							swap(item1[k], item1[k+1]);
							swap(ID1[k], ID1[k+1]);
							swap(price1[k], price1[k+1]);
							swap(amount1[k], amount1[k+1]);
							x=1;
						}
					}
					
					}while(x==1);
					
					cout<<"\033[92;40;1m\n\n\t Items Sorted by Quantity in Descending order. \n\033[0m"<<endl;
					break;
					
				default:
					cout<<"\033[91;40;1m\n\n\tInvalid Input! Please Enter between (1-2)\n\033[0m"<<endl;
					break;
			
			}	
			break;
		case 5:
			break;
		default:
			cout<<"\033[91;40;1m\n\n\tInvalid Input! Please Enter between (1-5)\n\033[0m"<<endl;
			break;
	

	
	}

    ofstream fout("temp.dat", ios::out | ios::binary); // Temporary file to write updated data
    for(int j=0; j<count; j++)
    {
        // Write the strings along with their lengths to the file
            int nlen = strlen(item1[j].c_str()) + 1; // Include null terminator
            fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
            fout.write(item1[j].c_str(), nlen);						//storing string

            fout.write(reinterpret_cast<char*>(&ID1[j]) , sizeof(ID1[j]));
            fout.write(reinterpret_cast<char*>(&price1[j]) , sizeof(price1[j]));
            fout.write(reinterpret_cast<char*>(&amount1[j]) , sizeof(amount1[j]));

           // cout<<ID1[j]<<"\t"<<item1[j]<<"\t"<<price1[j]<<"\t"<<amount1[j]<<endl;
    }
    fout.close();
    // Remove the original file
    remove("stock.dat");
    // Rename the temporary file to the original file name
    rename("temp.dat", "stock.dat");

    //deleting dynamic arrays 

    delete [] item1;
    item1 = NULL;
    delete [] ID1;
    ID1 = NULL;
    delete [] price1;
    price1 = NULL;
    delete [] amount1;
    amount1 = NULL;

}
void Stock::Warn()              //to display warning
{
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


        if(amount<10)		//condition to check if item is lower than threshold (10)
		{
			cout<<endl<<endl;
			cout<<"\033[91;107;1;5m  [ Warning ! "<<item<<" are low in stock  ]   \033[0m"<<endl;
		}

    }
    fin.close();

}

void Stock::salesinit()
{
    ifstream fin;
	fin.open("stock.dat" , ios::in | ios::binary);
    ofstream fout;
    fout.open("sales.dat" , ios::out | ios::binary);
	fin.seekg(0);					//starts with the beginning of file
    int s=0;
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

        //writing in sales file
        nlen = strlen(item.c_str()) + 1; // Include null terminator
        fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
        fout.write(item.c_str(), nlen);						//storing string
        fout.write(reinterpret_cast<char*>(&s) , sizeof(s));

        
    }
	fin.close();
    fout.close();
}
void Stock::salesdisp()
{
    ifstream fin;
	fin.open("sales.dat" , ios::in | ios::binary);
	fin.seekg(0);					//starts with the beginning of file
    int s;
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

        cout<<"\n"<<item<<"\t\t"<<s<<endl;
        
    }
	fin.close();
}