#pragma once

#include "socket.h"

namespace dropbox
{
    class ClientSocket : public Socket
    {
    public:
        /// @brief ClientSocket constructor
        /// @param ip_addr IP address of the server
        /// @param port Destination port number
        ClientSocket(std::string ip_addr, int port);

        /// @brief Create a connecto to the server
        /// @return true on succes.
        bool create_connection();

        /// @brief Send data to the destination
        /// @param data Data to be sent
        /// @param len Length of the data in bytes
        /// @return Number of bytes to be transferred
        ssize_t send_to(const void* data, size_t len);

        /// @brief Receive data from the socket
        /// @param buffer Buffer to store received data
        /// @param buffer_size Length of the buffer
        /// @return Number of bytes received
        ssize_t receive_from(char buffer[], size_t buffer_size);
    };
}