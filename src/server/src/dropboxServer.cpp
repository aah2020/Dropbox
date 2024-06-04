#include <chrono>

#include "dropboxServer.h"
#include "synchronizer.h"
#include "log.hpp"

using namespace dropbox;

void DropboxServer::start()
{
    auto sink_cout = std::make_shared<AixLog::SinkCout>(AixLog::Severity::trace);
    auto sink_file = std::make_shared<AixLog::SinkFile>(AixLog::Severity::trace, "server.log");
    AixLog::Log::init({sink_cout, sink_file});

    LOG(DEBUG) << "params: " << dir_name << ", " << ip << ", " << port << std::endl;
    LOG(DEBUG) << "start server socket" << std::endl;
    // Start the server
    auto server_sock = ServerSocket(ip, port);

    server_sock.bind_socket();

    server_sock.set_listen_set();

    LOG(DEBUG) << "wait for client connection" << std::endl;
    try
    {
        // Wait for connection request
        auto connect_sock = server_sock.accept_connection();
        if(connect_sock <= 0)
        {
            LOG(ERROR) << "Error in accpeting client request." << std::endl;
            exit(EXIT_FAILURE);
        }
        LOG(INFO) << "Server receives connection request." << std::endl;

        LOG(DEBUG) << "starting synchronizer" << std::endl;
        bool quit = false; // Flag to turn-off thread.
        Synchronizer synchronizer;
        std::thread t(std::ref(synchronizer), std::ref(dir_name), std::ref(connect_sock), std::ref(quit));
        std::this_thread::sleep_for (std::chrono::seconds(runtime));
        quit = true;
        (void)quit;
        t.join();
    }
    catch(const std::exception& e)
    {
        LOG(ERROR) << e.what() << std::endl;
    }
}