
#include "fileop.h"
#include "log.hpp"
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <experimental/filesystem>

using namespace dropbox;
namespace fs = std::experimental::filesystem;

bool dropbox::path_exists(const std::string& path)
{
    struct stat sb;
    return (stat(path.c_str(), &sb) == 0);
}

std::ofstream dropbox::open(const std::string& file_name)
{
    std::ofstream ofs;
    try
    {
        ofs.open(file_name, std::ofstream::out | std::ofstream::app);
        if(ofs.is_open())
        {
            LOG(DEBUG) << "Opened " << file_name << " successfully." << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        LOG(ERROR) << e.what() << std::endl;
    }
    return ofs;
}

ssize_t dropbox::read_from(int socket, void* buffer, size_t nbytes)
{
    auto result = read(socket, buffer, nbytes);
    LOG(DEBUG) << "Read " << result << " bytes of data" << std::endl;
    return result;
}

bool dropbox::create_dir(const std::string& path)
{
    if (dropbox::path_exists(path))
    {
        LOG(DEBUG) << path << " exist." << std::endl;
        return true;
    }
    try
    {
        auto res = fs::create_directory(path);
        if (res)
        {
            LOG(DEBUG) << "Successfully created " << path << std::endl;
            return res;
        }
    }
    catch(const std::exception& e)
    {
        LOG(ERROR) << e.what() << std::endl;
    }
    return false;
}

std::uintmax_t dropbox::remove_all(const std::string& path)
{
    uintmax_t nitems = 0;
    if(path.empty())
    {
        LOG(ERROR) << "Empty path provided." << std::endl;
        return 0;
    }
    try
    {
        nitems = fs::remove_all(path);
        LOG(DEBUG) << "Deleted item(s) " << path << std::endl;
    }
    catch(const std::exception& e)
    {
        LOG(ERROR) << e.what() << std::endl;
        nitems = 0;
    }
    return nitems;
}

bool dropbox::scan_dir(const std::string& path, DirEntries& dir_entries)
{
    dir_entries.clear();
    if (!path_exists(path))
    {
        LOG(ERROR) << path << " does not exist!";
        return false;
    }

    for (const auto &entry : fs::recursive_directory_iterator(path))
    {
        auto path = entry.path();
        struct stat statDat;
        if (!stat(path.c_str(), &statDat))
        {
            struct FileStat entry;
            entry.full_path = path;
            entry.mod_time = statDat.st_mtime;
            entry.size = statDat.st_size;
            entry.is_dir = fs::is_directory(path.c_str());
            entry.sync_op = Opcode::CREATE;
            dir_entries[path.filename()] = entry;
        }
        else
        {
            LOG(ERROR) << "Cannot get stats of file " << path.c_str();
            return false;
        }
    }
    return true;
}

void dropbox::get_diff(DirEntries& cur_state, const DirEntries& prev_state)
{
    if(prev_state.empty())
    {
        return;
    }

    try
    {
        // Each entry on the old-list is compared with the current-list
        // and then required opcode is added for synchronization.
        for (auto& i : prev_state)
        {
            auto it = cur_state.find(i.first);
            if (it != cur_state.end())  // exists on both lists
            {
                it->second.sync_op = Opcode::SKIP; 
            }
            else // entry is not in the new list, perform delete operation
            {   
                auto new_entry = i.second;
                new_entry.sync_op = Opcode::DELETE;
                cur_state.insert(std::make_pair(i.first, new_entry));
            }
        }
    }
    catch(const std::exception& e)
    {
        LOG(ERROR) << e.what() << std::endl;
    }
}

std::string dropbox::read_file(const std::string& fname)
{
    std::fstream file;
    file.open(fname, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        LOG(ERROR) << "Cannot read file: " << fname << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read file-content and send it to server
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

void dropbox::display_entries(const DirEntries& entries)
{
    if (entries.empty())
    {
        LOG(WARNING) << "Empty directory list." << std::endl;
        return;
    }

    for (const auto& entry : entries)
    {
        LOG(DEBUG) << entry.first << " : " << entry.second.size << ", " << std::endl;
        switch(entry.second.sync_op)
        {
            case Opcode::SKIP:
                LOG(DEBUG) << " SKIP " << std::endl;
                break;
            case Opcode::CREATE:
                LOG(DEBUG) << " CREATE" << std::endl;
                break;
            case Opcode::DELETE:
                LOG(DEBUG) << " DELETE" << std::endl;
                break;
        }
    }
}
