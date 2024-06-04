#include <chrono>

#include "dropboxClient.h"
#include "synchronizer.h"
#include "log.hpp"

using namespace dropbox;

void DropboxClient::start()
{
    auto sink_cout = std::make_shared<AixLog::SinkCout>(AixLog::Severity::trace);
    auto sink_file = std::make_shared<AixLog::SinkFile>(AixLog::Severity::trace, "client_start.log");
    AixLog::Log::init({sink_cout, sink_file});

    // Create client socket
    auto client_sock = ClientSocket(ip, port);

    // Create connection
    client_sock.create_connection();

    bool quit = false; // Flag to turn-off thread.
    Synchronizer synchronizer(client_sock);
    std::thread t(std::ref(synchronizer), std::ref(dir_name), std::ref(quit));

    std::this_thread::sleep_for (std::chrono::seconds(runtime));
    quit = true;
    (void)quit;

    // Wait for the thread to join
    t.join();

    // Close the socket connection
    client_sock.close_socket();
}