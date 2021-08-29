#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <iomanip>
using namespace std;
class owner
{
public:
    int days, interval;
    void adminlogin();
    void addStock();
    void listStock();
    void BillStock();
    void ModifyRate();
    int search();
    void addstock1();
    void inspect();
};
class manager
{
public:
    int days, interval;
    void managerslogin();
    void listStock1();
    int search();
    void borrow();
    void give();
};
struct Stock
{
    char Book_Name[100];
    char Book_Author[100];
    float Rate;
    float Book_stock;
    char unit[10];
    char copy_Bookname[10];
    char name[29];
    int bstock = 0;
    int days;
    float Bill;
} newitem, olditem, copyitem, copy2;
float nstock;
void owner ::addStock()
{
    FILE *fp;
    int i, choice;
    fp = fopen("stock.txt", "rb+");

    if (fp == nullptr)
    {
        cout << "File cannot be opened" << endl;
        return;
    }

    fflush(stdin);
    cout << " Enter Name of the Book: ";
    cin.getline(newitem.Book_Name, 100);

    int found = 0;
    float temp;
    fflush(stdin);
    while (fread(&olditem, sizeof(olditem), 1, fp) == 1)
    {
        if (strcmp(olditem.Book_Name, newitem.Book_Name) == 0)
        {
            found = 1;
            printf(" Current stock is %.2f %s", olditem.Book_stock,
                   olditem.unit);
            cout << "\n Enter new stock to be added : ";
            fflush(stdin);
            cin >> temp;
            olditem.Book_stock = olditem.Book_stock + temp;
            printf(" New stock is %.2f %s", olditem.Book_stock, olditem.unit);

            fseek(fp, -(long int)sizeof(olditem), SEEK_CUR);
            fwrite(&olditem, sizeof(olditem), 1, fp);
            break;
        }
    }

    if (found == 0)
    {
        cout << " Enter Rate : ";
        cin >> newitem.Rate;
        cout << " Enter Current stock: ";
        cin >> newitem.Book_stock;
        cout << " Enter Name of the author  : ";
        fflush(stdin);
        gets(newitem.Book_Author);
        fwrite(&newitem, (long int)sizeof(newitem), 1, fp);
    }
    fclose(fp);
    fflush(stdin);
    return;
}
void owner::addstock1()
{
    FILE *fa;
    fa = fopen("borrow.txt", "rb+");
    if (fa == nullptr)
    {
        cout << "File opening error!" << endl;
        return;
    }
    fflush(stdin);
    int i, choice;
    fflush(stdin);
    cout << " Enter Name of the Book: ";
    cin.getline(newitem.Book_Name, 100);

    int found = 0;
    float temp;
    fflush(stdin);
    while (fread(&copyitem, sizeof(copyitem), 1, fa) == 1)
    {
        if (strcmp(copyitem.Book_Name, newitem.Book_Name) == 0)
        {
            found = 1;
            printf(" Current stock is %.2f %s", copyitem.Book_stock,
                   copyitem.unit);
            cout << "\n Enter new stock to be added : ";
            fflush(stdin);
            cin >> temp;
            copyitem.Book_stock = copyitem.Book_stock + temp;
            printf(" New stock is %.2f %s", copyitem.Book_stock, copyitem.unit);

            fseek(fa, -(long int)sizeof(copyitem), SEEK_CUR);
            fwrite(&copyitem, sizeof(copyitem), 1, fa);
            break;
        }
    }
    if (found == 0)
    {
        cout << " Enter Rate : ";
        cin >> newitem.Rate;
        cout << " Enter Current stock: ";
        cin >> newitem.Book_stock;
        cout << " Enter Name of the author  : ";
        fflush(stdin);
        gets(newitem.Book_Author);
        fwrite(&newitem, sizeof(newitem), 1, fa);
    }
    fclose(fa);
    fflush(stdin);
    return;
}
//creating function for search
int owner::search()
{
    FILE *fs;
    char choice;
    fs = fopen("stock.txt", "rb+");
    fflush(stdin);
    cout << " Enter Authors name: ";
    cin.getline(newitem.Book_Author, 100);
    cout << " Enter Title of book: ";
    cin.getline(newitem.Book_Name, 100);

    int found = 0;

    while (fread(&olditem, sizeof(olditem), 1, fs) == 1)
    {
        if ((strcmpi(olditem.Book_Author, newitem.Book_Author) == 0) && (strcmpi(olditem.Book_Name, newitem.Book_Name) == 0))
        {
            found = 1;
            cout << "\n*Your Book Has Found*\n ";
            for (int i = 0; i < 98; i++)
            {
                printf("-");
            }
            cout << endl
                 << setw(30) << left << "Book Name" << setw(30) << left << "Author" << setw(30) << left << "Stock" << setw(30) << left << "Rate" << endl;

            cout << "\n"
                 << setw(30) << left << olditem.Book_Name << setw(30) << left << olditem.Book_Author
                 << setw(30) << left << olditem.Book_stock << setw(30) << left << olditem.Rate << setw(30) << left << endl;
            for (int i = 0; i < 98; i++)
            {
                printf("-");
            }
            fflush(stdin);
        }
    }
    if (found = 0)
    {
        cout << "\n\tSorry book has not found" << endl;
    }

    fclose(fs);

    return (found);
}
void owner ::listStock()
{
    FILE *fp;
    int i, choice;
    float total_amount = 0;
    fp = fopen("stock.txt", "rb+");
    cout << endl
         << endl
         << setw(30) << left << "Book Name" << setw(30) << left << "Author" << setw(30) << left << "Stock" << setw(30) << left << "Rate" << setw(30) << left << "Amount" << endl;

    for (i = 0; i < 150; i++)
    {
        printf("-");
    }

    system("Color 70");
    cout << endl
         << endl;
    while (fread(&olditem, sizeof(olditem), 1, fp) == 1)
    {

        cout << setw(30) << left << olditem.Book_Name << setw(30) << left << olditem.Book_Author
             << setw(30) << left << olditem.Book_stock << setw(30) << left << olditem.Rate << setw(30) << left << olditem.Rate * olditem.Book_stock << "\n";

        total_amount = total_amount + (olditem.Rate * olditem.Book_stock);
    }

    system("Color 70");
    for (i = 0; i < 150; i++)
        printf("-");
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tThe total amount :" << total_amount;
    fclose(fp);
    fflush(stdin);
    return;
}
// creating function for billing by manager
void owner ::BillStock()
{
    FILE *fp;
    int i;
    float buy, Bill = 0;
    char name[60], choice = 'Y';
    fp = fopen("stock.txt", "rb+");
    if (fp == nullptr)
    {
        cout << "file cannot be opened" << endl;
    }
    fflush(stdin);
    cout << " Enter the name of the customer : ";
    gets(name);
    fclose(fp);
    listStock();
    while (choice == 'Y' || choice == 'y')
    {
        fp = fopen("stock.txt", "rb+");
        if (fp == nullptr)
        {
            cout << "File cannot be opened" << endl;
            return;
        }
        fflush(stdin);
        cout << "\n Which Book do " << name << " want to buy ? : ";
        cin.getline(newitem.Book_Name, 100);
        int found = 0;
        while (fread(&olditem, sizeof(olditem), 1, fp) == 1)
        {
            if (strcmp(olditem.Book_Name, newitem.Book_Name) == 0)
            {
                found = 1;
                cout << " Current stock is " << olditem.Book_stock;
                cout << "\n Rate is : Rs. " << olditem.Rate ;
                cout << "\n Enter quantity of books customer wants : ";
                fflush(stdin);
                cin >> buy;
                if (olditem.Book_stock != 0 && ((olditem.Book_stock - buy) >= 0))
                {
                    Bill = Bill + (olditem.Rate * buy);
                    olditem.Book_stock = olditem.Book_stock - buy;
                    fseek(fp, -(long int)sizeof(olditem), SEEK_CUR);
                    fwrite(&olditem, sizeof(olditem), 1, fp);
                    break;
                }
                else if (olditem.Book_stock == 0 || (olditem.Book_stock - buy) < 0)
                {
                    Bill = Bill;
                    cout << " Sorry this book is not in stock or Book stock inefficient to provide your order" << endl;

                    olditem.Book_stock = olditem.Book_stock;
                    fseek(fp, -(long int)sizeof(olditem), SEEK_CUR);
                    fwrite(&olditem, sizeof(olditem), 1, fp);
                    break;
                }
            }
        }
        if (found == 0)
        {
            cout << " Sorry! " << newitem.Book_Name << " is not available in our store\n";
        }
        fflush(stdin);
        cout << " Do you want any other Book ? (Y/N) :";
        cin >> choice;
        fclose(fp);
    }
    cout << "  " << name;
    printf("  Your Bill is Rs %.2f ", Bill);
    // cout << endl;
    fflush(stdin);
    return;
}
// creating function to modify rate
void owner ::ModifyRate()
{
    FILE *fp;
    int i, choice;
    fp = fopen("stock.txt", "rb+");
    if (fp == nullptr)
    {
        cout << "File cannot be opened" << endl;
        return;
    }
    fflush(stdin);
    cout << " Enter Name of the Book : ";
    cin.getline(newitem.Book_Name, 100);
    int found = 0;
    while (fread(&olditem, sizeof(olditem), 1, fp) == 1)
    {
        if (strcmp(olditem.Book_Name, newitem.Book_Name) == 0)
        {
            found = 1;
            printf(" Current Rate is %.2f ", olditem.Rate);

            cout << "\n Enter new rate : ";
            fflush(stdin);
            cin >> olditem.Rate;
            fseek(fp, -(long int)sizeof(olditem), SEEK_CUR);
            fwrite(&olditem, sizeof(olditem), 1, fp);
            cout << " New Rate is updated successfully";
            break;
        }
    }
    if (found == 0)
    {
        cout << " Sorry !" << newitem.Book_Name << " is not available in our store\n";
    }
    fclose(fp);
    fflush(stdin);
    return;
}
void owner::inspect()
{
    FILE *fi;
    int i, choice;
    float total_charges = 0;
    fi = fopen("inspect.txt", "rb+");
    if (fi == nullptr)
    {
        cout << "File cannot be opened" << endl;
        return;
    }
    cout << endl
         << endl
         << setw(30) << left << "Book Name" << setw(30) << left << "Borrower Name" << setw(30) << left << "Books Borrowed";
    cout << endl;
    for (i = 0; i < 150; i++)
    {
        printf("-");
    }
    system("Color 70");
    cout << endl
         << endl;
    while (fread(&copy2, sizeof(copy2), 1, fi) == 1)
    {

        cout << setw(30) << left << copy2.Book_Name << setw(30) << left << copy2.name
             << setw(30) << left << copy2.bstock<< "\n";
        //              _stock << "\n";
        // << copyitem. * copyitem.Book
        total_charges = total_charges + (copy2.Bill);
    }

    system("Color 70");
    for (i = 0; i < 150; i++)
        printf("-");
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\tThe total amount :" << total_charges;
    fclose(fi);
    fflush(stdin);
    return;
}
void manager::listStock1()
{
    FILE *fp;
    int i, choice;
    float total_amount = 0;
    fp = fopen("borrow.txt", "rb+");
    if (fp == nullptr)
    {
        cout << "File cannot be opened" << endl;
        return;
    }
    cout << endl
         << endl
         << setw(30) << left << "Book Name" << setw(30) << left << "Author" << setw(30) << left << "Stock" << setw(30) << left << "Rate" << setw(30) << left << "Amount" << endl;

    for (i = 0; i < 150; i++)
    {
        printf("-");
    }

    system("Color 70");
    cout << endl
         << endl;
    while (fread(&copyitem, sizeof(copyitem), 1, fp) == 1)
    {

        cout << setw(30) << left << copyitem.Book_Name << setw(30) << left << copyitem.Book_Author
             << setw(30) << left << copyitem.Book_stock << setw(30) << left << copyitem.Rate << setw(30) << left << copyitem.Rate * copyitem.Book_stock << "\n";

        total_amount = total_amount + (copyitem.Rate * copyitem.Book_stock);
    }

    system("Color 70");
    for (i = 0; i < 150; i++)
        printf("-");
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tThe total amount :" << total_amount;
    fclose(fp);
    fflush(stdin);
    return;
}
void manager::give()
{
    FILE *fr;
    char name[20];
    fr = fopen("inspect.txt", "rb+");
    if (fr == nullptr)
    {
        cout << "File cannot be opened" << endl;
        return;
    }
    fflush(stdin);
    cout << "Enter the name of customer : ";
    cin.getline(newitem.name, 19);
    cout << "Enter the book to be returned: ";
    cin.getline(newitem.Book_Name, 100);
    int found = 0;

    while (fread(&copy2, sizeof(copy2), 1, fr) == 1)
    {
        if ((strcmp(copy2.name, newitem.name) == 0) && (strcmp(copy2.Book_Name, newitem.Book_Name) == 0))
        {
            found = 1;
            cout << "\n*Your Book Has Found*\n ";
            for (int i = 0; i < 90; i++)
            {
                printf("-");
            }
            cout << endl
                 << setw(30) << left << "Book Name" << setw(30) << left << "Name" << setw(30) << left << "Stock" << endl;

            cout << "\n"
                 << setw(30) << left << copy2.Book_Name << setw(30) << left << copy2.name
                 << setw(30) << left << copy2.bstock << endl;
            for (int i = 0; i < 90; i++)
            {
                printf("-");
            }
            fflush(stdin);
        }
    }
    if (found = 0)
    {
        cout << "\n\tSorry book has not found " << endl;
    }
    int st;
    cout << "\nEnter no of quantities of books to be returned : ";
    cin >> st;
    copy2.bstock = copy2.bstock - st;
    fseek(fr, -(long int)sizeof(copy2), SEEK_CUR);
    fwrite(&copy2, sizeof(copy2), 1, fr);
    cout << "The book Returned successfully" << endl;
    fclose(fr);
}
// creating managerslogin function for manager
void manager ::managerslogin()
{
    fflush(stdin);
    owner o;
    manager m; //creating object for manager
    int a = 0;
    string userName;
    char userPassword[] = "secret";
    int Attempt = 0;

    while (Attempt < 5)
    {
        cout << " Please enter your user name: ";
        cin >> userName;
        cout << " Please enter your user password: ";
        char copy_userpasswords[10];
        while (copy_userpasswords[a - 1] != '\r')
        {
            copy_userpasswords[a] = getch();
            if (copy_userpasswords[a - 1] != '\r')
            {
                cout << "*";
            }
            a++;
        }
        copy_userpasswords[a - 1] = '\0';
        if (userName == "Manager" && (strcmp(copy_userpasswords, userPassword) == 0))
        {
            cout << "\n Welcome successfully logged in !\n";
            char choice1;
            printf("\n\t\t------WELCOME TO THE BOOK SHOP------\n");
            while (1)
            {
                cout << "\n L : List of Stock";
                cout << "\n B : Billing";
                cout << "\n S : Search";
                cout << "\n K : Borrow Books list";
                cout << "\n T : Lend";
                cout << "\n G : Return";
                cout << "\n I : Inspect";
                cout << "\n E : Exit\n";
                cout << " Enter Your Choice : ";
                fflush(stdin);
                choice1 = getchar();
                switch (choice1)
                {
                case 'L':
                    o.listStock();
                    break;
                case 'B':
                    o.BillStock();
                    break;
                case 'S':
                    o.search();
                    break;
                case 'K':
                    m.listStock1();
                    break;
                case 'T':
                    char choice1;
                    cout << "\t\t---- Terms And Condition ----\n";
                    cout << "\t1.While Borrowing Book you should enter days to be borowed" << endl;
                    cout << "\t2.Do not Damage book at any Cost" << endl;
                    cout << "\t3.Return book in particular time else strictly action will be conducted" << endl;
                    cout << "\t4.If you do not return book then you have to pay some charges" << endl;
                    cout << "\t\t----------------\n";
                    cout << "Enter (Y/y) to continue:";
                    cin >> choice1;
                    if (choice1 == 'Y' || choice1 == 'y')
                    {
                        m.borrow();
                    }
                    else
                    {
                        cout << " We are Sorry\n";
                    }
                    break;
                case 'G':
                    m.give();
                    break;
                case 'I':
                    o.inspect();
                    break;
                case 'E':
                    cout << "\n\tTHANK YOU FOR USING OUR SERVICE";
                    return;
                    break;
                default:
                    choice1 = getchar();
                }
            }
        }
        else
        {
            cout << "\n Invalid login attempt. Please try again.\n"
                 << '\n';
            Attempt++;
        }
    }
    if (Attempt == 5)
    {
        cout << "Too many login attempts .....";
        cout << "Exiting...............";
        Sleep(2000);
        exit(0);
    }
}
void owner ::adminlogin()
{
    fflush(stdin);

    owner o;
    manager m; //creating object for owner
    string userName;
    char userPassword[] = "1234";
    int Attempt = 0;

    while (Attempt < 5)
    {
        cout << " Please enter your user name: ";
        cin >> userName;
        cout << " Please enter your user password: ";
        int a = 0;
        char copy_userpasswords[10];
        while (copy_userpasswords[a - 1] != '\r')
        {
            copy_userpasswords[a] = getch();
            if (copy_userpasswords[a - 1] != '\r')
            {
                cout << "*";
            }
            a++;
        }
        copy_userpasswords[a - 1] = '\0';

        if (userName == "Navneet" && (strcmp(copy_userpasswords, userPassword) == 0))
        {
            cout << "\n Welcome successfully logged in !\n";
            char choice1;
            printf("\n\t\t------WELCOME TO THE BOOK SHOP------\n");

            while (1)
            {
                cout << "\n A : Add or Modify Stock";
                cout << "\n L : List of Stock";
                cout << "\n M : Modify Rate";
                cout << "\n B : Billing";
                cout << "\n Z : Add Borrow";
                cout << "\n S : Search";
                cout << "\n K : Borrow Books list";
                cout << "\n E : Exit\n";
                cout << " Enter Your Choice : ";
                fflush(stdin);
                choice1 = getchar();
                switch (choice1)
                {
                case 'A':
                    o.addStock();
                    break;
                case 'L':
                    o.listStock();
                    break;
                case 'B':
                    o.BillStock();
                    break;
                case 'M':
                    o.ModifyRate();
                    break;
                case 'S':
                    o.search();
                    break;
                case 'Z':
                    o.addstock1();
                    break;
                case 'K':
                    m.listStock1();
                    break;
                case 'E':
                    cout << "\n\tTHANK YOU FOR USING OUR SERVICE";
                    return;
                    break;
                default:
                    choice1 = getchar();
                }
            }
        }
        else
        {
            cout << "\n Invalid login attempt. Please try again.\n"
                 << '\n';
            Attempt++;
        }
    }

    if (Attempt == 5)
    {
        cout << "Too many login attempts .....";
        cout << "Exiting...............";
        Sleep(2000);
        exit(0);
    }
}
void manager::borrow()
{

    int found = 0;
    FILE *fb;
    int i;

    int buy;
    float Bill = 0;
    int days;
    int length2;
    char name2[60];
    char name[60], choice = 'Y';
    fb = fopen("borrow.txt", "rb+");
    if (fb == nullptr)
    {
        cout << "File cannot be opened" << endl;
        return;
    }
    fflush(stdin);
    cout << " Enter the name of the customer : ";
    gets(name);
    fclose(fb);
    listStock1();
    while (choice == 'Y' || choice == 'y')
    {
        fb = fopen("borrow.txt", "rb+");
        if (fb == nullptr)
        {
            cout << "File cannot be opened" << endl;
            return;
        }
        fflush(stdin);
        cout << "\n Which Book do " << name << " want to Borrow : ";
        cin.getline(newitem.Book_Name, 100);

        length2 = sizeof(newitem.Book_Name);

        int found = 0;
        while (fread(&copyitem, sizeof(copyitem), 1, fb) == 1)
        {
            if (strcmp(copyitem.Book_Name, newitem.Book_Name) == 0)
            {
                found = 1;

                cout << "*Your Book Has Found*\n ";
                for (int i = 0; i < 150; i++)
                {
                    printf("-");
                }
                cout << endl
                     << setw(30) << left << "Book Name" << setw(30) << left << "Author" << setw(30) << left << "Stock" << setw(30) << left << "Rate" << endl;
                cout << setw(30) << left << copyitem.Book_Name << setw(30) << left << copyitem.Book_Author
                     << setw(30) << left << copyitem.Book_stock << setw(30) << left << copyitem.Rate << "\n";
                for (int i = 0; i < 150; i++)
                {
                    printf("-");
                }
                fflush(stdin);
                cout << "\n Current stock is  " << copyitem.Book_stock;
                cout << "\n Rate is : Rs.  " << copyitem.Rate << endl;
                fflush(stdin);

                cout << " Enter quantity of books customer wants : ";
                cin >> buy;

                cout << " How many days you want this book : ";
                fflush(stdin);
                cin >> days;
                copy2.days = days;
                if ((days > 3 && copyitem.Book_stock != 0 && (copyitem.Book_stock - buy) >= 0))
                {
                    interval = days - 3;
                    Bill = Bill + (interval * 10);
                    copyitem.Book_stock = copyitem.Book_stock - buy;
                    fseek(fb, -(long int)sizeof(copyitem), SEEK_CUR);
                    fwrite(&copyitem, sizeof(copyitem), 1, fb);
                    for (int i = 0; i < length2; i++)
                    {
                        copy2.Book_Name[i] = newitem.Book_Name[i];
                    }
                    break;
                }
                else if (copyitem.Book_stock == 0 || (copyitem.Book_stock - buy) < 0)
                {
                    fflush(stdin);
                    Bill = Bill;
                    buy = copy2.bstock;
                    cout << " Sorry! " << newitem.Book_Name << " is not available in our store or Book stock is inefficient to provide your order\n";
                    copyitem.Book_stock = copyitem.Book_stock;
                    strcpy(newitem.Book_Name, copy2.copy_Bookname);
                    fseek(fb, -(long int)sizeof(copyitem), SEEK_CUR);
                    fwrite(&copyitem, sizeof(copyitem), 1, fb);

                    break;
                }
                else if (days < 3 && copyitem.Book_stock != 0 && (copyitem.Book_stock - buy) >= 0)
                {
                    Bill = 0;
                    copyitem.Book_stock = copyitem.Book_stock - buy;

                    fseek(fb, -(long int)sizeof(copyitem), SEEK_CUR);
                    fwrite(&copyitem, sizeof(copyitem), 1, fb);
                    for (int i = 0; i < length2; i++)
                    {
                        copy2.Book_Name[i] = newitem.Book_Name[i];
                    }
                    break;
                }
            }
        }

        if (found == 0)
        {
            cout << " Sorry! " << newitem.Book_Name << " is not available in our store \n";
        }

        fflush(stdin);
        choice = 'N';
        fclose(fb);
    }

    cout << name;
    int length = (int)sizeof(name);
    printf(" You have to pay is Rs %.2f  if you did not return book in time", Bill);
    for (int i = 0; i < length; i++)
    {
        copy2.name[i] = name[i];
    }

    copy2.Bill = Bill;

    FILE *fia = nullptr;

    fia = fopen("inspect.txt", "ab");
    if (fia == nullptr)
    {
        cout << "File cannot be opened" << endl;
        return;
    }

    copy2.bstock = buy;

    fwrite(&copy2, sizeof(copy2), 1, fia);

    fclose(fia);
    fflush(stdin);
}
// output function
void output()
{
    owner o;
    manager m;
    FILE *fp;
    int n;
    char choice1;
    fp = fopen("stock.txt", "rb+");
    if (fp == nullptr)
    {
        cout << "File cannot be opened" << endl;
        return;
    }
    int i;
    char choice;
    system("color 75");
    system("cls"); 
    cout << "\n\t\t------WELCOME TO THE BOOK SHOP------";
    cout << "\n\t\t*************************************";
    fflush(stdin);
    while (1)
    {   fflush(stdin);
        cout << "\n A : Owner";
        cout << "\n B : Manager";
        cout << "\n E : Exit";
        cout << "\n Enter Your Choice : ";

        choice = getchar();
        switch (choice)
        {
        case 'A':
            o.adminlogin();
            break;
        case 'B':
            m.managerslogin();
            break;
        case 'E':
            cout << "\n\tTHANK YOU FOR USING OUR SERVICE";
            exit(0);
        }
    }
}
//the main function
int main()
{
    // owner o;
    output();
}