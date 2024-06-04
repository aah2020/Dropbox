#pragma once

#include <fstream>
#include <map>

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

    /// @brief Datastructure to keep file-stats.
    struct FileStat
    {
        std::string full_path;  // Absolute path of the file
        time_t mod_time;        // Last time of modification
        off_t size;             // Size of file
        bool is_dir;            // true if it is a directory
        Opcode sync_op;         // Type of syn-op to be performed
    };

    /// @brief List of files with corresponding stats
    typedef std::map<std::string, FileStat> DirEntries;

    /// @brief Chieck if path exists
    /// @param path Full path to check
    /// @return true if path pexists
    bool path_exists(const std::string& path);

    /// @brief Open a file.
    /// @param file_name Name of the file to open.
    /// @return true if open is successful.
    std::ofstream open(const std::string& file_name);

    /// @brief Read data from socket into buffer.
    /// @param socket Socket number to use for reading.
    /// @param buffer Buffer to store the data.
    /// @param nbytes Buffer length.
    /// @return Number of bytes read.
    ssize_t read_from(int socket, void* buffer, size_t nbytes);

    /// @brief Remove all items on the given path.
    /// @param path Full path to remove items.
    /// @return number of deleted items.
    std::uintmax_t remove_all(const std::string& path);

    /// @brief Create a directory on the given path.
    /// @param path Full path to create directory.
    /// @return true on success. false otherwise.
    bool create_dir(const std::string& path);

    /// @brief Scan the entries in a directory.
    /// @param path path to look into.
    /// @param dir_entries list of entries found in the path.
    /// @return true on successful operation.
    bool scan_dir(const std::string& path, DirEntries& dir_entries);

    /// @brief Find the difference between two different list.
    /// @param cur_state List of current directory entries.
    ///                  cur_state is updated after the operation is performed.
    /// @param prev_state List of old entries.
    /// @return true on success - cur_state is updated.
    void get_diff(DirEntries& cur_state, const DirEntries& prev_state);

    /// @brief Read the file content.
    /// @param fname Name of the file to be read.
    /// @return content of file as string.
    std::string read_file(const std::string& fname);

    /// @brief Display list of entries on the given data structure.
    /// @param entries list containing anumber of entries.
    void display_entries(const DirEntries& entries);
}