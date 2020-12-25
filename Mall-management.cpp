#include<iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>
using namespace std;
class shop
{
	int No;
	char Shopname[20];
	char OwnerName[20];
	int EBbill;
	int WaterBill;
	int Rent;
	public:
		void sgetData()
		{
			cout<<"\nShop No : ";
			cin>>No;
			cout<<"\nShop name : ";
			cin>>Shopname;
			cout<<"\nOwner Name : ";
			cin>>OwnerName;
			cout<<"\nEB bill : ";
			cin>>EBbill;
			cout<<"\nWater Bill : ";
			cin>>WaterBill;
			cout<<"\nRent : ";
			cin>>Rent;
		}
       void sdisplay()
       {
       	cout<<"\nTHE SHOP NUMBER: "<<No;
       	cout<<"\n THE SHOP NAME: "<<Shopname;
       	cout<<"\n THE SHOP OWNER NAME: "<<OwnerName;
       	cout<<"\n THE EB-BILL RATE: "<<EBbill;
       	cout<<"\n THE WATER BILL RATE: "<<WaterBill;
       	cout<<"\n THE RENT RATE : "<<Rent<<"\n\n";
       	cout<<"\n---------------------------------------";
	   }
        char *getm()
        {
            return Shopname;
        }
        int num()
        {
            return No;
        }
        int rent()
        {
            return Rent;
        }
        void calcTotalRent(shop s[],int n)
        {
        	int i=0,TotRent=0;
        	for(i=0;i<n;i++)
        	{
        		TotRent=TotRent+s[i].Rent;
			}
			
			cout<<"\n\nTHE TOTAL RENT OF ALL THE SHOPS:"<<TotRent;
		}
		
		void findShopDetails(shop s[],int n)
		{
			int i=0,flag=0;
			string sname;
			char c='y';
			while(c=='y'||c=='Y')
			{
			 cout<<"\n\n ENTER THE SHOP NAME:";
			 cin>>sname;
			 for(i=0;i<n;i++)
			 {
				if(sname==s[i].Shopname)
				{
					s[i].sdisplay();
					flag=flag+1;
				}
			 } 
			
			 if(flag==0)
			 {
				cout<<"\n\n THE SHOP DETAILS NOT FOUND:";
			 }
			 cout<<"\n\n CONTINUE SEARCH(y/n):";
			 cin>>c;
		    }
		}
		
		void NoofFreeShops(shop s[],int n)
		{
			int i=0,flag=0,flag1=0;
			for(i=0;i<n;i++)
			{
				if(!strcmp(s[i].Shopname,"NULL"))
				{
					flag++;
					if(flag1=0)
					{
						cout<<"\n[[[[<<<< THE EMPTY SHOPS ARE >>>>]]]]\n\n ";
						flag1++;
					}
					cout<<"\nTHE SHOP NUMBER IS:"<<s[i].No;
				}
			}
			
			if(flag==0)
			{
				cout<<"\n\n[[[[<<<<NO SHOPS ARE EMPTY>>>>]]]] ";
			}
		}
}obj1;
int main()
{
    int option;
    shop e;
    shop b[50];
    fstream fil;
    int income,Num;
    while(1)
    {
        cout<<"\n--------------------------------------------------------------------------------------------------------";
        cout<<"\n\t\tSHOP DETAILS";
        cout<<"\n--------------------------------------------------------------------------------------------------------";
        cout<<"\n\t1.ADD NEW SHOP DETAILS\n\t2.DISPLAY AVAILABLE SHOPS\n\t3.DELETE A SHOP\n\t4.UPDATE A SHOP\n\t5.TOTAL RENT OF SHOPS\n\t6.SEARCH A SHOP DETAILs\n\t7.AVAILABLE FREE SHOPS \n\t8.EXIT";
        cout<<"\n--------------------------------------------------------------------------------------------------------";
        cout<<"\nEnter your option.....";
        cin>>option;
        switch(option)
        {
            case 1:
              {

                      fstream f;
                      f.open("s.dat",ios::app|ios::binary);
                      e.sgetData();
                      income=income+e.rent();
                      f.write( (char*)&e, sizeof(shop) );
                      f.close();
                      break;

              }
            case 2:
            {
                ifstream infile("s.dat",ios::in|ios::binary);
                if(!infile)
                {
                    cout<<"\nFile cannot be opened";
                    return 1;
                }
                cout<<"\n\t\t\t\t\tShop details....\n";
                int i=0;
                while(infile)
                {
                    infile.read((char*)&b[i],sizeof(shop));
                    if(infile)
                    b[i].sdisplay();
                    i++;
                }
                Num=i;
                infile.close();
                break;
            }
            case 3:
            {
                fstream a;
                int b;
                ofstream c("s1.dat",ios::out|ios::app);
                a.open("s.dat",ios::in|ios::out);
                cout<<"\n\n\t\tID OF THE SHOP YOU WANT TO DELETE : ";
                cin>>b;
                a.seekg(0,ios::beg);
                while(a.read((char*)&obj1,sizeof(obj1)))
                {
                    if(obj1.num()!=b)
                    {
                        c.write((char*)&obj1,sizeof(obj1));
                    }
                }
                a.close();
                c.close();
                remove("s.dat");
                rename("s1.dat","s.dat");
                break;
            }
            case 4:
                {
                    char m[100];
                    cout<<"Enter Name that should be searched:";
                    cin>>m;
                    fil.open("s.dat",ios::in| ios::out|ios::binary);
                    if(!fil)
                    {
                        cout<<"File not Found";
                        exit(0);
                    }
                    else
                    {
                        fil.read((char*)&obj1, sizeof(obj1));
                        while(!fil.eof())
                        {
                            if(strcmp(m,obj1.getm())==0)
                            {
                                fil.seekg(0,ios::cur);
                                cout<<"Enter New Record.."<<endl;
                                obj1.sgetData();
                                fil.seekp(fil.tellg() - sizeof(obj1));
                            }
                            fil.read((char*)&obj1, sizeof(obj1));
                        }
                    }
                    fil.close();
                    break;
                }
            case 5:obj1.calcTotalRent(b,Num-1);break;    
            case 6:obj1.findShopDetails(b,Num);break;
            case 7:obj1.NoofFreeShops(b,Num);break;
			case 8:
                exit(0);
            default:
                {
                    cout<<"\nEnter correct option....";
                    break;
                }
        }
    }return 0;
    }
