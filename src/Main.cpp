#include <iostream>

#include <cpr/cpr.h>

int main()
{
    cpr::Response r = cpr::Get(cpr::Url{"https://www.facebook.com"});
    std::cerr <<r.status_code;
    return 0;
}