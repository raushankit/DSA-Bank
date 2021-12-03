#ifndef __ACCOUNT__
#define __ACCOUNT__
#include "log.h"
#include <vector>
#include <fstream>

class Account
{
public:
    Account();
    Account(std::string, std::string, std::string, double);
    Account(const Account &);
    Account &operator=(const Account &);
    void addLog(log);
    bool checkPassword(std::string);
    bool checkPIN(std::string);
    bool getStatus();
    void setStatus(bool);
    double getAmount();
    void setAmount(double);
    int getATMstatus();
    std::string getName();
    void setATMstatus(int);
    void printMiniStatement(unsigned int);
    void setPIN(std::string);
    friend std::ostream &operator<<(std::ostream &, const Account &);
    friend std::ostream &operator<<(std::ostream &, const backup &);
    friend Account getAccount(bool, std::ifstream &);

private:
    bool isAv;
    std::string pw;
    std::string ATMPIN;
    std::string name;
    std::string add;
    int ATMact;
    double amount;
    std::vector<log> z;
};

Account getAccount(bool, std::ifstream &);

#endif
