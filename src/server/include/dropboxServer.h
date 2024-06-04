#pragma once

#include "serverSocket.h"
#include <string>

namespace dropbox
{
    class DropboxServer
    {
        private:
            std::string dir_name;
            std::string ip;
            int port;
            int runtime;
        public:

            /// @brief Dropbox server constructor
            /// @param name Path to destination folder
            /// @param ip IP address for the listener
            /// @param port port number for the listener
            /// @param runtime how long the server will run in seconds
            DropboxServer(std::string name, std::string ip, int port, int runtime)
                        : dir_name(name)
                        , ip(ip)
                        , port (port)
                        , runtime (runtime)
            {}

            /// @brief Start the server instance.
            void start();
    };
}