#include "atm.h"

ATM::ATM() : ATMID("") {}

ATM::ATM(std::string s)
{
    ATMID = s;
    z.clear();
}

std::ostream &operator<<(std::ostream &out, const ATM &p)
{
    out << "ATMID : " << p.ATMID << std::endl;
    for (auto i : p.z)
    {
        out << i << std::endl;
    }
    return out;
}

std::string ATM::getID()
{
    return ATMID;
}

void ATM::addlog(log p)
{
    z.push_back(p);
}
