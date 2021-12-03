#ifndef __BANK__
#define __BANK__
#include <queue>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include "backup.h"

class Bank
{
public:
    Bank(int, int);
    bool isOpen();
    void Open(std::string);
    bool getAvAccount();
    std::string openAccount(std::string, std::string, std::string, double);
    bool verifyPassword(std::string, std::string);
    bool verifyAdminPassword(std::string);
    bool verifyPIN(std::string, std::string);
    double getAmount(std::string);
    void updateAmount(std::string, double);
    bool getAccStatus(std::string);
    void PrintBalance();
    int getATMstatus(std::string);
    void setATMstatus(std::string, bool, std::string);
    void addAccountLog(std::string, log);
    void closeAccount(std::string);
    void addBankLog(log);
    std::string addATMlog(log);
    void applyInterest(double);
    void ExitBank();
    std::string getAccountName(std::string);
    void getMIniStatement(std::string);
    friend std::ostream &operator<<(std::ostream &, const Bank &);

private:
    const std::string buffer = "0";
    const std::string ATMref = "0";
    bool open;
    int n1; // n1=max number of accounts
    int n2; // n2  = no of ATMs.
    std::string BankPW;
    std::queue<int> avAcc;
    std::unordered_map<std::string, Account> ump;
    std::vector<log> BankLog;
    backup Backup;
    std::vector<ATM> ATMlog;
};

#endif
