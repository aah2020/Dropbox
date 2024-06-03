#include <chrono>

#include "dropboxServer.h"
#include "synchronizer.h"
#include "log.hpp"

using namespace dropbox;

void DropboxServer::start()
{
    // Start the server
    auto server_sock = ServerSocket(ip, port);
    server_sock.bind_socket();
    server_sock.set_listen_set();

    // Wait for connection request
    auto connect_sock = server_sock.accept_connection();
    if(connect_sock <= 0)
    {
        LOG(ERROR) << "Error in accpeting client request." << std::endl;
        exit(EXIT_FAILURE);
    }
    LOG(INFO) << "Server receives connection request.\n";

    bool quit = false; // Flag to turn-off thread.
    Synchronizer synchronizer;
    std::thread t(std::ref(synchronizer), std::ref(dir_name), std::ref(connect_sock), std::ref(quit));

    std::this_thread::sleep_for (std::chrono::seconds(runtime));
    quit = true;
    (void)quit;

    t.join();
}