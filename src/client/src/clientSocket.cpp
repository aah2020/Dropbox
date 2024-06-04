#include <iostream>
#include <chrono>
#include <unistd.h>

#include "clientSocket.h"
#include "log.hpp"

using namespace dropbox;

ClientSocket::ClientSocket(std::string ip_addr, int port) : Socket(ip_addr, port)
{}

void ClientSocket::create_connection()
{
    if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        LOG(ERROR) << "Connection attempt failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
    LOG(INFO) << "Connection Successfull." << std::endl;
}

ssize_t ClientSocket::send_to(const void* data, size_t len)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    auto bytes_sent = send(sock, data, len, 0);
    if (bytes_sent > 0)
    {
        LOG(INFO) << "Transmitted file Size "<< bytes_sent <<" Bytes." << std::endl;
    }
    else
    {
        LOG(ERROR) << "Failed to send data!" << std::endl;
    }
    return bytes_sent;
}

ssize_t ClientSocket::receive_from(char buffer[], size_t buffer_size)
{
    int bytes_recv = read(sock, buffer, buffer_size);
    return bytes_recv;
}