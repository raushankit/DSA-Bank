#include "function.h"

void interaction(Bank &bank, char t)
{
    if (t == 'M' || t == 'F' || t == 'X')
    {
        std::cout << "Switch to ATM MODE for these operations" << std::endl;
        return;
    }
    switch (t)
    {
    case 'O':
        type_O(bank);
        break;

    case 'B':
        type_B(bank);
        break;

    case 'D':
        type_D(bank);
        break;

    case 'W':
        type_W(bank);
        break;

    case 'C':
        type_C(bank);
        break;

    case 'I':
        type_I(bank);
        break;

    case 'P':
        type_P(bank);
        break;

    case 'E':
        type_E(bank);
        break;

    case 'S':
        type_S(bank);
        break;

    case 'A':
        type_A(bank);
        break;

    case 'U':
        type_U(bank);
        break;

    default:
        std::cout << "INVALID TRANSACTION TYPE\nTry Again.\n";
        break;
    }
}

void ATMInteraction(Bank &bank, char t)
{
    if (t == 'S' || t == 'P' || t == 'I' || t == 'E' || t == 'A' || t == 'U' || t == 'O' || t == 'D' || t == 'C')
    {
        std::cout << "Switch to BANK MODE for these operations" << std::endl;
        return;
    }
    switch (t)
    {
    case 'W':
        ATM_W(bank);
        break;

    case 'M':
        ATM_M(bank);
        break;

    case 'F':
        ATM_F(bank);
        break;

    case 'B':
        ATM_B(bank);
        break;

    case 'X':
        ATM_X(bank);
        break;

    default:
        std::cout << "INVALID TRANSACTION TYPE\nTry Again.\n";
        break;
    }
}
