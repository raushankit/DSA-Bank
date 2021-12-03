#include "bank.h"

Bank::Bank(int max_Acc, int max_ATM)
{
    open = false;
    n1 = max_Acc;
    n2 = max_ATM;
    BankPW = "";
    ump.clear();
    BankLog.clear();
}

bool Bank::isOpen() { return open; }

void Bank::Open(std::string pw)
{
    BankPW = pw;
    open = true;
    std::cout << "Do you want your last backup data[y/n]? ";
    std::string str;
    std::cin >> str;
    std::ifstream fin("Logfile.txt");
    int flag = 0;
    if (str == "Y" || str == "y")
    {
        if (fin.peek() != std::ifstream::traits_type::eof())
            flag = 3;
        else
            flag = 2;
    }
    else
    {
        if (str == "n" || str == "N")
            flag = 1;
        else
            std::cout << "Invalid response. " << std::endl;
    }

    if (flag == 3)
    {
        fin >> str >> str >> str;
        std::string Accref, atmref;
        fin >> Accref >> str >> atmref;
        int bn1, bn2;
        fin >> str >> str >> bn1;
        fin >> str >> str >> bn2;
        n1 = (n1 > bn1) ? n1 : bn1;
        n2 = (n2 > bn2) ? n2 : bn2;
        int len = std::to_string(n2).length();
        for (int i = 1; i <= n2; i++)
        {
            std::string temp = std::to_string(i);
            for (int j = temp.length(); j < len; j++)
            {
                temp = "0" + temp;
            }
            ATMlog.push_back(ATM(ATMref + temp));
        }
        bool accFlags[n1] = {0};
        while (str != "BEGIN (Account Backup Data)")
            getline(fin, str);
        while (true)
        {
            getline(fin, str);
            if (str == "END (Account Backup Data)")
                break;
            bool wasOpen;
            std::stringstream ss(str);
            ss >> str >> wasOpen;
            std::string Accno;
            ss.str("");
            ss.clear();
            getline(fin, str);
            ss << str;
            ss >> str >> str >> Accno;
            if (!wasOpen)
                while (ss >> str)
                    Accno += " " + str;
            Account tempAcc = getAccount(wasOpen, fin);
            if (wasOpen)
            {
                int n_Acc = 0;
                for (unsigned int i = Accref.length(); i < Accno.length(); i++)
                {
                    n_Acc = 10 * n_Acc + (Accno[i] - '0');
                }
                accFlags[n_Acc - 1] = true;
                ump[Accno] = tempAcc;
            }
            else
                Backup.BackupAccount(Accno, tempAcc);
        }
        while (str != "BEGIN (Banklogs)")
            getline(fin, str);
        while (true)
        {
            getline(fin, str);
            if (str == "END (Banklogs)")
                break;
            BankLog.push_back(getlog(str));
        }
        while (str != "BEGIN (ATMlogs)")
            getline(fin, str);
        while (true)
        {
            getline(fin, str);
            if (str == "END (ATMlogs)")
                break;
            std::stringstream pp(str);
            pp >> str >> str;
            int n_Atm = 0;
            for (unsigned int i = atmref.length(); i < str.length(); i++)
            {
                n_Atm = 10 * n_Atm + (str[i] - '0');
            }
            while (true)
            {
                getline(fin, str);
                if (str == "")
                    break;
                ATMlog[n_Atm - 1].addlog(getlog(str));
            }
        }
        for (int i = 0; i < n2; i++)
        {
            ATMlog[i].addlog(log("ATM online !!!", "Manager"));
        }
        for (int i = 1; i <= n1; i++)
        {
            if (!accFlags[i - 1])
                avAcc.push(i);
        }
    }
    else
    {
        if (flag == 2)
            std::cout << "Backup files don't exist. " << std::endl;
        for (int i = 1; i <= n1; i++)
        {
            avAcc.push(i);
        }
        int len = std::to_string(n2).length();
        for (int i = 1; i <= n2; i++)
        {
            std::string temp = std::to_string(i);
            for (int j = temp.length(); j < len; j++)
            {
                temp = "0" + temp;
            }
            ATMlog.push_back(ATM(ATMref + temp));
            ATMlog[i - 1].addlog(log("ATM online !!!", "Manager"));
        }
    }
    Backup.set(buffer, ATMref, n1, n2);
    BankLog.push_back(log("Bank Opened", "manager"));
}

bool Bank::verifyPassword(std::string AcN, std::string p)
{
    return ump[AcN].checkPassword(p);
}

bool Bank::verifyPIN(std::string AcN, std::string p)
{
    return ump[AcN].checkPIN(p);
}

bool Bank::verifyAdminPassword(std::string pw)
{
    return BankPW == pw;
}

std::ostream &operator<<(std::ostream &out, const Bank &b)
{
    if (!b.open)
    {
        out << "Bank is closed. " << std::endl;
        return out;
    }
    out << "Bank is open. " << std::endl;
    out << "max number of Accounts : " << b.n1 << std::endl;
    out << "max number of ATMs : " << b.n2 << std::endl;
    out << "Password : " << b.BankPW << std::endl;
    out << "Available Accounts : " << b.avAcc.size() << std::endl;
    out << "Account Informattion : " << std::endl;
    for (auto i : b.ump)
    {
        out << i.first << ": " << std::endl;
        out << i.second << std::endl;
    }
    out << "Account Information end. " << std::endl;
    out << "Banklog Data: " << std::endl;
    for (auto i : b.BankLog)
    {
        out << i << std::endl;
    }
    out << "Banklog Data end. " << std::endl;
    out << "Backup data: " << std::endl;
    out << b.Backup << std::endl;
    out << "Backup data end" << std::endl;
    out << "ATM log data : " << std::endl;
    for (auto i : b.ATMlog)
    {
        out << i << std::endl;
    }
    out << "ATM log data end." << std::endl;
    return out;
}

double Bank::getAmount(std::string s)
{
    return ump[s].getAmount();
}

void Bank::updateAmount(std::string s, double d)
{
    ump[s].setAmount(d);
}

bool Bank::getAccStatus(std::string Acc)
{
    return ump[Acc].getStatus();
}

void Bank::PrintBalance()
{
    if (ump.size() == 0)
    {
        std::cout << "No Acconuts are open. " << std::endl;
        return;
    }
    std::cout << "Account number         Balance " << std::endl;
    for (auto i : ump)
    {
        std::cout << "   " << i.first << "                " << i.second.getAmount() << std::endl;
    }
}

bool Bank::getAvAccount()
{
    return !avAcc.empty();
}

std::string Bank::openAccount(std::string nm, std::string add, std::string pw, double amnt)
{
    int m = avAcc.front();
    avAcc.pop();
    std::string AccNo = std::to_string(m);
    m = std::to_string(n1).length();
    for (int i = AccNo.length(); i < m; i++)
    {
        AccNo = "0" + AccNo;
    }
    if (nm == "")
        nm = "name_" + AccNo;
    if (add == "")
        add = "address_" + AccNo;
    AccNo = buffer + AccNo;
    ump[AccNo] = Account(nm, add, pw, amnt);
    BankLog.push_back(log("Account number " + AccNo + " opened", "Self"));
    ump[AccNo].addLog(log("Account opened ", "Self"));
    ump[AccNo].addLog(log("first deposit of " + std::to_string(amnt), "Self"));
    return AccNo;
}

int Bank::getATMstatus(std::string AcNo)
{
    return ump[AcNo].getATMstatus();
}

void Bank::addAccountLog(std::string AccNo, log p)
{
    ump[AccNo].addLog(p);
}

void Bank::closeAccount(std::string AccNo)
{
    ump[AccNo].addLog(log("Account Closed", "Self"));
    BankLog.push_back(log("closed Account " + AccNo, "Self"));
    int n = 0;
    for (unsigned int i = buffer.length(); i < AccNo.length(); i++)
    {
        n = 10 * n + (AccNo[i] - '0');
    }
    avAcc.push(n);
    ump[AccNo].setStatus(false);
    unsigned long long int now = std::chrono::seconds(std::chrono::seconds(std::time(NULL))).count();
    Backup.BackupAccount(AccNo + " (" + std::to_string(now) + ")", ump[AccNo]);
    ump.erase(AccNo);
}

void Bank::addBankLog(log p)
{
    BankLog.push_back(p);
}

std::string Bank::addATMlog(log p)
{
    unsigned long long int now = std::chrono::seconds(std::chrono::seconds(std::time(NULL))).count();
    int ATMno = now % n2;
    ATMlog[ATMno].addlog(p);
    return ATMlog[ATMno].getID();
}

std::string Bank::getAccountName(std::string s)
{
    return ump[s].getName();
}

void Bank::setATMstatus(std::string An, bool penalty, std::string pw)
{
    int stat = ump[An].getATMstatus();
    if (penalty)
    {
        ump[An].setATMstatus(stat - 1);
        if (stat > 1)
            ump[An].addLog(log("Entered Incorrect PIN(" + std::to_string(stat - 1) + " trials left)", "self"));
        else
            ump[An].addLog(log("ATM blocked (Incorrect PIN 3 times)", "self"));
    }
    else
        ump[An].setPIN(pw);
}

void Bank::applyInterest(double I)
{
    if (ump.size() == 0)
    {
        std::cout << "No Accounts are open. " << std::endl;
        return;
    }
    for (auto i : ump)
    {
        std::string AccNo = i.first;
        double d = i.second.getAmount();
        double t_i = 0.01 * d * I;
        long long int e = 100 * t_i;
        if (t_i - 0.01 * e >= 0.005)
            e++;
        t_i = 0.01 * e;
        updateAmount(AccNo, d + t_i);
        addAccountLog(AccNo, log("Applied Interest " + std::to_string(t_i), "Manager"));
    }
    std::cout << "Interest applied successfully. " << std::endl;
}

void Bank::getMIniStatement(std::string AccNo)
{
    ump[AccNo].printMiniStatement(5);
}

void Bank::ExitBank()
{
    for (auto i : ump)
    {
        unsigned long long int now = std::chrono::seconds(std::chrono::seconds(std::time(NULL))).count();
        std::string AccNo = i.first;
        ump[AccNo].addLog(log("Bank Closed", "Manager"));
        Backup.BackupAccount(AccNo + " (" + std::to_string(now) + ")", ump[AccNo]);
    }
    for (int i = 0; i < n2; i++)
    {
        ATMlog[i].addlog(log("Bank Closed.", "Manager"));
    }
    open = false;
    BankLog.push_back(log("Bank Closed.", "Manager"));
    Backup.BackupATM(ATMlog);
    Backup.BackupBanklog(BankLog);
    char *file = (char *)"Logfile.txt";
    std::ofstream fout;
    fout.open(file, std::ofstream::out | std::ofstream::trunc);
    fout << Backup << std::endl;
    std::cout << "Backup data was saved in a text file <Logfile.txt> in the local directory. " << std::endl;
    std::cout << "Do you want your Backup data on Terminal[y/n]?";
    std::string response;
    std::cin >> response;
    if (response == "Y" || response == "y")
        std::cout << Backup << std::endl;
    else
    {
        if (response != "N" && response != "n")
            std::cout << "Invalide Response" << std::endl;
    }
}