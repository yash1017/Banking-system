#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;
#define MIN_BALANCE 500
class insufficientfunds{};

class account
{
    private: 
    long accountnumber;
    string firstname;
    string lastname;
    static long nextaccountnumber;
    float balance;

    public:
//constructors

    account(){}
    account(string fname,string lname,float balance);
//accessors

    long getaccountnumber(){return accountnumber;};
    string getfirstname(){return firstname;};
    string getlastname(){return lastname;};
    float getbalance(){return balance;};

    void deposit(float amount)
    {
        balance=balance+amount;
    }
    void withdraw(float amount)
    {  
        if((balance-amount) < MIN_BALANCE){
            throw insufficientfunds();
        }
        balance=balance-amount;
        
    }
    static void setlastaccountnumber(long accountnumber);
    static long getlastaccountnumber();
    friend ofstream & operator<<(ofstream &ofs,account &acc);
    friend ifstream & operator>>(ifstream &ifs,account &acc);
    friend ostream & operator<<(ostream &os,account &acc);

};
long account::nextaccountnumber=0;

class bank
{
    map<long,account> accounts;
    public:

    bank();
    account openaccount(string fname,string lname,float balance);
    account balanceenquiry(long accountnumber);
    account closeaccount(long accountnumber);
    account deposit(long accountnumber,float amount);
    account withdraw(long accountnumber,float amount);
    account showallaccounts();
    ~bank();  
};

int main()
{
    bank b;
    account acc;


    int choice;
    string fname,lname;
    float amount;
    long accountnumber;
    

    cout<<"*****welcome to our bank*****"<<endl;
    cout<<endl;
    do
    {
    cout<<"1 . Open an Account"<<endl;
    cout<<"2 . Balance Enquiry"<<endl;
    cout<<"3 . Deposit"<<endl;
    cout<<"4 . Withdraw"<<endl;
    cout<<"5 . Show All Accounts"<<endl;
    cout<<"6 . Close Account"<<endl;
    cout<<"7 . quit"<<endl;
    cout<<endl;
    cout<<"***Please Select One Choice*** : ";
    cin>>choice;
    switch(choice)
    {
        case 1:
               cout<<"Enter your First Name:"<<endl;
               cin>>fname;
               cout<<"Enter your Last Name:"<<endl;
               cin>>lname;
               cout<<"Enter your First deposit:"<<endl;
               cin>>amount;
               acc=b.openaccount(fname,lname,amount);
               cout<<"Congratulations Your Account Is Created"<<endl;
               cout<<acc;
               break;
        case 2:
               cout<<"Enter Your Account Number:"<<endl;
               cin>>accountnumber; 
               acc=b.balanceenquiry(accountnumber);
               cout<<"Your Account Balace is:"<<endl;
               cout<<acc;
               break;
        case 3:
               cout<<"Enter Your Account Number:"<<endl;
               cin>>accountnumber;
               cout<<"Enter Yout Amount:"<<endl;
               cin>>amount;
               acc=b.deposit(accountnumber,amount);
               cout<<"Your Amount Is Successfully Deposited"<<endl;
               cout<<acc;
               break;
        case 4:      
               cout<<"Enter Your Account Number:"<<endl;
               cin>>accountnumber;
               cout<<"Enter Your Amount:"<<endl;
               cin>>amount;
               acc=b.withdraw(accountnumber,amount);
               cout<<"Your Amount is Successfully Withdrawn"<<endl;
               cout<<acc;
               break;
        case 5:
               b.showallaccounts();
               break;       
        case 6:
               cout<<"Enter Your Account Number"<<endl;
               cin>>accountnumber;
               b.closeaccount(accountnumber);
               cout<<"Your Account Is Successfully Closed"<<endl;
               break;
        case 7:
               break; 
               default:
               cout<<"Please Enter Correct Choice"<<endl;
               exit(0);
    }
    }while(choice!=7);

    return 0;
}


account::account( string fname, string lname,float amount)
{
    nextaccountnumber++;
    accountnumber=nextaccountnumber;
    firstname=fname;
    lastname=lname;
    balance=amount;
}
account bank::balanceenquiry(long accountnumber)
{
    map<long,account>::iterator it=accounts.find(accountnumber);
    return it->second;
}
account bank::deposit(long accountnumber,float amount)
{
    map<long,account>::iterator it=accounts.find(accountnumber);
    it->second.deposit(amount);
    return it->second;
}
account bank::withdraw(long accountnumber,float amount)
{
    map<long,account>::iterator it=accounts.find(accountnumber);
    it->second.withdraw( amount);
    return it->second;
}
account bank::closeaccount(long accountnumber)
{
    map<long,account>::iterator it=accounts.find(accountnumber);
    cout<<"Account Deleted Successfully"<<endl;
    accounts.erase(accountnumber);
}
account bank::showallaccounts()
{
    map<long,account>::iterator it;
    for(it=accounts.begin();it!=accounts.end();it++)
    {
        cout<<"Account "<<it->first<<endl<<it->second<<endl;
    }
}
void account::setlastaccountnumber(long accountnumber)
{
 nextaccountnumber=accountnumber;
}
long account::getlastaccountnumber()
{
 return nextaccountnumber;
}
ofstream & operator<<(ofstream &ofs,account &acc)
{
    ofs<<acc.accountnumber<<endl;
    ofs<<acc.firstname<<endl;
    ofs<<acc.lastname<<endl;
    ofs<<acc.balance<<endl;
    return ofs;
}
ifstream & operator>>(ifstream &ifs,account &acc)
{
    ifs>>acc.accountnumber;
    ifs>>acc.firstname;
    ifs>>acc.lastname;
    ifs>>acc.balance;
    return ifs;
}
ostream & operator<<(ostream &os,account &acc)
{
    os<<"First Name:"<<acc.getfirstname()<<endl;
    os<<"Last Name:"<<acc.getlastname()<<endl;
    os<<"Account Number:"<<acc.getaccountnumber()<<endl;
    os<<"Balance:"<<acc.getbalance()<<endl;
    return os;
}

account bank::openaccount(string fname,string lname,float balance)
{
 ofstream outfile;
 account Account(fname,lname,balance);
 accounts.insert(pair<long,account>(Account.getaccountnumber(),Account));
 outfile.open("Bank.D ata", ios::trunc);

 map<long,account>::iterator it;
 for(it=accounts.begin();it!=accounts.end();it++)
 {
 outfile<<it->second;
 }
 outfile.close();
 return Account;
}
bank::bank()
{

    account Account;
    ifstream infile;
    infile.open("bank.data");
    if(!infile)
    {
        cout<<"Error in Opening ! File Not Found !!"<<endl;
        return;
    }
    while(!infile.eof())
    {
        infile>>Account;
        accounts.insert(pair<long,account>(Account.getaccountnumber(),Account));
    }
    
    account::setlastaccountnumber(Account.getaccountnumber());

    infile.close();
}


bank::~bank()
{
    ofstream outfile;
    outfile.open("bank.data",ios::trunc);

    map<long,account>::iterator it;
    for(it=accounts.begin();it!=accounts.end();it++)
    {
        outfile<<it->second;
    }
    outfile.close();
}
