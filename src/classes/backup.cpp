#include "backup.h"

backup::backup()
{
    z.clear();
    Banklog.clear();
    ATMlog.clear();
}

void backup::set(std::string s1, std::string s2, int n1, int n2)
{
    AccountBuffer = s1;
    ATMbuffer = s2;
    this->n1 = n1;
    this->n2 = n2;
}

void backup::BackupAccount(std::string AccNo, Account p)
{
    z[AccNo] = p;
}

void backup::BackupATM(std::vector<ATM> p)
{
    ATMlog = p;
}

void backup::BackupBanklog(std::vector<log> p)
{
    Banklog = p;
}

std::ostream &operator<<(std::ostream &out, const backup &p)
{
    out << "BackupData" << std::endl;
    out << "=================================================" << std::endl;
    out << "AccountReference: " << p.AccountBuffer << std::endl;
    out << "ATMbuffer: " << p.ATMbuffer << std::endl;
    out << "Maximum Account: " << p.n1 << std::endl;
    out << "Maximum ATM: " << p.n2 << std::endl;
    out << "=================================================" << std::endl;
    out << std::endl;
    out << "BEGIN (Account Backup Data)" << std::endl;
    for (auto i : p.z)
    {
        out << "AccountOpen: " << i.second.isAv << std::endl;
        out << "Account Number: " << i.first << std::endl;
        out << "Name: " << i.second.name << std::endl;
        out << "Address: " << i.second.add << std::endl;
        out << "AccountPassword: " << i.second.pw << std::endl;
        out << "ATMstatus: " << i.second.ATMact << std::endl;
        out << "ATMPIN: " << i.second.ATMPIN << std::endl;
        out << "Balance: " << i.second.amount << std::endl;
        out << "LOGDATA" << std::endl;
        for (auto j : i.second.z)
        {
            out << "Time: " << j.Time << " ";
            out << "Action: " << j.action << " ";
            out << "By: " << j.mode << std::endl;
        }
        out << std::endl;
    }
    out << "END (Account Backup Data)" << std::endl;
    out << std::endl;
    out << "BEGIN (Banklogs)" << std::endl;
    for (auto j : p.Banklog)
    {
        out << "Time: " << j.Time << " ";
        out << "Action: " << j.action << " ";
        out << "By: " << j.mode << std::endl;
    }
    out << "END (Banklogs)" << std::endl;
    out << std::endl;
    out << "BEGIN (ATMlogs)" << std::endl;
    for (auto i : p.ATMlog)
    {
        out << "ATMID: " << i.ATMID << std::endl;
        for (auto j : i.z)
        {
            out << "Time: " << j.Time << " ";
            out << "Action: " << j.action << " ";
            out << "By: " << j.mode << std::endl;
        }
        out << std::endl;
    }
    out << "END (ATMlogs)" << std::endl;
    return out;
}
