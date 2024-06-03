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
        public:
            /// @brief DropboxClient constructor.
            /// @param name Source directory name.
            DropboxClient(std::string name, std::string ip, int port)
                        : dir_name(name)
                        , ip(ip)
                        , port (port = 8050)
            {}

            /// @brief Start the client instance.
            void start();
    };
}