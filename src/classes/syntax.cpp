#include "syntax.h"

bool passwordCheck(std::string pw)
{
    if (pw.length() < 8)
    {
        std::cout << "Your password's length is LESS THAN 8 " << std::endl;
        return false;
    }
    bool num_a, lar_a, small_a, spec_a;
    num_a = lar_a = small_a = spec_a = false;
    for (char c : pw)
    {
        int temp = (int)c;
        if (!lar_a && temp >= 65 && temp <= 90)
            lar_a = true;
        if (!small_a && temp >= 97 && temp <= 122)
            small_a = true;
        if (!spec_a && ((temp >= 32 && temp <= 47) || (temp >= 58 && temp <= 64) || (temp >= 91 && temp <= 96) || (temp >= 123 && temp <= 126)))
        {
            spec_a = true;
        }
        if (!num_a && temp >= 48 && temp <= 57)
            num_a = true;
    }
    if (!(num_a && lar_a && small_a && spec_a))
    {
        std::cout << "Password is not according to the policy. " << std::endl;
        return false;
    }
    return true;
}

bool checkPIN(std::string PIN)
{
    if (PIN.length() != 4)
    {
        std::cout << "PIN length must be 4. " << std::endl;
        return false;
    }
    for (char c : PIN)
    {
        if (c - '0' < 0 || c - '0' > 9)
        {
            std::cout << "Only numbers are allowed. " << std::endl;
            return false;
        }
    }
    return true;
}

bool checkAmount(double Amount)
{
    if (Amount <= 0)
    {
        std::cout << "Entered Amount is zero or less than zero. " << std::endl;
        return false;
    }
    std::string temp = std::to_string(Amount);
    for (unsigned int i = temp.length() - 4; i < temp.length(); i++)
    {
        if (temp[i] != '0')
        {
            std::cout << "Amount has more the 2 decimal digits. " << std::endl;
            return false;
        }
    }
    return true;
}

bool checkInterest(double interest)
{
    if (interest <= 0)
    {
        std::cout << "Entered interest rate is zero or less than zero. " << std::endl;
        return false;
    }
    std::string temp = std::to_string(interest);
    for (unsigned int i = temp.length() - 4; i < temp.length(); i++)
    {
        if (temp[i] != '0')
        {
            std::cout << "entered interest rate was INVALID." << std::endl;
            return false;
        }
    }
    return true;
}

void passwordpolicy()
{
    std::cout << "Password must contain : " << std::endl;
    std::cout << "   1. must be at least 8 characters long. " << std::endl;
    std::cout << "   2. must contain a capital letter[A,B.....,Z]." << std::endl;
    std::cout << "   3. must contain a small letter[a,b.....,z]." << std::endl;
    std::cout << "   4. must contain a number[0,1.....,9]" << std::endl;
    std::cout << "   5. must contain a special character[!,@.....,*]" << std::endl;
}

void INFO(bool b)
{
    if (b)
    {
        std::cout << "   BANK MODE   " << std::endl;
        std::cout << " ============= " << std::endl;
        std::cout << "CODE :: ACTION" << std::endl;
        std::cout << "  S  :: OPEN BANK" << std::endl;
        std::cout << "  O  :: OPEN AN ACCOUNT" << std::endl;
        std::cout << "  B  :: BALANCE INQUIRY" << std::endl;
        std::cout << "  W  :: WITHDRAWAL" << std::endl;
        std::cout << "  D  :: DEPOSIT" << std::endl;
        std::cout << "  C  :: CLOSE ACCOUNT" << std::endl;
        std::cout << "  A  :: ACTIVATE ATM" << std::endl;
        std::cout << "  U  :: UNLOCK ATM" << std::endl;
        std::cout << "  P  :: PRINT ACCOUNTS" << std::endl;
        std::cout << "  I  :: APPLY INTEREST" << std::endl;
        std::cout << "  E  :: EXIT AND CLOSE ALL ACCOUNTS" << std::endl;
    }
    else
    {
        std::cout << "   ATM MODE   " << std::endl;
        std::cout << " ============ " << std::endl;
        std::cout << "CODE :: ACTION" << std::endl;
        std::cout << "  W  :: WITHDRAWAL" << std::endl;
        std::cout << "  M  :: MINI STATEMENT" << std::endl;
        std::cout << "  F  :: FUND TRANSFER" << std::endl;
        std::cout << "  B  :: BALANCE INQUIRY" << std::endl;
        std::cout << "  X  :: PIN CHANGE" << std::endl;
    }
}
