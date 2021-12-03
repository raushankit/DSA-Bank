#include "log.h"

log::log() : Time(""), action(""), mode("") {}

log::log(std::string action, std::string mode)
{
    this->action = action;
    this->mode = mode;
    time_t now = time(0);
    tm *z = localtime(&now);
    std::string t = "";
    if (z->tm_mday < 10)
        t += "0";
    t += std::to_string(z->tm_mday) + "/";
    if (z->tm_mon < 9)
        t += "0";
    t += std::to_string(z->tm_mon+1) + "/" + std::to_string(1900 + z->tm_year) + " ";
    int hour = (z->tm_hour + 11) % 12 + 1;
    if (hour < 10)
        t += "0";
    t += std::to_string(hour) + ":";
    if (z->tm_min < 10)
        t += "0";
    t += std::to_string(z->tm_min) + ":";
    if (z->tm_sec < 10)
        t += "0";
    t += std::to_string(z->tm_sec) + ":";
    t += (z->tm_hour >= 12) ? "PM" : "AM";
    Time = t;
}

log::log(std::string a, std::string b, std::string c)
{
    Time = a;
    mode = b;
    action = c;
}

log::log(const log &p)
{
    Time = p.Time;
    action = p.action;
    mode = p.mode;
}

log &log::operator=(const log &p)
{
    if (this != &p)
    {
        Time = p.Time;
        action = p.action;
        mode = p.mode;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const log &p)
{
    out << p.Time << " :: " << p.action << " by " << p.mode;
    return out;
}

log getlog(std::string s)
{
    std::stringstream ss(s);
    log p;
    ss >> p.action;
    ss >> p.Time;
    ss >> p.action;
    p.Time += " " + p.action;
    ss >> p.action;
    ss >> p.action;
    while (true)
    {
        ss >> p.mode;
        if (p.mode == "By:")
            break;
        p.action += " " + p.mode;
    }
    ss >> p.mode;
    return p;
}
