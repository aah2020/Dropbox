
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

std::ofstream dropbox::open(std::string file_name)
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

bool dropbox::create_dir(const std::string &path)
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

std::uintmax_t dropbox::remove_all(std::string path)
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
