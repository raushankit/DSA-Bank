#include "verification.h"

std::string commonVerificationAccount(Bank b)
{
    if (!b.isOpen())
    {
        std::cout << "Bank is CLOSED!." << std::endl;
        return "";
    }
    std::cout << "Enter Your Account number: ";
    std::string ACCNo;
    std::cin >> ACCNo;
    if (!b.getAccStatus(ACCNo))
    {
        std::cout << "This Account does not exist. " << std::endl;
        return "";
    }
    std::string pw;
    std::cout << "Enter your password: ";
    std::cin >> pw;
    if (!b.verifyPassword(ACCNo, pw))
    {
        std::cout << "Incorrect Password. " << std::endl;
        return "";
    }
    return ACCNo;
}

std::string commonVerificationATM(Bank &b)
{
    if (!b.isOpen())
    {
        std::cout << "Bank is CLOSED!." << std::endl;
        return "";
    }
    std::cout << "Enter Your Account number: ";
    std::string ACCNo;
    std::cin >> ACCNo;
    if (!b.getAccStatus(ACCNo))
    {
        std::cout << "This Account does not exist. " << std::endl;
        return "";
    }
    int m = b.getATMstatus(ACCNo);
    if (m == -1)
    {
        std::cout << "ATM services are not active. " << std::endl;
        return "";
    }
    if (m == 0)
    {
        std::cout << "ATM services are blokced. " << std::endl;
        return "";
    }
    std::string pw;
    std::cout << "Enter your ATM PIN: ";
    std::cin >> pw;
    if (!b.verifyPIN(ACCNo, pw))
    {
        std::cout << "Incorrect PIN " << std::endl;
        if (m == 1)
        {
            std::cout << "You have entered wrong PIN 3 times.\nATM Blocked." << std::endl;
            b.addBankLog(log("Account number " + ACCNo + "  ATM BLOCKED", "self"));
        }
        b.setATMstatus(ACCNo, true, "");
        return "";
    }
    return ACCNo;
}

bool ManagerVerification(Bank b)
{
    if (!b.isOpen())
    {
        std::cout << "Bank is CLOSED!." << std::endl;
        return false;
    }
    std::cout << "Please Enter your Password: ";
    std::string pw;
    std::cin >> pw;
    if (!passwordCheck(pw))
    {
        std::cout << "Invalid Password. " << std::endl;
        return false;
    }
    if (!b.verifyAdminPassword(pw))
    {
        std::cout << "Incorrect Password. " << std::endl;
        return false;
    }
    return true;
}
