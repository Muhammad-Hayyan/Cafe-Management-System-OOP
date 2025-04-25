/*							MUHAMMAD HAYYAN
								23I-2041
								Cyber - B
								OOP Project									*/
#include "main.h"
#include <fstream>

Order::Order()
{

}
Order::Order(int a, string i)
{
    item = i;
    amount = a;
}
void Order::add()                       //to add a schedule order
{
    int ID, price;
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

        fin.read(reinterpret_cast<char*>(&ID1[i]) , sizeof(ID1[i]));
        fin.read(reinterpret_cast<char*>(&price1[i]) , sizeof(price1[i]));
        fin.read(reinterpret_cast<char*>(&amount1[i]) , sizeof(amount1[i]));
        i++;
        
        
    }
    fin.close();


    bool x=0, r=0, n=0, z=0;
    int p, sch_id, sch_qty, choice;
    do
    {
      
        x=0;
        r=0; 
        n=0;
        do
        {
            x=0;
            cout<<"\n\nEnter the ID of item you want to order : ";			//taking input id from user
            cin>>sch_id;
            
            for (int k=0; k<count; k++)
            {
                if(sch_id == ID1[k])				//checking if id exists in stock, if not it generates error 
                {
                    x=1;
                    p=k;
                    break;
                }
                
            }
            if (x==0)
                cout<<"\033[91;40;1m\n\n No items found with this ID. Please enter again. \n\n\033[0m"<<endl;
            
        }while(x==0);				//continues if invalid ID

        do
        {
            cout<<"\n\nEnter quantity of item you want to order : ";		//taking quantity of item from user
            cin>>sch_qty;
            
            if(sch_qty<1)
            {
                cout<<"\033[91;40;1m\n\n Please enter quantity greater than 1 !\n\n\033[0m"<<endl;
            }
            else 
                r=1;
        }while(r==0);


        ofstream fout;
        fout.open("schorder.dat", ios::out | ios::binary | ios::app);

        int nlen = strlen(item1[p].c_str()) + 1; // Include null terminator
        fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
        fout.write(item1[p].c_str(), nlen);						//storing string
        fout.write(reinterpret_cast<char*>(&sch_qty) , sizeof(sch_qty));

        fout.close();

        do                      //to prompt to continue ordering
        {
            cout<<"\n\n\t1. Continue Ordering "<<endl;		//asking user if he want to continue ordering or exit
            cout<<"\n\t2. Exit Order "<<endl;
            cout<<"\n\nSelect any option : ";
            cin>>choice;
            
            switch (choice)
            {
                case 1:
                    n=1;
                    break;
                case 2:
                    cout<<"\033[34;40;1m\n\n Your order has been scheduled successfully ! \n\n\033[0m"<<endl;
                    z=1, n=1;
                    break;
                default:
                    cout<<"\033[91;40;1m\n\n Invalid Input! Please enter between (1 - 2). \n\n\033[0m"<<endl;
                    break;
            
            }
        }while(n==0);			//continues if invalid input

    }while(z==0);

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
void Order::manage()                        //for employee/admin to approve/decline schedule orders
{
    ifstream fin;
    fin.open("schorder.dat" , ios::in | ios::binary);

    int count=0, count1=0, ID, price, choice;
    bool x=0, y=0, z=0;

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

        fin.read(reinterpret_cast<char*>(&amount) , sizeof(amount));
        count1++;                   //reading number of orders
    
    }
    fin.close();

    fin.open("stock.dat" , ios::in | ios::binary);
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

        count++;                //reading number of items
        
    }
	fin.close();

    //to store stock items
    string *item1 = new string[count];
    int *ID1 = new int[count];
    int *price1 = new int[count];
    int *amount1 = new int[count];

    //to store scheduled items
    string *sch_item = new string[count1];
    int *sch_amount = new int[count1];
    int *s_no = new int[count1];

    
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

        //storing in arrays
        fin.read(reinterpret_cast<char*>(&ID1[i]) , sizeof(ID1[i]));
        fin.read(reinterpret_cast<char*>(&price1[i]) , sizeof(price1[i]));
        fin.read(reinterpret_cast<char*>(&amount1[i]) , sizeof(amount1[i]));
        i++;
    }
    fin.close();

    i=0;
    fin.open("schorder.dat" , ios::in | ios::binary);
    while (!fin.eof()) 
    {
        int nlen;
        fin.read(reinterpret_cast<char*>(&nlen), sizeof(nlen));
        if (fin.eof()) // Break loop if end of file
            break;

        // Allocate memory for name and read from file
        char* nameBuffer = new char[nlen];
        fin.read(nameBuffer, nlen);
        sch_item[i] = nameBuffer;
        delete[] nameBuffer;

        fin.read(reinterpret_cast<char*>(&sch_amount[i]) , sizeof(sch_amount[i]));
        s_no[i] = i;
        i++;
    
    }
    fin.close();


    int order, m, p;
    ofstream fout;
    ifstream fin1;
    ofstream fout1;

    do						
	{
        x=0, y=0, z=0;
        
        //Printing the scheduled orders 
        
        cout<<"\n\n\t\tS.No\t\tItem\t\tQuantity\n"<<endl;
        for(int k=0; k<count1; k++)
        {
            
            cout<<"\t\t"<<s_no[k]<<"\t\t"<<sch_item[k]<<"\t\t  "<<sch_amount[k]<<"\n";
            cout<<"\n\t  --------------------------------------------------\n\n";
        
        }
        
        cout<<"\n\n-------------------------------------------------------------------------------------------------\n\n";
        cout<<"\n\t 1. Approve Order \n";
        cout<<"\n\t 2. Decline Order \n";
        cout<<"\n\t 3. Go Back \n";
        cout<<"\n\n Select one of the option (1-3) :";			//taking choice from admin/employee 
        cin>>choice;
        
        switch(choice)
        {
            case 1:					//to approve order
                do
                {
                    x=0;
                    cout<<"\n\n Enter S.No of scheduled order you want to approve : ";
                    cin>>order;
                    
                    for (int k=0; k<count1; k++)			//Checking if schedule order with this s no exists or not
                    {
                        if(order == s_no[k])
                        {
                            m=k;			//m is now the index of scheduled order selected
                            x=1;
                            break;
                        }
                    
                    }
                    if (x==0)			//if not then prints error and loop goes on
                        cout<<"\033[91;40;1m\n\n No orders found with this S.No. Please enter again ! \n\n\033[0m"<<endl;
                        
                }while (x==0);		//loop breaks if entered s.no exists 
                
                for (int k=0; k<count; k++)			//stocks ki file k liye loop
                {
                    if(sch_item[m] == item1[k])			//Finding the selected schedule order item from stock
                    {
                        p=k;						//p is now index of stock item that is scheduled
                        
                        if(sch_amount[m] <= amount1[k])			//this condition checks k utni items stock mein available hein or not
                        {
                            y=1;
                            z=1;
                            
                            fout.open("schorder.dat", ios::out | ios::binary);			
                            for(int s=0; s<count1; s++)		//deleting order from schedule txt that is approved
                            {
                                if(m == s)		//This does not write data when condition satisfies
                                {
                                    cout<<"\033[34;40;1m\n\n Order Approved Successfully ! \n\n\033[0m"<<endl;
                                    cout<<"\n\n--------------------------------------------------------------------------------------\n\n";
                                
                                }
                                else
                                {
                                    int nlen = strlen(sch_item[s].c_str()) + 1; // Include null terminator
                                    fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
                                    fout.write(sch_item[s].c_str(), nlen);						//storing string
                                    fout.write(reinterpret_cast<char*>(&sch_amount[s]) , sizeof(sch_amount[s]));
                                
                                }
                                
                            } 
                            fout.close();
                            break;
                        }
                        else		//Generates an error message when not enough quantity is in stock
                        {
                            cout<<"\033[91;40;1m\n\n Sorry ! "<<sch_amount[m]<<" "<<item1[p]<<" not available in stock.\n\n\033[0m"<<endl;
                            cout<<"\n\n--------------------------------------------------------------------------------------\n\n";
                            z=1;
                            break;
                        }
                    }
                
                }

                if(y==1)			//Updating stock when item is approved 
                {
                    fout.open("stock.dat" , ios::out | ios::binary);
                    for(int k=0; k<count; k++)
                    {
                        if(k==p)
                        {
                            amount1[k] = amount1[k] - sch_amount[m];
                        }
                        int nlen = strlen(item1[k].c_str()) + 1; // Include null terminator
                        fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
                        fout.write(item1[k].c_str(), nlen);						//storing string
                        fout.write(reinterpret_cast<char*>(&ID1[k]) , sizeof(ID1[k]));
                        fout.write(reinterpret_cast<char*>(&price1[k]) , sizeof(price1[k]));
                        fout.write(reinterpret_cast<char*>(&amount1[k]) , sizeof(amount1[k]));
                    }

                    
                        //Now updating sales file
                    fout1.open("temp2.dat" , ios::out | ios::binary);
                    fin1.open("sales.dat" , ios::in | ios::binary);
                    fin1.seekg(0);					//starts with the beginning of file
                    int s;
                    string s_item;
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

                        if(s_item == item1[p])
                        {
                                s += sch_amount[m];
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
                }
                
                break;
                
            case 2:						//to decline order
                
                do
                {
                    x=0;
                    cout<<"\n\n Enter S.No of scheduled order you want to Decline : ";
                    cin>>order;
                    
                    for (int k=0; k<count1; k++)			//stocks ki file k liye loop
                    {
                        if(order == s_no[k])			//Checking if schedule order with this s no exists or not
                        {
                            x=1;
                            
                            fout.open("schorder.dat", ios :: out | ios::binary);		//now deleting declined order from schedule txt
                            for(int s=0; s<count1; s++)
                            {
                                    
                                    if(s == k)              //when matches, do not write
                                    {
                                        cout<<"\033[34;40;1m\n\n Order has been declined  \n\n\033[0m"<<endl;
                                        z=1;
                                    
                                    }
                                    else
                                    {
                                        int nlen = strlen(sch_item[s].c_str()) + 1; // Include null terminator
                                        fout.write(reinterpret_cast<char*>(&nlen) , sizeof(nlen));				//storing size
                                        fout.write(sch_item[s].c_str(), nlen);						//storing string
                                        fout.write(reinterpret_cast<char*>(&sch_amount[s]) , sizeof(sch_amount[s]));
                                    
                                    }
                                    
                            } 
                            fout.close();
                            break;
                        }
                    
                    }
                    if (x==0)
                        cout<<"\033[91;40;1m\n\n No orders found with this S.No. Please enter again ! \n\n\033[0m"<<endl;
                        
                }while (x==0);
                
                break;
                
            case 3:						//go back
                z=1;
                break;
                
            default:
                cout<<"\033[91;40;1m\n\n Invalid Input! Please enter between (1 - 3). \n\n\033[0m"<<endl;
                break;
        
        
        }

	}while(z==0); 


    //deleting dynamic arrays 

    delete [] item1;
    item1 = NULL;
    delete [] ID1;
    ID1 = NULL;
    delete [] price1;
    price1 = NULL;
    delete [] amount1;
    amount1 = NULL;
    delete [] sch_item;
    sch_item = NULL;
    delete [] sch_amount;
    sch_amount = NULL;
}