#include <iostream>
// #include <thread>
// #include <string>
#include "monitor.h"
#include <functional>
#include <atomic>
#include <fileop.h>

using namespace dropbox;

void connect_to_server() {}

int main()
{
    std::cout << "Hello from client app!" << std::endl;

    // Get dir-name as an argument
    std::string dir_name = "src_dir";

    // TODO: Connect to server
    connect_to_server();

    // Start Monitoring
    std::string s = "Client thread starts";

    json dir_listing;
    dropbox::scan_dir("/home/kratos/pps/Dropbox/build/src", dir_listing);

    bool flag = false;
    dropbox::Monitor monitor;
    std::thread t(std::ref(monitor), "src_dir", std::ref(flag));
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Press enter to quit!" << std::endl;
    // std::cin.get() ;

    flag = true;
    t.join();


    return 0;
}