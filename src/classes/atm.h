#ifndef __ATM__
#define __ATM__
#include "log.h"
#include <vector>

class ATM
{
public:
    ATM();
    ATM(std::string);
    std::string getID();
    void addlog(log);
    friend std::ostream &operator<<(std::ostream &, const ATM &);
    friend std::ostream &operator<<(std::ostream &, const backup &);

private:
    std::string ATMID;
    std::vector<log> z;

    friend void load();
};

#endif
