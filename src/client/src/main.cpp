#include <iostream>
#include "log.hpp"
#include "dropboxClient.h"
#include "fileop.h"

/// @brief Function to show usage information.
void show_usage()
{
    LOG(INFO) << "Usage: DropboxClient <PATH> <opt: ip addr> <opt: port>  <opt: rumtime>" << std::endl;
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

    // Check for the additional user params
    if (argc == 5)
    {
        ip = argv[2];
        port = atoi(argv[3]);
        runtime = atoi(argv[4]);
    }

    LOG(INFO) << "Client config param:" << std::endl;
    LOG(INFO) << "Dir path:" << dir_name << std::endl;
    LOG(INFO) << "IP:" << ip << std::endl;
    LOG(INFO) << "Dir path:" << dir_name << std::endl;
    LOG(INFO) << "Runtime:" << runtime << std::endl;

    dropbox::DropboxClient client(dir_name, ip, port, runtime);
    client.start();

    return 0;
}