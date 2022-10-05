#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

#include "factory.hpp"

using LoggerCreator = std::function<std::unique_ptr<Logger>()>;

using namespace std;

class Service
{
    LoggerCreator creator_;
    bool is_started_ = false;

public:
    Service(LoggerCreator creator)
        : creator_(creator)
    {
    }

    Service(const Service&) = delete;
    Service& operator=(const Service&) = delete;

    void run()
    {
        unique_ptr<Logger> logger = creator_();
        if (!is_started_)
        {
            start();
            logger->log("Service has been started...");
        }
        process_requests();
        logger->log("Service has processed all requests...");
    }

protected:
    virtual void start() {}
    virtual void process_requests() {}
};

using LoggerFactory = std::unordered_map<std::string, LoggerCreator>;

int main()
{
    LoggerFactory logger_factory;
    logger_factory.insert(make_pair("ConsoleLogger", &make_unique<ConsoleLogger>));
    logger_factory.insert(make_pair("FileLogger", []{ return make_unique<FileLogger>("data.log"); }));
    logger_factory.insert(make_pair("DbLogger", &make_unique<DbLogger>));

    Service srv(logger_factory.at("DbLogger"));
    srv.run();
}
