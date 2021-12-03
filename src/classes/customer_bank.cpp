#include "customer_bank.h"

void type_O(Bank &b)
{
    if (!b.isOpen())
    {
        std::cout << "Bank is closed. " << std::endl;
        return;
    }
    if (!b.getAvAccount())
    {
        std::cout << "Maximum number of Accounts are open. " << std::endl;
        return;
    }
    std::cout << "Welcome to XYZ bank. " << std::endl;
    passwordpolicy();
    std::string pw;
    std::cout << "Enter your password: ";
    std::cin >> pw;
    int trials = 2;
    while (!passwordCheck(pw) && trials--)
    {
        std::cout << "Enter valid password: ";
        std::cin >> pw;
    }
    std::cout << std::endl;
    if (!passwordCheck(pw))
    {
        std::cout << "Account opening failed.\nTry Again." << std::endl;
        return;
    }
    std::cout << "\nDo you want to enter your personal details[y/n]? ";
    std::string response, name, address;
    name = address = "";
    std::cin >> response;
    if (response == "Y" || response == "y")
    {
        getline(std::cin, response);
        std::cout << "Please Enter your name : ";
        getline(std::cin, name);
        std::cout << "Enter your Address : ";
        getline(std::cin, address);
    }
    if (name == "" || address == "")
    {
        std::cout << "Continued with system's default name. " << std::endl;
    }
    double amount;
    std::cout << "Amount must only be upto 2 decimal digits" << std::endl;
    std::cout << "Enter amount to be deposited: ";
    std::cin >> amount;
    trials = 2;
    while (!checkAmount(amount) && trials--)
    {
        std::cout << "Enter valid amount: ";
        std::cin >> amount;
    }
    std::cout << std::endl;
    if (!checkAmount(amount))
    {
        std::cout << "Account opening failed.\nTry Again." << std::endl;
        return;
    }
    std::string AccNo = b.openAccount(name, address, pw, amount);
    std::cout << "Account number: " << AccNo << std::endl;
    std::cout << "Balance: " << amount << std::endl;
    std::cout << "\nDo you want to activate ATM services[y/n]? ";
    std::cin >> response;
    if (response != "y" && response != "Y")
    {
        if (response != "n" && response != "N")
            std::cout << "Invalid response. " << std::endl;
        return;
    }
    std::cout << "Choose a PIN(4 digits): ";
    std::cin >> response;
    trials = 2;
    while (!checkPIN(response) && trials--)
    {
        std::cout << "Enter valid PIN: ";
        std::cin >> response;
    }
    std::cout << std::endl;
    if (!checkPIN(response))
    {
        std::cout << "ATM activation failed. " << std::endl;
        return;
    }
    b.setATMstatus(AccNo, false, response);
    b.addBankLog(log("Account number " + AccNo + " activated ATM.", "Self"));
    std::cout << "ATM services Activated. " << std::endl;
}

void type_B(Bank &b)
{
    std::string AccNo = commonVerificationAccount(b);
    if (AccNo == "")
        return;
    std::cout << "Balance = " << b.getAmount(AccNo) << std::endl;
    b.addAccountLog(AccNo, log("Balance Inquiry", "self"));
}

void type_D(Bank &b)
{
    std::string AccNo = commonVerificationAccount(b);
    if (AccNo == "")
        return;
    double amount;
    std::cout << "Amount must only be upto 2 decimal digits" << std::endl;
    std::cout << "Enter amount to be deposited: ";
    std::cin >> amount;
    int trials = 2;
    while (!checkAmount(amount) && trials--)
    {
        std::cout << "Enter valid amount: ";
        std::cin >> amount;
    }
    if (!checkAmount(amount))
    {
        std::cout << "Deposit failed.\nTry Again." << std::endl;
        return;
    }
    double d = b.getAmount(AccNo);
    b.updateAmount(AccNo, d + amount);
    b.addAccountLog(AccNo, log("deposited " + std::to_string(amount), "self"));
    std::cout << "Balance: " << d + amount << "\n\n";
}

void type_W(Bank &b)
{
    std::string AccNo = commonVerificationAccount(b);
    if (AccNo == "")
        return;
    double amount;
    std::cout << "Amount must only be upto 2 decimal digits" << std::endl;
    std::cout << "Enter amount to be withdrawn: ";
    std::cin >> amount;
    if (!checkAmount(amount))
    {
        std::cout << "Withdrawal failed.\nTry Again." << std::endl;
        return;
    }
    double d = b.getAmount(AccNo);
    if (d < amount)
    {
        std::cout << "You do not have sufficient funds. " << std::endl;
        return;
    }
    b.updateAmount(AccNo, d - amount);
    std::cout << "Withdrawn: " << amount << std::endl;
    b.addAccountLog(AccNo, log("withdrawn " + std::to_string(amount), "self"));
    std::cout << "Balance: " << d - amount << "\n\n";
}

void type_C(Bank &b)
{
    std::string AccNo = commonVerificationAccount(b);
    if (AccNo == "")
        return;
    std::cout << "Do you really want to close your Account[y/n]? ";
    std::string response;
    std::cin >> response;
    if (response != "y" && response != "Y")
    {
        if (response != "n" && response != "N")
            std::cout << "Invalid response. " << std::endl;
        return;
    }
    b.closeAccount(AccNo);
    std::cout << "Account closed. \n\n";
}

void type_A(Bank &b)
{
    std::string AccNo = commonVerificationAccount(b);
    if (AccNo == "")
        return;
    int m = b.getATMstatus(AccNo);
    if (m != -1)
    {
        std::cout << "ATM services are already active." << std::endl;
        return;
    }
    std::string response;
    std::cout << "Enter PIN(4 digits): ";
    std::cin >> response;
    int trials = 2;
    while (!checkPIN(response) && trials--)
    {
        std::cout << "Enter valid PIN: ";
        std::cin >> response;
    }
    std::cout << std::endl;
    if (!checkPIN(response))
    {
        std::cout << "ATM activation failed." << std::endl;
        return;
    }
    b.setATMstatus(AccNo, false, response);
    b.addBankLog(log("Account number " + AccNo + " activated ATM.", "Self"));
    std::cout << "ATM services Activated." << std::endl;
}

void type_U(Bank &b)
{
    std::string AccNo = commonVerificationAccount(b);
    if (AccNo == "")
        return;
    int m = b.getATMstatus(AccNo);
    if (m == -1)
    {
        std::cout << "ATM services are inactive." << std::endl;
        std::cout << "First Activate your ATM. " << std::endl;
        return;
    }
    if (m != 0)
    {
        std::cout << "ATM is already active. " << std::endl;
        return;
    }
    std::string response;
    std::cout << "Choose PIN(4 digits): ";
    std::cin >> response;
    int trials = 2;
    while (!checkPIN(response) && trials--)
    {
        std::cout << "Enter valid PIN: ";
        std::cin >> response;
    }
    std::cout << std::endl;
    if (!checkPIN(response))
    {
        std::cout << "ATM re-activation failed." << std::endl;
        return;
    }
    b.setATMstatus(AccNo, false, response);
    b.addBankLog(log("Account number " + AccNo + " unblocked ATM.", "self"));
    b.addAccountLog(AccNo, log("ATM unblocked", "self"));
    std::cout << "ATM UNBLOCKED." << std::endl;
}
