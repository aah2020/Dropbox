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
        public:
            /// @brief DropboxServer constructor.
            /// @param name destination path name.
            DropboxServer(std::string name, std::string ip, int port)
                        : dir_name(name)
                        , ip(ip)
                        , port (port = 8050)
            {}

            /// @brief Start the server instance.
            void start();
    };
}