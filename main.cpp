/****************************************HeaderFiles*/

#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cctype>
#include <windows.h>
using namespace std;

/****************************************function prototypes*/

void enter();
void view();
void edit();
void del();
/****************/
void introduction();
void draw(char*);
bool exit();
bool aia(char*);

/****************************************Class definition*/

class pay
{
   public:
      char tit[80],det[400];
         float c;
         int y,m,d;
         pay();
      void getdata();
      void showdata();
};
pay::pay()
{
   c=0;m=0;y=0;d=0;
}
void pay::getdata()
{
   char st[9];
   cout<<"Title: ";
   gets(tit);
   do{
      cout<<"* Cost: ";
      gets(st);
      if(aia(st))
         c=(float)atof(st);
   }while(c>999999||c<-999999||c==0);
   cout<<"Date:   \n";
   do{
      cout<<"      * Year: ";
      gets(st);
      if(aia(st))
         y=(int)atof(st);
   }while(y<00||y>99);
   do{
      cout<<"     * Month: ";
      gets(st);
      if(aia(st))
         m=(int)atof(st);
   }while(m>12||m<1);
   if(m>0&&m<7)
      do{
         cout<<"       * Day: ";
         gets(st);
      if(aia(st))
         d=(int)atof(st);
      }while(d>31||d<1);
   if(m>6&&m<12)
      do{
         cout<<"       * Day: ";
         gets(st);
      if(aia(st))
         d=(int)atof(st);
      }while(d>30||d<1);
   if(m==12&&y%4==3)
      do{
         cout<<"       * Day: ";
         gets(st);
      if(aia(st))
         d=(int)atof(st);
      }while(d>30||d<1);
   if(m==12&&y%4!=3)
      do{
         cout<<"       * Day: ";
         gets(st);
      if(aia(st))
         d=(int)atof(st);
      }while(d>29||d<1);
   cout<<"Det: ";
   gets(det);
}

void pay::showdata()
{
   cout<<"Title: ";
   puts(tit);
   cout<<"Cost: "<<c;
   cout<<"\nDate: "<<y<<" / "<<m<<" / "<<d;
   if(det[0])
   {
      cout<<"\nDetails: ";
      puts(det);
      cout<<endl;
      for(int m=0;m<75;m++)
         cout<<"*";
      return;
   }
   cout<<endl<<endl;
   for(int m=0;m<75;m++)
      cout<<"*";
}

int main()
{

   char ans;
   introduction();
   while(1)
   {
      draw("MENU");
      cout<<"\tChoose item by pressing keys...\n\n";
      cout<<"\n\t\t1)Enter\n\t\t2)View\n\t\t3)Edit\n\t\t4)Delete\n\t\t5)Help\n\t\t6)Exit";
      ans=_getch();
      switch(ans)
      {
         case '1': enter();  break;
         case '2': view();  break;
         case '4': del();  break;
         case '3': edit(); break;
         case '5': introduction(); break;
         case '6': if(exit()) return 0;
      }
   }
}

void enter()
{
   draw("Add new record");
   cout<<"Enter information to create and add a new record.\n\n";
   pay p;
   fstream f;
   f.open("Datafile1.ssa",ios::out|ios::binary|ios::app);
   p.getdata();
   cout<<"\nAre you sur you want to save this as a record? <y>\n";
   if(_getch()!='y')
      return;
   f.write((char*) &p,sizeof(pay));
   f.close();
   cout<<"\nRecord Saved";
   return;
}


void view()
{
   draw("View");
   int i=0,yy,mm;
   float tp=0,tw=0;
   char st[8],ans;
   fstream f;
   pay p;
   f.open("Datafile1.ssa",ios::in|ios::binary);
   cout<<"To view Full List enter 0 below. \n";
   cout<<"Enter year and month to view that records of that month:\n";
   do{
      cout<<"      * Year: ";
      gets(st);
      if(aia(st))
         yy=atoi(st);
   }while(yy<00||yy>99);
   if(yy)
    do{
         cout<<"     * Month: ";
      gets(st);
         if(aia(st))
            mm=atoi(st);
    }while(mm>12||mm<1);
   cout<<"\n\n \tSelect by pressing 1 , 2 or 3:\n\n\t\t1) View all\n\t\t2) View Payments\n\t\t3) View withdrawals";
   ans=_getch();
   if(yy==0)
   {
      draw("Full List");
      switch(ans)
            {
            case'2':

               while(f.read((char*) &p,sizeof(pay)))
               {
                  if(p.d)
                  {
                  if(p.c>=0)
                  {
                     if(i%2)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                     else
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                     cout<<++i<<":\n";
                     p.showdata();
                     cout<<"\n\n";
                     tp+=p.c;
                  }
                  else
                     tw+=p.c;
                  }
               }
               break;

            case'3':
               while(f.read((char*) &p,sizeof(pay)))
               {
                  if(p.d)
                  {
                  if(p.c<0)
                  {
                      if(i%2)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                     else
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                     cout<<++i<<":\n";
                     p.showdata();
                     cout<<"\n\n";
                     tw+=p.c;
                  }
                  else
                     tp+=p.c;
                  }
               }
               break;
            default:
               while(f.read((char*) &p,sizeof(pay)))
               {
                  if(p.d)
                  {
                  if(i%2)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                     else
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                     cout<<++i<<":\n";
                  p.showdata();
                  cout<<"\n\n";
                  if(p.c<0)
                     tw+=p.c;
                  else
                     tp+=p.c;
                  }
               }
            }
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
      switch(ans)
         {
         case '2':
            cout<<"\n\t\tTotal paymnets:    "<<tp;
            break;
         case '3':
            cout<<"\n\t\tTotal withdrawals: "<<(-tw);
            break;
         default:
              cout<<"\n\t\tTotal paymnets:    "<<tp;
            cout<<"\n\t\tTotal withdrawals: "<<(-tw);
         }
      cout<<"\n\t\t-----------------------\n\t\tBallane:      "<<-(tp+tw);
      f.close();
      _getch();
      return;
   }
   draw("Monthly list");
   cout<<"Year: "<<yy<<"\tMonth: "<<mm<<"\n\n";
   if(yy!=0)
   {
      switch(ans)
      {
         case'2':
            while(f.read((char*) &p,sizeof(pay)))
            {
               if(p.d)
               {
               if(p.c>=0&&p.y==yy&&p.m==mm)
               {
                  if(i%2)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                     else
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                     cout<<++i<<":\n";
                  p.showdata();
                  cout<<"\n\n";
                  tp+=p.c;
               }
               else
                  tw+=p.c;
               }
            }
            break;
         case'3':
            while(f.read((char*)&p,sizeof(pay)))
            {
               if(p.d)
               {
               if(p.c<0&&p.y==yy&&p.m==mm)
               {
                  if(i%2)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                     else
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                     cout<<++i<<":\n";
                  p.showdata();
                  cout<<"\n\n";
                  tw+=p.c;
               }
               else
                  tp+=p.c;
               }
            }
            break;
         default:
            while(f.read((char*)&p,sizeof(pay)))
            {
               if(p.d)
               {
               if(p.y==yy&&p.m==mm)
               {
                  if(i%2)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                     else
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                     cout<<++i<<":\n";
                  p.showdata();
                  cout<<"\n\n";
               if(p.c>=0)
                       tp+=p.c;
                  else
                       tw+=p.c;
            }
               }
            }
         }
      }
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
   switch(ans)
   {
   case '2':
      cout<<"\n\t\tTotal paymnets:    "<<tp;
      break;
   case '3':
      cout<<"\n\t\tTotal withdrawals: "<<(-tw);
      break;
   default:
      cout<<"\n\t\tTotal paymnets:    "<<tp;
      cout<<"\n\t\tTotal withdrawals: "<<(-tw);
   }
   cout<<"\n\t\t-----------------------\n\t\tBallane:      "<<-(tp+tw);
   f.close();
   _getch();
   return;
}


void edit()
{
   draw("Edit");
   int n=1,i=0,e=0;
   char st[10];
   pay p;
   fstream f;
   f.open("Datafile1.ssa",ios::in|ios::out|ios::binary);
   cout<<"View the Full List to find out the record no...\n";
   do{
      do{
         cout<<"Enter the record no to edit: ";
         gets(st);
         if(aia(st))
            n=atoi(st);
      }while(n<1);
      while(f.read((char*) &p,sizeof(pay))&&i<n)
      {
         if(p.d==0)
         {
            e++;
            i--;
         }
         i++;
      }
   }while(n>i);
   n=n+e-1;
   f.clear();
   f.seekg(n*sizeof(pay));
   f.read((char*)&p,sizeof(pay));
   draw("Edit");
   p.showdata();
   char ans;
   cout<<"\nAre you sure to edit? <y>";
   ans=_getch();
   if(ans!='y')
      return;
   cout<<"\n\n";
   p.getdata();
   f.clear();
   f.seekp(n*sizeof(pay));
   f.write((char*) &p,sizeof(pay));
   cout<<"\nIs it OK? <y>";
   ans=_getch();
   if(ans!='y')
      return;
   cout<<"\nEditing completed successfully";
   _getch();
   f.close();
}


void del()
{
   char st[8];
   draw("Delete");
   int n,i=0,e=0;
   pay p;
   fstream f;
   f.open("Datafile1.ssa",ios::in|ios::out|ios::binary);
   cout<<"View the Full List to find out the record no...\n";
   do{
      do{
         cout<<"Enter the record no to delete: ";
         gets(st);
         if(aia(st))
            n=atoi(st);
      }while(n<1);
      while(f.read((char*) &p,sizeof(pay))&&i<n)
      {
         if(p.d==0)
         {
            e++;
            i--;
         }
         i++;
      }
   }while(n>i);
   n=n+e-1;
   f.clear();
   f.seekg(n*sizeof(pay));
   f.read((char*)&p,sizeof(pay));
   draw("Delete");
   p.showdata();
   char ans;
   cout<<"\n\nAre you sure to delete? <y>";
   ans=_getch();
   if(ans!='y')
      return;
   p.d=0;
   f.clear();
   f.seekp(n*sizeof(pay));
   f.write((char*) &p,sizeof(pay));
   f.close();
   cout<<"\n\nDeleting completed successfulle";
   _getch();
}

void introduction()
{
   draw("SOROUSH SIMPLE ACCOUNTING 1.0v");
   cout<<char(16);cout<<"  Please, read this note before use:\n\n";
   cout<<char(16);cout<<" It's a very simple accounting program whith primary facilities writen by C++.\n";
   cout<<char(16);cout<<" You can  Enter records , save , edit , delete oand view them.\n";
   cout<<char(16);cout<<" You can enter the month and the year and vie records of that month.\n";
   cout<<char(16);cout<<" To enter a withdrawal record you should enter the cost should be negative.\n";
   cout<<char(16);cout<<" View the Full List to see the records #no to viewing or deleting them.\n";
   cout<<char(16);cout<<" You can't enter numbers bigger than 999999 or smaller than -999999.\n";
   cout<<char(16);cout<<" Enter the years (yy), not(yyyy).\n";
   cout<<char(16);cout<<" The float numbers have only one integer after \".\".\n";
   cout<<char(16);cout<<" You have to fill the fields .\n";
   cout<<char(16);cout<<" Items marked with a * are required unless stated otherwise.\n";
   cout<<char(16);cout<<" If you enter an unacceptable data, It would be asked you again.\n";
   cout<<char(16);cout<<" Whenever you enter a date, it will be checked in persian date mode.\n";
   _getch();
}



void draw(char *st)
{
   system("cls");
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
   int n=strlen(st);
   cout<<"\n\t\t\t";
   puts(st);
   cout<<"\n";
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
   for(int i=0;i<80;i++)
      cout<<char(31);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
   cout<<"\n\n\n\n\n";
}


bool exit()
{
   draw("EXIT");
   cout<<"\tAre you sure to Exit? <y>";
   if(_getch()=='y')
      return 1;
   return 0;
}

bool aia(char *st)
{
   int i=0;
   while(st[i])
   {
      if((st[i]>57||(st[i]<48&&st[i]!=46))&&st[i]!='-')
         return 0;
      i++;
   }
   if(i>9)
      return 0;
   return 1;
}
