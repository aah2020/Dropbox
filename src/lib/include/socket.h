#pragma once

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace dropbox
{
    class Socket
    {
        private:
            std::string ip_addr;
            int port;

        protected:
            int sock;
            int address_length;
            struct sockaddr_in sock_addr;

        public:
            Socket(const std::string& ip_addr, int port);
            void close_socket();
    };
} // End of namespace dropbox