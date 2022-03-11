#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <fstream.h>
#include <stdlib.h>
#include <io.h>
#include <iomanip.h>

class student
{ // io.h: used for "rename" and "remove" keywords
protected:
    char name[100];
    int age, rollno;
    float pmarks, mmarks, cmarks, csmarks, emarks, marks;

public:
    void in()
    {
        cout << "\n\t\tENTER THE FOLLOWING INFORMATION: \n"
             << endl;
        cout << "Enter Roll Number: ";
        cin >> rollno;
        cout << "Enter Student Name: ";
        gets(name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Physics Marks Out Of 100: ";
        cin >> pmarks;
        cout << "Enter Maths Marks Out Of 100: ";
        cin >> mmarks;
        cout << "Enter Chemistry Marks Out Of 100: ";
        cin >> cmarks;
        cout << "Enter Computer Science Marks Out Of 100: ";
        cin >> csmarks;
        cout << "Enter English Marks Out Of 100: ";
        cin >> emarks;
    }
    void process()
    {
        marks = (pmarks + mmarks + cmarks + csmarks + emarks) / 5;
    }
    void display()
    {
        cout << "Roll Number: " << rollno << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Physics Marks: " << pmarks << endl;
        cout << "Maths Marks: " << mmarks << endl;
        cout << "Chemistry Marks: " << cmarks << endl;
        cout << "Computer Science Marks: " << csmarks << endl;
        cout << "English Marks: " << emarks << endl;
        cout << "Aggregate Marks: " << marks << endl
             << endl;
    }
    void showtab()
    {
        cout << rollno << '\t' << name << '\t' << age << '\t' << pmarks << '\t' << mmarks << '\t' << cmarks << '\t' << csmarks << '\t' << emarks << '\t' << setprecision(3) << marks << endl
             << endl;
    }
    int ret_roll()
    {
        return rollno;
    }
};
//***************************************************************************
// SYNTAX FOR WRITING A FILE IN FILE HANDLING
//***************************************************************************
void write()
{
    clrscr(); // ios::binary used for ios::in ie reading of file
    char ans;
    student s1; // ios::app (append) used for ios::out ie writing of file
    ofstream a;
    a.open("student1.dat", ios::app | ios::binary);
    ans = 'y';
    do
    {
        s1.in();
        s1.process();
        a.write((char *)&s1, sizeof(s1));
        cout << "\nstudent record has been created...";
        cout << "\nDo you want to enter more records?(Y/N)\n";
        cin >> ans;
    } while (ans == 'Y' || ans == 'y');
    a.close();
    getch();
}
//***************************************************************************
// SYNTAX FOR READING A FILE IN FILE HANDLING
//***************************************************************************
void read()
{
    clrscr();
    student s1;
    ifstream a;
    a.open("student1.dat", ios::binary);
    cout << "\n\t\t\tSTUDENT RECORDS\n\n";
    while (a.read((char *)&s1, sizeof(s1)))
    {
        s1.process();
        s1.display();
    }
    a.close();
    getch();
}
//****************************************************************************
void show_tab()
{
    clrscr();
    student s1;
    ifstream a;
    a.open("student1.dat", ios::binary);
    cout << "\n\t\t\tSTUDENTS RECORD CARD\n\n";
    cout << "===========================================================================" << endl;
    cout << "RollNo.\t"
         << "Name\t"
         << "Age\t"
         << "P\t"
         << "M\t"
         << "C\t"
         << "CS\t"
         << "E\t"
         << "Percentage" << endl;
    cout << "===========================================================================" << endl;
    while (a.read((char *)&s1, sizeof(s1)))
    {
        s1.process();
        s1.showtab();
    }
    a.close();
    getch();
}
//***************************************************************************
void read1()
{
    int rollnew;
    clrscr();
    student s1;
    ifstream a;
    a.open("student1.dat", ios::binary);
    cout << "\n\t\t\tSTUDENT RECORD\n\n";
    cout << "Enter Roll Number To Show Record: ";
    cin >> rollnew;
    cout << endl;
    while (a.read((char *)&s1, sizeof(s1)))
    {
        if (rollnew == s1.ret_roll())
        {
            s1.process();
            s1.display();
        }
    }
    a.close();
    getch();
}
//***************************************************************************
// SYNTAX FOR MODIFYING A FILE IN FILE HANDLING
//***************************************************************************
void modify()
{
    clrscr();
    int rollnew, i;
    student s;
    cout << "\nenter roll number to modify record: ";
    cin >> rollnew;
    ofstream x;
    ifstream y;
    x.open("temp1.dat", ios::binary);    // humne ek temporary file banayi aur
    y.open("student1.dat", ios::binary); // modified record usme save kar liya
    i = 0;
    while (y.read((char *)&s, sizeof(s)))
    {
        if (rollnew == s.ret_roll())
        {
            cout << "Enter new values: " << endl;
            s.in();
            s.process();
            ++i;
        }
        x.write((char *)&s, sizeof(s));
    }
    x.close();
    y.close();
    remove("student1.dat");              // fir humne original file ko delete kar
    rename("temp1.dat", "student1.dat"); // diya aur temp wali ko rename kar ke
    if (i == 0)                          // original wali bana diya
    {
        cout << "Failed to modify record...";
    }
    else
    {
        cout << "record modified.....";
    }
}
//***************************************************************************
// SYNTAX FOR DELETING A FILE IN FILE HANDLING
//***************************************************************************
void delete_()
{
    clrscr();
    int rollnew, i;
    student s;
    cout << "\nenter roll number to delete record: ";
    cin >> rollnew;
    ofstream x;
    ifstream y;
    x.open("temp1.dat", ios::binary);
    y.open("student1.dat", ios::binary);
    i = 0;
    while (y.read((char *)&s, sizeof(s)))
    {
        if (rollnew != s.ret_roll()) // humne temp file main saare records save
        {                            // kar liya except jiska delete karna tha
            x.write((char *)&s, sizeof(s));
            ++i;
        }
    }          // fir temp file ko rename karke original
    x.close(); // file bna diya
    y.close();
    if (i != 0)
    {
        cout << "Record deleted...";
    }
    else
    {
        cout << "Failed to delete record...";
    }
    remove("student1.dat");
    rename("temp1.dat", "student1.dat");
}
//***************************************************************************
// MAIN MENU
//***************************************************************************
void result_menu()
{
    int ch;
    clrscr();
    cout << "\n\t\t\t\tDISPLAY RESULT MENU\n";
    cout << "\t\t\t\t*******************\n\n";
    cout << "\t\t\t1." << '\t' << "Show All Student Records" << endl;
    cout << "\t\t\t2." << '\t' << "Show Student Record Card" << endl;
    cout << "\t\t\t3." << '\t' << "Show Specific Student's Record" << endl;
    cout << "\t\t\t4." << '\t' << "Main Menu" << endl
         << endl
         << endl;
    cout << "\t\t\tEnter Your Choice: ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        read();
        break;
    case 2:
        show_tab();
        break;
    case 3:
        read1();
        break;
    case 4:
        break;
    default:
        cout << endl
             << "Wrong Choice Entered......" << endl
             << "Please Try Again";
        break;
    }
}
//***************************************************************************
void edit_menu()
{
    int ch;
    clrscr();
    cout << "\n\t\t\t\tENTRY / EDIT MENU\n";
    cout << "\t\t\t\t*****************\n\n";
    cout << "\t\t\t1." << '\t' << "Enter Student Record" << endl;
    cout << "\t\t\t2." << '\t' << "Show Specific Student's Record" << endl;
    cout << "\t\t\t3." << '\t' << "Modify Record" << endl;
    cout << "\t\t\t4." << '\t' << "Delete Record" << endl;
    cout << "\t\t\t5." << '\t' << "Main Menu" << endl
         << endl
         << endl;
    cout << "\t\t\tEnter Your Choice: ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        write();
        break;
    case 2:
        read1();
        break;
    case 3:
        modify();
        break;
    case 4:
        delete_();
        break;
    case 5:
        break;
    default:
        cout << endl
             << "Wrong Choice Entered......" << endl
             << "Please Try Again";
        break;
    }
}
//**************************************************************************
/*int main()
{
 int ch;
 do
 {
 clrscr();
 cout<<"\n\t\t\t\tOPTIONS\n";
 cout<<"\t\t\t\t*******\n\n";
 cout<<"\t\t\t1."<<'\t'<<"Enter Student Record"<<endl;
 cout<<"\t\t\t2."<<'\t'<<"Show All Student Records"<<endl;
 cout<<"\t\t\t3."<<'\t'<<"Show Student Record Card"<<endl;
 cout<<"\t\t\t4."<<'\t'<<"Show Specific Student's Record"<<endl;
 cout<<"\t\t\t5."<<'\t'<<"Modify Record"<<endl;
 cout<<"\t\t\t6."<<'\t'<<"Delete Record"<<endl;
 cout<<"\t\t\t7."<<'\t'<<"Exit"<<endl<<endl<<endl;
 cout<<"\t\t\tEnter Your Choice: ";
 cin>>ch;
 switch(ch)
 {
  case 1:  write();    break;
  case 2:  read();     break;
  case 3:  show_tab(); break;
  case 4:  read1();    break;
  case 5:  modify();   break;
  case 6:  delete_();  break;
  case 7:              break;
  default: cout<<endl<<"Wrong Choice Entered......"<<endl<<"Please Try Again"; break;
 }
 }
 while(ch!=7);
 return 0;
}*/
//***************************************************************************
int main()
{
    int ch;
    do
    {
        clrscr();
        cout << "\n\t\t\t\tOPTIONS\n";
        cout << "\t\t\t\t*******\n\n";
        cout << "\t\t\t1." << '\t' << "Entry / Edit Menu" << endl;
        cout << "\t\t\t2." << '\t' << "Display Results Menu" << endl;
        cout << "\t\t\t3." << '\t' << "Exit" << endl
             << endl
             << endl;
        cout << "\t\t\tEnter Your Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            edit_menu();
            break;
        case 2:
            result_menu();
            break;
        case 3:
            break;
        default:
            cout << endl
                 << "Wrong Choice Entered......" << endl
                 << "Please Try Again";
            break;
        }
    } while (ch != 3);
    return 0;
}