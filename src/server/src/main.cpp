#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <chrono>
 
// void independentThread() 
// {
//     std::cout << "Starting concurrent thread.\n";
//     std::this_thread::sleep_for(std::chrono::seconds(2));
//     std::cout << "Exiting concurrent thread.\n";
// }

// void threadCaller() 
// {
//     std::cout << "Starting thread caller.\n";
//     std::thread t(independentThread);
//     t.detach();
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     std::cout << "Exiting thread caller.\n";
// }
 
// int main() 
// {
//     threadCaller();
//     std::this_thread::sleep_for(std::chrono::seconds(5));
// }

void process (int sock) {
    std::cout << "Running " << std::endl;
    // call monitor after every-10 sec
}

void accept_loop (int listen_sock) {
    int new_sock;
    while ((new_sock = accept(listen_sock, 0, 0)) != -1) {
        std::thread t(process, new_sock);
    }
}

int main()
{
    std::cout << "Hello from server app!" << std::endl;
    return 0;
}