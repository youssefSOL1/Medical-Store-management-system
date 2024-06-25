#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#define el '\n'
#define tab '\t'
using namespace std;
char proceed;
int Nbcustomers = 1, Nbsuppliers = 1;
string validphone();
struct customer_details
{
    //year month and day for last bill
    bool empty = true;
    double year, month, day, last_value = 0, sum_purchased = 0;
    string ID, name, phone;
    int purchased_products[100] = {}, productid[100] = {};
}customers[100], tempcus[100];

// the next struct for supplier_products_details
struct product_details
{
    //each supply's quantity and expiry date
    bool empty = true;
    int month, year;
    string id, name, supplies[100] = {};
    int nexti = 0;
    //to check where to put the supplier name
    double  price;
    int stock = 0, stock_last = 0;
}products[100];

struct supplier_details
{
    bool empty = true;
    string ID, name, phone;
    int  med_prod[100];
    //string for med supplies quantity and id and expiry date
}suppliers[100];

struct Last_report
{
    int day = 1, month = 1, year = 1;
}Report, temprep;

void initiliaze() {
    products[1].empty = false;
    products[1].name = "Panadol";
    products[1].month = 12;
    products[1].year = 2025;
    products[1].price = 40;
    products[1].stock = 10;
    products[1].stock_last = 10;
    products[2].empty = false;
    products[2].name = "Congestal";
    products[2].month = 2;
    products[2].year = 2025;
    products[2].price = 35;
    products[2].stock = 4;
    products[2].stock_last = 4;
    products[3].empty = false;
    products[3].name = "Zinc";
    products[3].month = 7;
    products[3].year = 2029;
    products[3].price = 20;
    products[3].stock = 2;
    products[3].stock_last = 2;
    products[4].empty = false;
    products[4].name = "omega3";
    products[4].month = 7;
    products[4].year = 2024;
    products[4].price = 35;
    products[4].stock = 20;
    products[4].stock_last = 10;
}

void Add_new_customer(int CID) {
    cout << el << "------------------------------------" << el << el;
    cout << "\t\t Sign up" << el << "\t\t*********" << el;
    customers[CID].empty = false;
    customers[CID].ID = 'U' + to_string(CID);
    cout << "customer ID: " << customers[CID].ID << el;
    cout << "PLease enter the customer's name: ";
    cin >> customers[CID].name;
    cout << "Please enter the customer's phone number: ";
    customers[CID].phone = validphone();
    cout << "Please enter the total number of purchased products: ";
    int i; cin >> i;
    bool Bought_products = false;
    for (int j = 1; j <= i; j++)
    {
        string x;
        int y;
        cout << "Enter the new product #" << j << "ID: ";
        cin >> x;
        int index;
        if (x.size() <= 2) {
            index = x[1] - '0';
        }
        else
        {
            index = (x[1] - '0') * 10 + (x[2] - '0');
        }
        cout << "Enter the desired amount:"; // hya5od ad eh mn el product da
        cin >> y;
        if (y > products[index].stock)
        {
            cout << "Sorry, out of stock" << el;
            cout << "Current stock : " << products[index].stock << el;
            cout << "If you wish to place another transaction instead enter 'y' " << el;
            cin >> proceed;
            if (proceed == 'y' || proceed == 'Y') {
                j--;
            }
            continue;
        }
        Bought_products = true;
        customers[CID].purchased_products[index] = y;
        products[index].stock -= y;
    }
    if (Bought_products == false)
        return;
    cout << "Enter the total bill value:";
    cin >> customers[CID].last_value;
    // for discount
    if (customers[CID].last_value > 500) {
        double discount = 95 / 100.0;
        customers[CID].last_value *= discount;
        cout << "Bill after discount : " << customers[CID].last_value << el;
    }
    customers[CID].sum_purchased += customers[CID].last_value;
    cout << "Enter date of bill :-" << el;
    cout << "Year : ";
    cin >> customers[CID].year;
    cout << "Month : ";
    cin >> customers[CID].month;
    cout << "Day :";
    cin >> customers[CID].day;
    Nbcustomers++;
    return;
}

//update details of existing customers by modifying the date of Last bill and its value after every new selling
//process and update the total price of bought products per week
void old_customer()
{
    cout << el << "------------------------------------" << el << el;
    cout << "\t\t Sign in" << el;
    cout << "\t\t*********" << el;
    string x;
    cout << "Please enter your ID : ";
    cin >> x;
    int CID; // customer ID
    if (x.size() <= 2) {
        CID = x[1] - '0';
    }
    else
    {
        CID = (x[1] - '0') * 10 + (x[2] - '0');
    }
    while (true)
    {
        if ((x[0] == 'u' || x[0] == 'U') && CID < 50) {
            break;
        }
        cout << "Invalid ID , Customer ID starts with U followed by a number from 1 to 50 " << el;
        cout << "Please enter your ID : ";
        cin >> x;

        if (x.size() <= 2) {
            CID = x[1] - '0';
        }
        else
        {
            CID = (x[1] - '0') * 10 + (x[2] - '0');
        }
    }


    // now we have the ID
    if (customers[CID].empty == 1) {
        cout << "Sorry,Customer does not exist" << el;
        return;
    }
    int i;
    cout << "Please enter the total number of purchased products: ";
    cin >> i;
    bool Bought_products = false;
    for (int j = 1; j <= i; j++)
    {
        int y;
        cout << "Enter  ID for product " << j << ':';
        cin >> x;
        int index;
        if (x.size() <= 2) {
            index = x[1] - '0';
        }
        else
        {
            index = (x[1] - '0') * 10 + (x[2] - '0');
        }
        while (true)
        {
            if ((x[0] == 'M' || x[0] == 'm') && index < 50) {
                break;
            }
            cout << "Invalid product ID , product ID starts with M followed by a number from 1 to 100" << el;
            cout << "Enter  ID for product " << j << ':';
            cin >> x;
            int index;
            if (x.size() <= 2) {
                index = x[1] - '0';
            }
            else
            {
                index = (x[1] - '0') * 10 + (x[2] - '0');
            }
        }
        
        cout << "Enter the desired amount:";
        cin >> y;
        if (y > products[index].stock)
        {
            cout << "Sorry, out of stock" << el;
            cout << "Current stock : " << products[index].stock << el;
            cout << "If you wish to place another transaction instead, enter (y) ";
            cin >> proceed;
            if (proceed == 'y' || proceed == 'Y')
                j--;
            else {
                continue;
            }
        }
        Bought_products = true;
        customers[CID].purchased_products[index] += y;
        products[index].stock -= y;
    }
    if (!Bought_products)
        return;
    cout << "Enter the total bill value: ";
    cin >> customers[CID].last_value;
    while (true)
    {
        if (customers[CID].last_value > 0) {
            break;
        }
        cout << "Please enter the right value." << el;
        cout << "Enter the total bill value: ";
        cin >> customers[CID].last_value;
    }
    // for discount
    if (customers[CID].last_value > 500) {
        double discount = 95 / 100.0;
        customers[CID].last_value *= discount;
        cout << "Hurray you got a discount!" << el;
        cout << "Your bill after discount: " << customers[CID].last_value << "$" << el;
    }
    customers[CID].sum_purchased += customers[CID].last_value;
    customers[CID].sum_purchased += customers[CID].last_value;
    cout << "Enter date of bill : " << el;
    cout << "Year : ";
    cin >> customers[CID].year;
    cout << "Month : ";
    cin >> customers[CID].month;
    cout << "Day :";
    cin >> customers[CID].day;
    return;
}

void display_customer() {
    // to display details of existing customer
    cout << el << "------------------------------------" << el << el;
    cout << "\t\t Display customer's details" << el;
    cout << "\t\t****************************" << el;
    string x;
    cout << "Please enter your ID : ";
    cin >> x;
    while (x[0] != 'U') {
        cout << "Customer ID start with (U) then a number form 1 to 50." << el;
        cout << "Enter correct ID please " << ':';
        cin >> x;
    }
    int CID; // customer ID
    if (x.size() <= 2) {
        CID = x[1] - '0';
    }
    else {
        CID = (x[1] - '0') * 10 + (x[2] - '0');
    }


    if (customers[CID].empty == true) {
        cout << "No records." << el;
        return;
    }
    cout << "Customer's name: " << customers[CID].name << el;
    cout << "Customer's phone number: " << customers[CID].phone << el;
    cout << "Products purchased: " << el;
    cout << "Product    " << tab << "Amount" << el;
    for (int i = 1; i < 100; i++) {
        if (customers[CID].purchased_products[i] > 0) {
            cout << "Product M" << i << ':' << tab << customers[CID].purchased_products[i] << el;
        }
    }
    cout << "Last bill value: " << customers[CID].last_value << "$" << el;
    cout << "Date of last bill: ";
    cout << customers[CID].day << '/' << customers[CID].month << '/' << customers[CID].year << el;
    cout << "Total money spent: " << customers[CID].sum_purchased << '$' << el;
}
void new_product(int SID) {
    products[SID].empty = false;
    cout << "Enter product name: ";
    cin >> products[SID].name;
    cout << "Enter product price: ";
    cin >> products[SID].price;
}
//name, phone, supplied products. supplier id is auto updated value that starts with S.
void new_supplier(int SID) {
    cout << el << "------------------------------------" << el << el;
    cout << "\t\t Sign up" << el << "\t\t*********" << el;
    suppliers[SID].empty = false;
    suppliers[SID].ID = 'S' + to_string(SID);
    cout << "Supplier ID: " << suppliers[SID].ID << el;
    cout << "PLease enter your name: ";
    cin >> suppliers[SID].name;
    cout << "Enter your phone number: ";
    suppliers[SID].phone = validphone();
    cout << "Please enter the total number of supplied products: ";
    int i;
    cin >> i;
    for (int j = 1; j <= i; j++) {
        string x;
        int y;
        cout << "Enter product #" << j << "ID:";
        while (true) {
            cin >> x;
            if (x[0] == 'M' || x[0] == 'm') {
                break;
            }
            else {
                cout << "Invalid ID." << el;
                cout << "Please enter (M) then a number from 1 to 50: ";
            }
        }

        int index;
        if (x.size() <= 2) {
            index = x[1] - '0';
        }
        else {
            index = (x[1] - '0') * 10 + (x[2] - '0');
        }
        if (products[index].empty) {
            new_product(index);
        }
        bool found = false;
        for (int e = 0; e <= products[index].nexti; e++) {
            if (products[index].supplies[e] == suppliers[SID].name)
                found = true;
        }

        if (!found) {
            products[index].supplies[products[index].nexti] = suppliers[SID].name;
            products[index].nexti++;
        }
        cout << "Enter the added amount: ";
        cin >> y;
        suppliers[SID].med_prod[index] = y;
        products[index].stock += y;
        cout << "Enter expiry month: ";
        cin >> products[index].month;
        if (products[index].month > 12) {
            cout << "Not a valid month." << el;
            cout << "Please enter a valid month: ";
            cin >> products[index].month;
        }
        cout << "Enter expiry year: ";
        cin >> products[index].year;
        if (products[index].year < 2022) {
            cout << "It's expired already." << "\nPlease enter a valid expiry date: ";
            cin >> products[index].year;
        }
    }
    Nbsuppliers++;
    return;
}

void old_supplier()
{
    cout << el << "------------------------------------" << el << el;
    cout << "\t\t Update supplier's details" << el;
    cout << "\t\t***************************" << el;
    string x; // x : supplier ID
    cout << "Please enter supplier's ID : " << el;
    while (true) {
        cin >> x;

        if (x[0] == 'S') {
            break;
        }
        else {
            cout << "Invalid ID." << el;
            cout << "Please enter a valid ID : " << el;
            continue;
        }
    }
    int SID;

    if (x.size() <= 2) {
        SID = x[1] - '0';
    }
    else {
        SID = (x[1] - '0') * 10 + (x[2] - '0');
    }

    cout << "Please enter the total number of supplied products: " << el;
    int i;
    cin >> i;
    for (int j = 1; j <= i; j++) {
        string x;
        int y;
        cout << "Enter the new product #" << j << " ID: ";
        while (true) {
            cin >> x;

            if (x[0] == 'M' || x[0] == 'm') {
                break;
            }
            else {
                cout << "Invalid ID." << el;
                cout << "Please enter (M) then a number from 1 to 50: ";
                continue;
            }
        }

        int index; // the index of the new product
        if (x.size() <= 2) {
            index = x[1] - '0';
        }
        else {
            index = (x[1] - '0') * 10 + (x[2] - '0');
        }

        products[index].id = x;

        if (products[index].empty) {
            new_product(index);
        }

        cout << "Enter the added amount: ";
        cin >> y;
        //to increase stock of new product
        suppliers[SID].med_prod[index] += y;
        products[index].stock += y;

        cout << "Enter expiry month: ";
        cin >> products[index].month;
        if (products[index].month > 12) {
            cout << "Not a valid month." << el;
            cout << "Please enter a valid month: ";
            cin >> products[index].month;
        }
        cout << "Enter expiry year: ";
        cin >> products[index].year;
        if (products[index].year < 2022) {
            cout << "It's expired already." << "\nPlease enter a valid expiry date: ";
            cin >> products[index].year;
        }
        bool found = false;
        for (int e = 0; e <= products[index].nexti; e++) {
            if (products[index].supplies[e] == suppliers[SID].name)
                found = true;
        }

        if (!found) {
            products[index].supplies[products[index].nexti] = suppliers[SID].name;
            products[index].nexti++;
        }
    }
}

void display_supplier() {
    cout << el << "------------------------------------" << el << el;
    cout << "\t\t Display supplier's details" << el;
    cout << "\t\t****************************" << el << el;
    string x; // x : supplier ID
    cout << "Please enter supplier's ID:" << el;
    cin >> x;

    int SID; // SID: the number of supplier
    if (x.size() <= 2) {
        SID = x[1] - '0';
    }
    else {
        SID = (x[1] - '0') * 10 + (x[2] - '0');
    }
    while (true) {
        if ((x[0] == 's' || x[0] == 'S') && SID < 50) {
            break;
        }
        cout << "Invalid ID , Supplier's ID starts with S followed by a number from 1 to 100 " << el;
        cout << "Please enter supplier's ID : " << el;
        cin >> x;

        int SID; // SID: the number of supplier
        if (x.size() <= 2) {
            SID = x[1] - '0';
        }
        else {
            SID = (x[1] - '0') * 10 + (x[2] - '0');
        }
    }

    if (suppliers[SID].empty) {
        cout << "No records." << el;
        return;
    }

    cout << "Supplier's name : " << suppliers[SID].name << el;
    cout << "Supplier's phone number : " << suppliers[SID].phone << el;
    cout << "Supplied Products:- " << el;
    for (int i = 1; i < 50; i++) {
        if (suppliers[SID].med_prod[i] > 0) {
            cout << "Product ID: M" << i << tab << ",Amount: " << suppliers[SID].med_prod[i] << el;
        }
    }
}

void display_product() {
    cout << el << "------------------------------------" << el << el;
    cout << "\t\t Display product details" << el;
    cout << "\t\t**************************" << el;
    string x;
    cout << "Enter product's ID : ";
    cin >> x;
    int PID;
    if (x.size() <= 2) {
        PID = x[1] - '0';
    }
    else {
        PID = (x[1] - '0') * 10 + (x[2] - '0');
    }
    if (products[PID].empty) {
        cout << "No records." << el;
        return;
    }
    cout << "Product's name : " << products[PID].name << el;
    cout << "Product's price : " << products[PID].price << el;
    cout << "Product's amount in stock : " << products[PID].stock << el;
    cout << "Suppliers: " << el;
    for (int i = 0; i < products[PID].nexti; i++) {
        cout << products[PID].supplies[i] << el;
    }
}

void save_lastreport() {
    ofstream outt("lastreport.txt");
    outt << Report.day << el;
    outt << Report.month << el;
    outt << Report.year << el;
}
void save_outoffile() {
    ifstream inn("lastreport.txt");

    inn >> temprep.day;
    inn >> temprep.month;
    inn >> temprep.year;
}

int main() {
    initiliaze();
    cout << el << "\t\t\t\t**************************" << el;
    cout << "\t\t\t\t*Medical Store Management*" << el;
    cout << "\t\t\t\t**************************" << el << el;
    do {
        cout << "Please enter the letter for your desired operation :-" << el;
        cout << "--------------------------------------------------" << el;
        cout << "C: If you are a customer" << el << "P: If you want to display product details" << el
            << "S: If you are a supplier" << el << "D: If you want to delete records" << el;
        cin >> proceed;
        cout << el << "------------------------------------" << el << el;
        cout << tab << tab << "*************************" << el;
        cout << tab << tab << "* Welcome to our system *" << el;
        cout << tab << tab << "*************************" << el << el;

        while (proceed != 'c' && proceed != 'C' && proceed != 's' && proceed != 'S' && proceed != 'p' && proceed != 'P' && proceed != 'd' && proceed != 'D') {
            cout << "Please enter a valid operation." << el;
            cin >> proceed;
        }
        if (proceed == 'c' || proceed == 'C') {
            cout << "Are you a new customer?" << el << "Y: Yes" << el << "N: No" << el;
            cin >> proceed;
            while (proceed != 'y' && proceed != 'Y' && proceed != 'n' && proceed != 'N') {
                cout << "Please enter a valid operation." << el;
                cin >> proceed;
            }
            if (proceed == 'y' || proceed == 'Y') {

                Add_new_customer(Nbcustomers);

            }
            else if (proceed == 'n' || proceed == 'N') {
                cout << el << "Please enter your desired operation :-" << el;
                cout << "------------------------------------" << el;
                cout << "D :To display existing customer details" << el;
                cout << "U :To update existing customer details" << el;
                cin >> proceed;
                while (proceed != 'u' && proceed != 'U' && proceed != 'd' && proceed != 'D') {
                    cout << "Please enter a valid operation." << el;
                    cin >> proceed;
                }
                if (proceed == 'u' || proceed == 'U') {
                    old_customer();

                }
                else if (proceed == 'd' || proceed == 'D') {
                    display_customer();
                }
            }
        }
        else if (proceed == 's' || proceed == 'S') {
            cout << "Are you a new supplier?" << el << "Y: Yes" << el << "N: No" << el;
            cin >> proceed;
            while (proceed != 'y' && proceed != 'Y' && proceed != 'n' && proceed != 'N') {
                cout << "Please enter a valid operation." << el;
                cin >> proceed;
            }
            if (proceed == 'y' || proceed == 'Y') {
                new_supplier(Nbsuppliers);
            }
            else if (proceed == 'n' || proceed == 'N') {
                cout << el << "Please enter your desired operation :-" << el;
                cout << "------------------------------------" << el << el;
                cout << "D :To display existing supplier details" << el;
                cout << "U :To update existing supplier details" << el;
                cin >> proceed;

                while (proceed != 'u' && proceed != 'U' && proceed != 'd' && proceed != 'D') {
                    cout << "Please enter a valid operation." << el;
                    cin >> proceed;
                }
                if (proceed == 'u' || proceed == 'U') {
                    old_supplier();
                }
                else if (proceed == 'd' || proceed == 'D') { // display data for the old supplier
                    display_supplier();
                }
            }
        }
        else if (proceed == 'p' || proceed == 'P') {
            display_product();
        }
        else if (proceed == 'd' || proceed == 'D') {
            cout << el << "\t\t\t Delete records" << el;
            cout << "\t\t\t****************" << el;
            cout << "Please enter your desired operation :-" << el;
            cout << "------------------------------------" << el << el;
            cout << "C: Delete customer details" << el << "S: Delete supplier details" << el << "P: Delete product details" << el;
            cin >> proceed;
            while (proceed != 'c' && proceed != 'C' && proceed != 'p' && proceed != 'P' && proceed != 's' && proceed != 'S') {
                cout << "Please enter a valid operation:" << el;
                cin >> proceed;
            }
            cout << el << "Enter ID: " << el;
            string x;
            cin >> x;
            int ID;
            if (x.size() <= 2) {
                ID = x[1] - '0';
            }
            else
            {
                ID = (x[1] - '0') * 10 + (x[2] - '0');
            }
            while (ID > 99) {
                cout << "Please enter a valid ID: " << el;
                cin >> x;
                if (x.size() <= 2) {
                    ID = x[1] - '0';
                }
                else
                {
                    ID = (x[1] - '0') * 10 + (x[2] - '0');
                }
            }
            if (proceed == 'C' || proceed == 'c') {
                customers[ID].empty = true;
            }
            else if (proceed == 'S' || proceed == 's') {
                suppliers[ID].empty = true;
            }
            else if (proceed == 'P' || proceed == 'p') {
                products[ID].empty = true;
            }

        }
        struct tm newtime;
        time_t now = time(0);
        localtime_s(&newtime, &now);
        //to get today's date to compare it to the last date the user opened the system
        int Month = 1 + newtime.tm_mon;
        int year = 1900 + newtime.tm_year;
        int day = newtime.tm_mday;

        save_lastreport();//save into file
        save_outoffile();// read from file

        if (year > temprep.year || Month > temprep.month || day > temprep.day) {
            bool found = false;
            for (int i = 0; i < 50; i++) {
                if (!products[i].empty && products[i].stock < 5) {
                    if (!found) {
                        cout << "\t\t\t Daily report " << el;
                        cout << "\t\t\t**************" << el;
                        cout << "Recommended products :- " << el;
                        cout << "---------------------" << el << el;
                    }
                    found = true;
                    cout << "Product ID :  M" << i << el;
                    cout << "Product name : " << products[i].name << el;
                    cout << "Stock : " << products[i].stock << el << el;
                }
            }
            cout << "\t\t\t The updated products " << el;
            cout << "\t\t\t**********************" << el;
            bool Update = false;
            for (int i = 1; i < 50; i++) {
                if (products[i].stock != products[i].stock_last) {
                    cout << "Product name: " << products[i].name << el << "Product ID: M" << i << el;
                    products[i].stock_last = products[i].stock;
                    cout << "Product's current stock: " << products[i].stock_last << el;
                    Update = true;
                }
            }
            if (Update == false)
                cout << "No updates." << el;
            Report.year = year;
            Report.month = Month;
            Report.day = day;
            save_lastreport();
        }
        cout << el << "If you want to continue, please enter (y)" << el;
        cin >> proceed;
        if (proceed != 'y' && proceed != 'Y')
        {
            cout << el << "Thank you for visiting us." << el;
            break;
        }
    } while (proceed == 'y' || proceed == 'Y');
}

string validphone() {
    // check if the entered phone number is valid
    bool vphone = true;
    string phone;
    do {
        cin >> phone;
        vphone = true;
        for (int i = 0; i < phone.size(); i++) {
            if (!isdigit(phone[i])) {
                // check each character if it is a number or not
                vphone = false;
                break;
            }
        }
        if (!vphone) {
            cout << "Invalid phone number." << el;
            cout << "Enter the correct phone number: ";
            continue;
        }
        if (phone.size() != 11) {
            cout << "Invalid phone number." << el;
            cout << "Enter the correct phone number: ";
            vphone = false;
            continue;
        }
        if (phone[0] != '0' || phone[1] != '1' || (phone[2] != '1' && phone[2] != '2' && phone[2] != '0' && phone[2] != '5')) {
            cout << "Invalid phone number." << el;
            cout << "Enter the correct phone number: ";
            vphone = false;
            continue;
        }
    } while (!vphone);
    // assign the phone to the database
    return phone;
}