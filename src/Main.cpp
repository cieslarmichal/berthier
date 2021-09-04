#include <cstdint>
#include <iostream>
#include <vector>

#include <cpr/cpr.h>

int main()
{
    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::client client{mongocxx::uri{}};

    cpr::Response r = cpr::Get(cpr::Url{"https://www.facebook.com"});
    std::cerr <<r.status_code;
    return 0;
}