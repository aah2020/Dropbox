#include <iostream>

#include "dropboxServer.h"
#include "log.hpp"
#include "fileop.h"

using namespace std;

/// @brief Function to show usage information.
void show_usage()
{
    LOG(INFO) << "Usage: DropboxServer <PATH>" << std::endl;
    LOG(INFO) << "Parameters:" << std::endl;
    LOG(INFO) << "  PATH    Complete path to synchronization directory" << std::endl;
}

int main(int argc, char *argv[])
{
    AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::info);

    // Initialize config-params with default values
    std::string dir_name = "/home/kratos/dest_dir";
    std::string ip = "127.0.0.1";
    int port = 8050;

    // Check dest-dir is provided or not.
    if (argc < 2)
    {
        show_usage();
        exit(EXIT_FAILURE);
    }

    // Get the directory name & check if it exists
    // dir_name = argv[1];
    if (!dropbox::path_exists(dir_name))
    {
        LOG(ERROR) << "File does not exists.";
        exit(EXIT_FAILURE);
    }

    // // Start the server
    // dropbox::ServerSocket s;
    // s.bind_socket();
    // s.set_listen_set();

    // // Wait for client connection
    // auto client_dp = s.accept_connection();

    dropbox::DropboxServer server(dir_name, ip, port);
    server.start();
}