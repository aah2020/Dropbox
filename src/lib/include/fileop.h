#pragma once

#include <fstream>

namespace dropbox
{
    /// @brief List of enums defining the operation types.
    enum MsgType:int
    {
        META_DATA,  // Message contains info about a file
        PAYLOAD,    // Message contains actual file content
    };

    /// @brief List of enums defining the operation types.
    enum Opcode:int
    {
        SKIP,   // No operation needed to be performed
        CREATE, // Create a file or directory
        DELETE  // Delete a file or directory
    };

    /// @brief Chieck if path exists
    /// @param path Full path to check
    /// @return true if path pexists
    bool path_exists(const std::string& path);

    /// @brief Open a file.
    /// @param file_name Name of the file to open.
    /// @return true if open is successful.
    std::ofstream open(std::string file_name);

    /// @brief Read data from socket into buffer.
    /// @param socket Socket number to use for reading.
    /// @param buffer Buffer to store the data.
    /// @param nbytes Buffer length.
    /// @return Number of bytes read.
    ssize_t read_from(int socket, void* buffer, size_t nbytes);

    /// @brief Remove all items on the given path.
    /// @param path Full path to remove items.
    /// @return number of deleted items.
    std::uintmax_t remove_all(std::string path);

    /// @brief Create a directory on the given path.
    /// @param path Full path to create directory.
    /// @return true on success. false otherwise.
    bool create_dir(const std::string &path);
}