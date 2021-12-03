#include "manager.h"

void type_S(Bank &b)
{
    if (b.isOpen())
    {
        std::cout << "Bank is already OPEN. " << std::endl;
        return;
    }
    std::cout << "Welcome !!!" << std::endl;
    passwordpolicy();
    std::cout << "Please enter your password: ";
    std::string s;
    std::cin >> s;
    std::cout << std::endl;
    int trials = 2;
    while (!passwordCheck(s) && trials--)
    {
        std::cout << "enter a valid password: ";
        std::cin >> s;
        std::cout << std::endl;
    }
    if (!passwordCheck(s))
    {
        std::cout << "could not open bank. " << std::endl;
        return;
    }
    b.Open(s);
    std::cout << "Bank is OPEN.\n\n";
}

void type_P(Bank &b)
{
    if (!ManagerVerification(b))
        return;
    b.PrintBalance();
    b.addBankLog(log("Account Information accessed", "Manager"));
}

void type_I(Bank &b)
{
    if (!ManagerVerification(b))
        return;
    std::cout << "Interest entered is in percentage and upto 2 decimal digits" << std::endl;
    std::cout << "How much interest you want to apply: ";
    double interest;
    std::cin >> interest;
    int trials = 2;
    while (!checkInterest(interest) && trials--)
    {
        std::cout << "Enter interest rate in valid format: ";
        std::cin >> interest;
    }
    if (!checkInterest(interest))
    {
        std::cout << "Process failed. " << std::endl;
        return;
    }
    b.applyInterest(interest);
    b.addBankLog(log("applied interest " + std::to_string(interest) + "%", "Manager"));
}

void type_E(Bank &b)
{
    if (!b.isOpen())
    {
        std::cout << "Bank is already CLOSED!" << std::endl;
        return;
    }
    std::string response;
    std::cout << "Do you really want to close Bank[y/n]? ";
    std::cin >> response;
    if (response != "Y" && response != "y")
    {
        if (response != "n" && response != "N")
            std::cout << "invalid Answer" << std::endl;
        return;
    }
    if (!ManagerVerification(b))
        return;
    b.ExitBank();
    std::cout << "Bank Closed..................." << std::endl;
}
