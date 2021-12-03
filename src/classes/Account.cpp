#include "Account.h"

Account::Account()
{
    pw = ATMPIN = name = add = "";
    isAv = false;
    ATMact = -1;
    amount = 0;
    z.clear();
}

Account::Account(std::string nm, std::string ad, std::string ps, double b)
{
    ATMPIN = "";
    name = nm;
    add = ad;
    pw = ps;
    amount = b;
    isAv = true;
    ATMact = -1;
}

Account::Account(const Account &p)
{
    pw = p.pw;
    ATMPIN = p.ATMPIN;
    name = p.name;
    isAv = p.isAv;
    add = p.add;
    ATMact = p.ATMact;
    amount = p.amount;
    z = p.z;
}

Account &Account::operator=(const Account &p)
{
    if (this != &p)
    {
        pw = p.pw;
        ATMPIN = p.ATMPIN;
        name = p.name;
        isAv = p.isAv;
        add = p.add;
        ATMact = p.ATMact;
        amount = p.amount;
        z = p.z;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Account &p)
{
    if (!p.isAv)
        out << "Account : closed " << std::endl;
    else
        out << "Account : open " << std::endl;
    out << "Name : " << p.name << std::endl;
    out << "Address : " << p.add << std::endl;
    out << "Balance : " << p.amount << std::endl;
    out << "\nLOG data " << std::endl;
    for (auto x : p.z)
    {
        out << x << std::endl;
    }
    return out;
}

void Account::addLog(log p)
{
    z.push_back(p);
}

bool Account::checkPassword(std::string p)
{
    return pw == p;
}

bool Account::getStatus()
{
    return isAv;
}

void Account::setStatus(bool b)
{
    isAv = b;
}

double Account::getAmount()
{
    return amount;
}

std::string Account::getName()
{
    return name;
}

void Account::setAmount(double d)
{
    amount = d;
}

int Account::getATMstatus()
{
    return ATMact;
}

void Account::setATMstatus(int b)
{
    ATMact = b;
}

bool Account::checkPIN(std::string p)
{
    return p == ATMPIN;
}

void Account::printMiniStatement(unsigned int n)
{
    int m;
    if (z.size() <= n)
        m = 0;
    else
        m = z.size() - n;
    for (int i = z.size() - 1; i >= m; i--)
    {
        std::cout << z[i] << std::endl;
    }
}

void Account::setPIN(std::string p)
{
    ATMact = 3;
    if (ATMPIN == "")
    {
        z.push_back(log("ATM activated. ", "self"));
    }
    else
    {
        z.push_back(log("ATM PIN changed oldPIN = " + ATMPIN, "self"));
    }
    ATMPIN = p;
}

Account getAccount(bool b, std::ifstream &fin)
{
    Account p;
    std::string str;
    p.isAv = b;
    getline(fin, str);
    std::stringstream ss(str);
    ss >> str >> p.name;
    while (ss >> str)
        p.name += " " + str;
    ss.str("");
    ss.clear();
    getline(fin, str);
    ss << str;
    ss >> str >> p.add;
    while (ss >> str)
        p.add += " " + str;
    ss.str("");
    ss.clear();
    getline(fin, str);
    ss << str;
    ss >> str >> p.pw;
    while (ss >> str)
        p.pw += " " + str;
    ss.str("");
    ss.clear();
    getline(fin, str);
    ss << str;
    ss >> str >> p.ATMact;
    ss.str("");
    ss.clear();
    getline(fin, str);
    ss << str;
    ss >> str >> p.ATMPIN;
    ss.str("");
    ss.clear();
    getline(fin, str);
    ss << str;
    ss >> str >> p.amount;
    while (str != "LOGDATA")
        getline(fin, str);
    while (true)
    {
        getline(fin, str);
        if (str == "")
            break;
        p.z.push_back(getlog(str));
    }
    return p;
}
