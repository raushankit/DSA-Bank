#ifndef __LOG__
#define __LOG__
#include <iostream>
#include <sstream>
#include <ctime>

class backup;

class log
{
public:
    log();
    log(std::string, std::string);
    log(std::string, std::string, std::string);
    log(const log &);
    log &operator=(const log &);
    friend std::ostream &operator<<(std::ostream &, const log &);
    friend std::ostream &operator<<(std::ostream &, const backup &);
    friend log getlog(std::string);

private:
    std::string Time;
    std::string action;
    std::string mode;
};

log getlog(std::string);

#endif
