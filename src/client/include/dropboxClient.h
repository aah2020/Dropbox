#pragma once

#include "clientSocket.h"
#include <string>

namespace dropbox
{
    class DropboxClient
    {
        private:
            std::string dir_name;
            std::string ip;
            int port;
            int runtime;
        public:
            /// @brief Dropbox client constructor
            /// @param name Path to the source folder
            /// @param ip IP address for the server
            /// @param port port number for the server
            /// @param runtime how long the client will run in seconds
            DropboxClient(std::string name, std::string ip, int port, int runtime)
                        : dir_name(name)
                        , ip(ip)
                        , port (port)
                        , runtime(runtime)
            {}

            /// @brief Start the client instance.
            void start();
    };
}