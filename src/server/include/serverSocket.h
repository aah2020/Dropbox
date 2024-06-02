#pragma once

#include "socket.h"

namespace dropbox
{
    class ServerSocket : public Socket
    {
        public:
            /// @brief ServerSocket constructor
            /// @param ip_addr IP address of the listener
            /// @param port Listening port number
            ServerSocket(std::string ip_addr, int port);

            /// @brief Bind the socket
            void bind_socket();

            /// @brief Listen to the socket
            void set_listen_set();

            /// @brief Accept any incoming request
            /// @return Returns socket_id
            int accept_connection();

            /// @brief Send data to the destination
            /// @param socket_dp Socket to be used for data transfer
            /// @param data Data to be sent
            /// @param len Length of the data in bytes
            /// @return Number of bytes to be transferred
            int send_to(int socket_dp, const void* data, size_t len);

            /// @brief Receive data from the socket
            /// @param socket_dp Socket to receive data
            /// @param buffer Buffer to store received data
            /// @param buffer_size Length of the buffer
            /// @return Number of bytes received
            ssize_t receive_from(int socket_dp, void *buffer, size_t buffer_size);
    };
}