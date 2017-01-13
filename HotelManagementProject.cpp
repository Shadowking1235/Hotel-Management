//PROJECT ON HOTEL MANAGEMENT

#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

fstream f1,f2,f3,f4,f5;
int rno[25];

//*****************************************************************************************************
//          CLASS NAME :  Enter
//          DETAILS         :  IT CONSISTS OF ALL REQUIRED INFORMATION
//                                    ABOUT A CUSTOMER.
//*****************************************************************************************************


class Enter
{
	char name[25];
	char address[30];
	long phnum;
	int num_p;
	public:
	int n;                   //no of rooms
	int rooms[5];
	void enterdata();
	void displaydata();
	void roomnum();
	int* getrno();

}e,e1;

struct vacancy
{
	 char v;
	 int r ;
}v1;


void Enter::enterdata()     //TO ENTER DATA OF THE CUSTOMER.
{
	cout<<"\n"<<"ENTER THE NAME OF THE CUSTOMER : "<<endl;
	cin>>name;
	cout<<"\n";
	cout<<"\n"<<"ENTER THE ADDRESS : "<<endl;
	cin>>address;
	cout<<"\n";
	cout<<"\n"<<"ENTER CONTACT NUMBER : "<<endl;
	cin>>phnum;
	cout<<"\n";
	cout<<"\n"<<"ENTER NUMBER OF PEOPLE : "<<endl;
	cin>>num_p;
	cout<<"\n";
	cout<<"\n"<<"ENTER NUMBER OF ROOMS REQUIRED(MAX 5) : "<<endl;
	cin>>n;
	cout<<"\n";
	roomnum();
}


void Enter::displaydata()    //TO DISPLAY DATA OF THE CUSTOMER.
{
	cout<<"\n"<<"**********CUSTOMER DETAILS************"<<endl
	    <<"\n"<<"NAME : "<<name<<"\n"<<endl
	    <<"\n"<<"ADDRESS : "<<address<<"\n"<<endl
	    <<"\n"<<"CONTACT NUMBER : "<<phnum<<"\n"<<endl
	    <<"\n"<<"NUMBER OF PEOPLE : "<<num_p<<"\n"<<endl
	    <<"\n"<<"NUMBER OF ROOMS : "<<n<<"\n"<<endl
	    <<"\n"<<"YOUR ROOMNUMBERS ARE :"<<endl;
	for(int x = 0; x<n; x++)
	{
		cout<<"\n";
	     	cout<<rooms[x];
	}

}


void Enter::roomnum()       //TO GENERATE ROOMNUMBERS FOR THE CUSTOMER.
{
	f1.open("Room.dat",ios::binary|ios::out|ios::in);
	char ch;
	cout<<"\n"<<endl;
	cout<<"\n"<<"ENTER YOUR CHOICE (N/D/C) : ";
	cin>>ch;
	int z, q,i;
	if(ch == 'N')
	{
		z = 1;
		q=200;
	}
	else if(ch == 'D')
	{	z = 201;
		q = 250;
	}
	else if(ch == 'C')
	{
		z = 251;
		q = 253;
	}
	for( i=0;i<n;)
	{

		f1.read((char*)&v1, sizeof(v1));
		if(!f1.eof())
		{
			if((v1.r>=z) && (v1.r<=q))
			{
				if((v1.v == 'N'))
				{
					cout<<"\n"<<v1.r;
					rooms[i] = v1.r;
					++i;
					int x=sizeof(vacancy);
					x=-1*x;
					f1.seekg(x,ios::cur);
					f1.write((char*)&v1,sizeof(vacancy));
				}

			}
		}
		else
			break;
	}


	if(i!=n)
		cout<<"\n"<<"Rooms not available";
	f1.close();

}


int* Enter::getrno()
{
	return rooms;
}


void room()  //TO CREATE A FILE CONTAINING ROOMNUMBERS AND THEIR STATUS.
{
	f2.open("Room.dat",ios::binary|ios::out);
	for(int i=1;i<=253;i++)
	{
		v1.v = 'N';
		v1.r = i;
		f2.write((char*)&v1, sizeof(v1));
	}
	f2.close();
}

void entry()     //TO CREATE A FILE TO STORE THE DATA OF THE CUSTOMER.
{	cout<<"\n";
	cout<<"\n"<<"THREE TYPES OF ROOMS ARE AVAILABLE...."<<endl;
	cout<<"\n";
	cout<<"\n"<<"NORMAL (N) - 1500 RUPEES PER DAY ,"<<endl;
	cout<<"\n";
	cout<<"\n"<<"DELUXE (D) - 3500 RUPEES PER DAY ,"<<endl;
	cout<<"\n";
	cout<<"\n"<<"CONFERENCE HALLS (C) - 7000 RUPEES PER DAY ."<<endl;
	cout<<"\n";
	f3.open("Hoteldata.dat",ios::binary|ios::out|ios::app);
	e.enterdata();
	f3.write((char*)&e,sizeof(e));
	f3.seekg(0);
	e.displaydata();
	cout<<"\n";
	cout<<"\n"<<"DATA FROM FILE IS : "<<"\n"<<endl;
	cout<<"\n";
	f3.read((char*)&e,sizeof(e));
	e.displaydata();
	f3.close();

}


void billing()   //TO CALCULATE THE HOTEL BILL OF THE CUSTOMER.
{
	int k,temp,small, a[25],no_of_days,*r,i,x,n;
	float service_tax,R,b[25],VAT,bill=0,bill1,total_bill;
	cout<<"\n";
	cout<<"\n"<<"ENTER NUMBER OF ROOMS : "<<endl;
	cin>>n;
	cout<<"\n";
	cout<<"\n"<<"ENTER ROOM NUMBERS : "<<endl;
	cout<<"\n";
	for(k=0;k<n;++k)
		cin>>a[k];
	f4.open("Hoteldata.dat",ios::binary|ios::in);
	while(!f4.eof())
	{
		f4.read((char*)&e1,sizeof(e1));
		r=e1.getrno();
		for(k=0,i=0;k<n;++k,++i)
		{
			if(r[i]==a[k])
			{	cout<<"\n";
				cout<<"\n"<<"CUSTOMER'S DATA IS : "<<"\n"<<endl;
				e1.displaydata();
				cout<<"\n";
				if(r[0]<=200 )
					R=1500;
				else if(r[0]<=250)
					R=3500;
				else if(r[0]<=253 )
					R=7000;
			}

		}
	}
	cout<<"\n"<<"ENTER NUMBER OF DAYS : "<<endl;
	cin>>no_of_days;
	bill=bill+(no_of_days*R*n);
	f4.close();
	VAT=bill*0.15;                                   //VAT is 15%of the bill.
	service_tax=bill*0.12;                      //service tax is 12% of the bill.
	bill1=bill+VAT+service_tax;
	cout<<"\n"<<"********HOTEL SUKH SAGAR*********"<<endl;
	cout<<"\n"<<"BILL : "<<"\n"<<endl;
	f5.open("Hoteldata.dat",ios::binary|ios::in);
	while(!f5.eof())
	{
		f5.read((char*)&e1,sizeof(e1));
		if(r[0]==a[0])
			e1.displaydata();
	} f5.close();
	cout<<"\n"<<"LODGING FEE : "<<bill<<"\n"<<endl;
	cout<<"\n"<<"VAT : "<<VAT<<"\n"<<endl;
	cout<<"\n"<<"SERVICE TAX : "<<service_tax<<"\n"<<endl;
	cout<<"\n"<<"YOUR TOTAL BILL IS : "<<bill1<<"\n"<<endl;
	cout<<"\n"<<"THANK YOU FOR VISITING PLEASE VISIT AGAIN..........."<<endl;
}

//************************************************************************************************************************
// CLASS NAME :  food
//  DETAILS        :  IT CONSISTS OF ALL THE DATA REQUIRED FOR THE RESTAURANT'S MENU.
//***********************************************************************************************************************

class food
{
	public:
	char food_type;
	float cost;
	char food_name[25];

};


void restaurant(void)  //MENU TO ORDER FOOD AND TO GENERATE THE BILL.
{	cout<<"\n";
	cout<<"PLEASE SWITCH ON THE CAPSLOCK. ENTER IN WITH CAPITAL LETTERS\n\n"<<endl;
	int choice;
	cout<<"WHAT DO YOU WANT TO DO?? \n"<<endl;
	cout<<"\n 1. ENTER NEW FOOD ITEM \n"<<endl;
	cout<<"\n 2. ORDER FOOD \n"<<endl;
	cout<<"\n\n ENTER YOUR CHOICE- 1 OR 2 \t\t"<<endl;
	cin>>choice;
	fstream f;
	switch (choice)
	{
		case 1	:	food newfood;
				// fstream f;
				f.open("menu.dat", ios::binary | ios::out | ios::app);
				char ch;
				do
				{	cout<<"\n";
					cout<<"ENTER NAME OF FOOD \t\t"<<endl;
					cin>>newfood.food_name;
					cout<<"\n"<<"ENTER TYPE - \n"<<endl
					<<"'V' FOR VEGETARIAN\n"<<endl
					<<"'N' FOR NON VEGETARIAN\n\t"<<endl;
					cin>>newfood.food_type;
					cout<<"ENTER COST \t\t"<<endl;
					cin>>newfood.cost;
					f.write((char*)&newfood, sizeof(newfood));
					cout<<"\n\n DO YOU WANT TO ENTER MORE? :\t\t"<<endl;
					cin>>ch;

				} while(ch=='Y');
				break;
				char ch1;

		case 2	:	float bill = 0;
				do
				{      	 int plates;
					char name[25], typ;
					food order;
					// fstream f;
					f.open("menu.dat", ios::binary | ios::in | ios::out);
					cout<<"\n"<<"ENTER TYPE OF FOOD YOU WANT TO EAT \n"<<endl
					<<" V FOR VEGETARIAN, \n"<<endl
					<<" N FOR NON VEGETARIAN, \n"<<endl
					<<" B FOR BOTH \n \t\t"<<endl;
					cin>>typ;

					if(typ == 'N' ||typ == 'V')
					{	while(!f.eof())
						{	f.read((char*)&order, sizeof(order));
							if(order.food_type == typ)
							{
								cout<<"\n"<<order.food_name<<"\t\t\t"<<order.cost<<"\n";
							}
						}
					}
					else if(typ == 'B')
					{	while(!f.eof())
						{

							f.read((char*)&order, sizeof(order));

							cout<<"\n"<<order.food_name<<"\t\t\t"<<order.food_type<<"\t"<<order.cost<<"\n";

						}
					}
					cout<<"\n"<<"ENTER NAME OF FOOD YOU WANT TO ORDER :\t\t";
					cin>>name;
					cout<<"\n"<<"ENTER NUMBER OF PLATES YOU WANT TO ORDER\t\t";
					cin>>plates;
					f.close();
					f.open("menu.dat",ios::binary| ios::in);
					while(!f.eof())
					{
						f.read((char*)&order, sizeof(order));
						if (strcmp(name, order.food_name) == 0)
						{
						       bill=bill+(order.cost*plates);
						}

					}
					f.close();
					cout<<"\n"<<"DO YOU WANT TO ORDER MORE?? Y OR N\t\t"<<endl;
					cin>>ch1;

				} while(ch1 == 'Y');
				cout<<"\n"<<"YOUR BILL AMOUNT IS: \t\t\t" <<bill;


	}

}


int main()
{
	int c;
	do
	{


		cout<<"\n"<<"*************WELCOME TO HOTEL SUKH SAGAR*************"<<endl;
		cout<<"\n"<<"WHAT DO YOU WANT TO DO ? "<<endl;
		cout<<"\n"<<"ENTER YOUR CHOICE : "<<"\n"<<endl
	    	<<"\n"<<"1. CHECK IN "<<"\n"<<endl
	    	<<"\n"<<"2. RESTAURANT "<<"\n"<<endl
	    	<<"\n"<<"3. CHECK OUT "<<"\n"<<endl
	    	<<"\n"<<"4. MARK ALL ROOMS EMPTY?"<<endl<<endl<<endl<<"5. EXIT"<<endl;
		cin>>c;
		switch(c)
		{
			case 1 : cout<<"\n";
				entry();
			 	break;

			case 2 : cout<<"\n";
				 restaurant();
			 	break;

			case 3 : cout<<"\n";
				 billing();
			 	break;
			case 4 : cout<<"\n";
			 	room();
			 	break;

		}


	}while(c!=5);
	return 0;
}
