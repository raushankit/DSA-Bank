#ifndef __BACKUP__
#define __BACKUP__
#include "atm.h"
#include "Account.h"
#include <unordered_map>

class backup
{
public:
    backup();
    void set(std::string, std::string, int, int);
    void BackupAccount(std::string, Account);
    void BackupATM(std::vector<ATM>);
    void BackupBanklog(std::vector<log>);
    friend std::ostream &operator<<(std::ostream &out, const backup &);

private:
    std::string ATMbuffer, AccountBuffer;
    int n1;
    int n2;
    std::unordered_map<std::string, Account> z;
    std::vector<log> Banklog;
    std::vector<ATM> ATMlog;

    void load();
};

#endif
