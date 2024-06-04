#include <iostream>

#include "dropboxServer.h"
#include "log.hpp"
#include "fileop.h"

using namespace std;

/// @brief Function to show usage information.
void show_usage()
{
    LOG(INFO) << "Usage: DropboxServer <PATH> <opt: ip addr> <opt: port>  <opt: rumtime>" << std::endl;
    LOG(INFO) << "Parameters:" << std::endl;
    LOG(INFO) << "  PATH    Complete path to synchronization directory" << std::endl;
    LOG(INFO) << "  IP ADDR IP address of the server" << std::endl;
    LOG(INFO) << "  PORT    Port number of the server" << std::endl;
    LOG(INFO) << "  RUNTIME Server runtime in seconds" << std::endl;
}

int main(int argc, char *argv[])
{
    // Start with the default config values
    std::string ip = "127.0.0.1";
    int port = 8050;
    int runtime = 60;
    // std::string dir_name = "/home/kratos/test_dstDir/";

    // Check dest-dir is provided or not.
    if (argc < 2)
    {
        show_usage();
        exit(EXIT_FAILURE);
    }

    // Get the directory name & check if it exists
    std::string dir_name = argv[1];
    if (!dropbox::path_exists(dir_name))
    {
        LOG(ERROR) << "File does not exists.";
        exit(EXIT_FAILURE);
    }

    if (argc == 5)
    {
        ip = argv[2];
        port = atoi(argv[3]);
        runtime = atoi(argv[4]);
    }

    dropbox::DropboxServer server(dir_name, ip, port, runtime);
    server.start();

    return 0;
}