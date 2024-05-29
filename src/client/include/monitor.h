#include <iostream>
#include <thread>
#include <string>
#include <atomic>

// https://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php

namespace dropbox
{
    class Monitor
    {
        public:
        // Monitor() {}
        void operator()(std::string dir_name, bool &stop)
        {

            // Scan dir

            // Synchronizer


            while(true)
            {
                std::cout << "Scanning directory:" << "dir_name" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (stop == true)
                {
                    break;
                }
            }
        }
        void scanDir()
        {}
    };
}