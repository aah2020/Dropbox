#include <chrono>

#include "dropboxClient.h"
#include "synchronizer.h"
#include "log.hpp"

using namespace dropbox;

void DropboxClient::start()
{
    // Start the server
    auto client_sock = ClientSocket(ip, port);

    // Create connection
    client_sock.create_connection();

    bool quit = false; // Flag to turn-off thread.
    Synchronizer synchronizer(client_sock);
    std::thread t(std::ref(synchronizer), std::ref(dir_name), std::ref(quit));

    std::this_thread::sleep_for (std::chrono::seconds(runtime));
    quit = true;
    (void)quit;

    t.join();
}