#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;
struct Manu
{
	string RetailerName;
	string MobileModle, LaptopModle;
	unsigned int MobileAmount, LaptopAmount;
	unsigned int RetailerID;
	int Investment = 0;
	Manu *Nptr, *Pptr;
};
class ManufecturOrder
{
private:
	Manu* start, * current, * next;
	string rn, mm, lm;
	unsigned int ma, la, ri;
	bool found;
	int Invest, keyID;;
	ifstream read;
	ofstream write;
	bool correctinput = true;
	string mobile_models[5]={"A72","A52","A20","A30","A52"};
	string laptop_models[5]={"Core2Duo","Pentium4","Corei3","Corei4","Corei5"};
public:
	ManufecturOrder()
	{
		start = current = next = NULL;
	}
	void ReadFile()
	{
		start = NULL;
		read.open("RetailerData.txt");
		while (read >> rn >> ri >> mm >> ma >> lm >> la >> Invest)
		{
			if (start == NULL)
			{
				next = new Manu;
				next->RetailerName=rn;
				next->RetailerID = ri;
				next->MobileModle=mm;
				next->MobileAmount=ma;
				next->LaptopModle=lm;
				next->LaptopAmount=la;
				next->Investment=Invest;
				next->Nptr = NULL;
				next->Pptr = NULL;
				current = next;
				start = next;
			}
			else
			{
				next = new Manu;
				next->RetailerName = rn;
				next->RetailerID = ri;
				next->MobileModle = mm;
				next->MobileAmount = ma;
				next->LaptopModle = lm;
				next->LaptopAmount = la;
				next->Investment = Invest;
				next->Nptr = NULL;
				next->Pptr = current;
				current->Nptr = next;
				current = next;
			}	
		}
			read.close();
		}
		
	int MobilePrices(string MbMD, int amount)
	{
		if (MbMD == mobile_models[0])
		{
			correctinput = true;
			return amount*50000;
		}
		else if(MbMD==mobile_models[1])
		{
			correctinput = true;
			return amount * 40000;
		}
		else if (MbMD == mobile_models[2])
		{
			correctinput = true;
			return amount * 200000;
		}
		else if(MbMD==mobile_models[3])
		{
			correctinput = true;
			return amount * 40000;
		}
		else if (MbMD == mobile_models[4])
		{
			correctinput = true;
			return amount * 200000;
		}
		else
		{
			cout << "Mobile Model Does Not Exit\n\n";
			correctinput = false;
			return 0;
		}
	}
	int LaptopPrices(string LpMD, int amount)
	{
		if (LpMD == laptop_models[0])
		{
			correctinput = true;
			return amount * 50000;
		}
		else if (LpMD == laptop_models[1])
		{
			correctinput = true;
			return amount * 60000;
		}
		else if (LpMD == laptop_models[2])
		{
			correctinput = true;
			return amount * 75000;
		}
		else if (LpMD == laptop_models[3])
		{
			correctinput = true;
			return amount * 60000;
		}
		else if (LpMD == laptop_models[4])
		{
			correctinput = true;
			return amount * 75000;
		}
		else
		{
			cout << "Laptop Model Does Not Exit\n\n";
			correctinput = false;
			return 0;
		}
	}
	void show_available_items()
	{
		cout<<"MOBILES THAT ARE AVAILABLE ARE:-"<<endl;
		for (int i=0; i<5;i++)
			{cout <<mobile_models[i]<<"   ";
			}
		cout<<endl<<endl;
		cout<<"LAPTOPS THAT ARE AVAILABLE ARE:-"<<endl;
		for (int i=0; i<5;i++)
			{cout <<laptop_models[i]<<"   ";
			}
		cout<<endl<<endl;
	}
	void RetailerDataInsertion()
	{
		string check;
		ReadFile();
		write.open("RetailerData.txt", ios::app);
		show_available_items();
		if (start == NULL)
		{
			next = new Manu;
			cout << "\nEnter the Name of New Retailer: ";
			cin >> next->RetailerName;
			write<< next->RetailerName<<" \t\t";
			cout << "Enter the ID of New Retailer: ";
			cin >> next->RetailerID;
			write << next->RetailerID << " \t\t";
			
			
			cout<<"\nPRESS 1 TO BUY MOBILES\nPRESS 0 FOR NOT\n";
			cin>>check;
			if(check=="1")
				{
					cout << "Enter Mobile Model: ";
					cin >> next->MobileModle;
					cout << "Enter the Number of Mobiles Retailer Bought: ";
					cin >> next->MobileAmount;
					next->Investment += MobilePrices(next->MobileModle, next->MobileAmount);
					if (correctinput == true)
					{
						write << next->MobileModle << " \t\t"<<next->MobileAmount<<" \t\t";
					}
					else
					{
						next->MobileModle = "NIL";
						next->MobileAmount = 0;
						write << next->MobileModle << " \t\t" << next->MobileAmount << " \t\t";
					}
				}
			else if(check=="0")
				{
				
				}
			else	
				{
					cout<<"INVALID INPUT"<<endl;
				}
				
			cout<<"\nPRESS 1 TO BUY LAPTOPS\nPRESS 0 FOR NOT\n";	
			cin>>check;
			if(check=="1")
			{
				cout << "\nEnter Laptop Model: ";
				cin >> next->LaptopModle;
				cout << "Enter the Number of Laptop Retailer Bought: ";
				cin >> next->LaptopAmount;
				next->Investment += LaptopPrices(next->LaptopModle, next->LaptopAmount);
				if (correctinput == true)
				{
					write << next->LaptopModle << " \t\t" << next->LaptopAmount << " \t\t";
				}
				else
				{
					next->LaptopModle = "NIL";
					next->LaptopAmount = 0;
					write << next->LaptopModle << " \t\t" << next->LaptopAmount << " \t\t";
				}
				
			}
			else if(check=="0")
				{
					
				}
			else	
				{
					cout<<"INVALID INPUT"<<endl;
				}
			write << next->Investment<<endl;
			next->Nptr = NULL;
			next->Pptr = NULL;
			current = next;
			start = next;
		}
		else
		{
			next = new Manu;
			cout << "\nEnter the Name of New Retailer: ";
			cin >> next->RetailerName;
			write << next->RetailerName << " \t\t";
			cout << "Enter the ID of New Retailer: ";
			cin >> next->RetailerID;
			write << next->RetailerID << " \t\t";
			
			cout<<"\nPRESS 1 TO BUY MOBILES\nPRESS 0 FOR NOT\n";
			cin>>check;
			if(check=="1")
				{
					cout << "Enter Mobile Model: ";
					cin >> next->MobileModle;
					cout << "Enter the Number of Mobiles Retailer Bought: ";
					cin >> next->MobileAmount;
					next->Investment += MobilePrices(next->MobileModle, next->MobileAmount);
					if (correctinput == true)
					{
						write << next->MobileModle << " \t\t" << next->MobileAmount << " \t\t";
					}
					else
					{
						next->MobileModle = "NIL";
						next->MobileAmount = 0;
						write << next->MobileModle << " \t\t" << next->MobileAmount << " \t\t";
					}
				}
			else if(check=="0")
				{
					
				}
			else	
				{
					cout<<"INVALID INPUT"<<endl;
				}
				
			cout<<"\nPRESS 1 TO BUY LAPTOPS\nPRESS 0 FOR NOT\n";
			cin>>check;	
			if(check=="1")
			{
				cout << "\n\nEnter Laptop Model: ";
				cin >> next->LaptopModle;
				cout << "Enter the Number of Laptop Retailer Bought: ";
				cin >> next->LaptopAmount;
				next->Investment += LaptopPrices(next->LaptopModle, next->LaptopAmount);
				if (correctinput == true)
				{
					write << next->LaptopModle << " \t\t" << next->LaptopAmount << " \t\t";
				}
				else
				{
					next->LaptopModle = "NIL";
					next->LaptopAmount = 0;
					write << next->LaptopModle << " \t\t" << next->LaptopAmount << " \t\t";
				}
			}	
			else if(check=="0")
				{
					
				}
			else	
				{
					cout<<"INVALID INPUT"<<endl;
				}
			write << next->Investment<<endl;
			next->Nptr = NULL;
			next->Pptr = current;
			current->Nptr = next;
			current = next;
		}
		write.close();
	}
	void DeleteRetailerData()
	{	ManufecturOrder obj;
		ReadFile();
		ofstream write2;
		found=false;
		cout<<"EXISTING PRODUCTS RECORD LIST:-"<<endl<<endl;
		obj.RetailerDataTRAVER();
		cout << "Enter the Retailer ID You want to DELETE: ";
		cin >> keyID;
		read.open("RetailerData.txt", ios::app);
		write2.open("RetailerData2.txt", ios::app);
		
		while (read >> rn >> ri >> mm >> ma >> lm >> la >> Invest)
		{
			if (ri == keyID)
			{
				cout << endl << ri << "   Retailer Data is Deleted\n\n";
				found = true;
			}
			else
			{
				write2 << rn << " \t\t";
				write2 << ri << " \t\t";
				write2 << mm << " \t\t" << ma << " \t\t";
				write2 << lm << " \t\t" << la << " \t\t";
				write2 << Invest << endl;
			}
		}
		if (found == false)
		{
			cout << "Retailer ID is INVALID\n\n";
		}
		read.close();
		write2.close();
		remove("RetailerData.txt");
		rename("RetailerData2.txt","RetailerData.txt");
		ReadFile();
	}
	void SearchRetailerData()
	{	ManufecturOrder obj;
		ReadFile();
		found = false;
		obj.show_record_ids();
		cout << "\n\nEnter the ID You want to search: ";
		cin >> keyID;
		current = start;
		while (current != NULL)
		{
			if (keyID == current->RetailerID)
			{
				found = true;
				break;
			}
			current = current->Nptr;
		}
		if (found == false)
		{
			cout << "ID Not Found\n\n";
		}
		else
		{
			cout << "    " << "Name      |      " << "ID     |      " << "Laptop     |     " << "Amount   |      " << "Mobile     |      " << "Amount     |     " << "Investment\n";
			cout << "______________|_____________|_________________|______________|_________________|_________________|_________________\n";
			cout << "     " << current->RetailerName << "          " << current->RetailerID << "           " << current->LaptopModle << "                 " << current->LaptopAmount;
			cout << "                " << current->MobileModle << "               " << current->MobileAmount;
			cout << "                " << current->Investment << endl << endl;
			cout << "______________|_____________|_________________|______________|_________________|_________________|_________________\n";
		}
	}
	
	void RetailerDataTRAVER()
	{
		ReadFile();
		unsigned short int numbernig = 1;
		if (start == NULL)
		{
			cout << "No Retailer Data to Show\n\n";
		}
		else
		{
			current = start;
	
			cout << "    " << "Name      |      " << "ID     |      " << "Laptop     |     " << "Amount   |      " << "Mobile     |      " << "Amount     |     " << "Investment\n";
			cout << "______________|_____________|_________________|______________|_________________|_________________|_________________\n";
			while (current != NULL)
			{
				cout <<numbernig<< ".  " << current->RetailerName<< "          "<<current->RetailerID << "           " << current->LaptopModle << "                 " << current->LaptopAmount;
				cout << "                " << current->MobileModle << "               " << current->MobileAmount;
				cout << "                " << current->Investment << endl<<endl;
				cout << "______________|_____________|_________________|______________|_________________|_________________|_________________\n";

				current = current->Nptr;
				numbernig++;
			}
		}
	}
	
	
	void ModifyRetailerData()
	{	ManufecturOrder obj;
		cout<<"EXISTING PRODUCTS RECORD LIST:-"<<endl<<endl;
		obj.RetailerDataTRAVER();
		ofstream write2;
		found = false;
		cout << "\nEnter the Retailer ID you want to Modify: ";
		cin >> keyID;
		read.open("RetailerData.txt", ios::app);
		write2.open("RetailerData2.txt", ios::app);
		while (read >> rn >> ri >> mm >> ma >> lm >> la >> Invest)
		{
			if (ri == keyID)
			{	
				show_available_items();
				Invest = 0;
				found = true;
				cout << "\nEnter the New Retailer Name: ";
				cin >> rn;
				write2 << rn << " \t\t";
				cout << "Enter the New Retailer ID: ";
				cin >> ri;
				write2 << ri << " \t\t";
				cout << "Enter the New Mobile Model: ";
				cin >> mm;
				cout << "Enter the New Mobile Amount: ";
				cin >> ma;
				Invest += MobilePrices(mm, ma);
				if (correctinput == true)
				{
					write2 << mm << " \t\t" << ma << " \t\t";
				}
				else
				{
					mm = "NIL";
					ma = 0;
					write2 << mm << " \t\t" << ma << " \t\t";
				}
				cout << "\nEnter the New Laptop Model: ";
				cin >> lm;
				cout << "Enter the New Laptop Amount: ";
				cin >> la;
				Invest += LaptopPrices(lm, la);
				if (correctinput == true)
				{
					write2 << lm << " \t\t" << la << " \t\t";
				}
				else
				{
					lm = "NIL";
					la = 0;
					write2 << lm << " \t\t" << la << " \t\t";
				}
				write2 << Invest << endl;
			}
			else
			{
				write2 << rn << " \t\t";
				write2 << ri << " \t\t";
				write2 << mm << " \t\t" << ma << " \t\t";
				write2 << lm << " \t\t" << la << " \t\t";
				write2 << Invest << endl;
			}
		}
		write2.close();
		if (found == false)
		{
			cout << "Reatailer ID is INVALID\n\n";
		}
		read.close();
		remove("RetailerData.txt");
		rename("RetailerData2.txt", "RetailerData.txt");
		ReadFile();

	}
	
	void show_record_ids()
	{
		ReadFile();
	
		if (start == NULL)
		{
			cout << "THERE IS NO RECORD EXIST...\n\n";
		}
		else
		{
			current = start;
	
			cout<<"THE IDs THAT ARE AVAILABLE TO SEARCH"<<endl;		
			while (current != NULL)
			{
					
				cout <<current->RetailerID <<"  ";
				
				current = current->Nptr;
				
			}
		}
	}

};


