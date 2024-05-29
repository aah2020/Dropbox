
#include <fileop.h>
#include <experimental/filesystem>
#include <iostream>

using namespace dropbox;
namespace fs = std::experimental::filesystem;

bool dropbox::scan_dir(const std::string& path, json& dir_listing)
{
    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}

    
// bool dropbox::scan_dir(const std::string& dir_name, json& json)
// {
//     // for (const auto & entry : fs::directory_iterator(path))
// //     // std::cout << entry.path() << std::endl;
// //         
//     DIR *dirp;
//     if ((dirp = opendir(dir_name.c_str())) == NULL)
//     {
//         std::cerr << "couldn't open " << dir_name << std::endl;
//         return false;
//     }

//     json obj;
//     struct dirent *dp;
//     while((dp = readdir(dirp)) != nullptr)
//     {
//         std::string d_name = dp->d_name;
//         if(d_name != "." && d_name != "..")
//         {
//             json property;
//             struct stat statDat;
//             char full_path[MAX_PATH_LENGTH];
//             sprintf(full_path,"%s/%s/%s", get_current_dir_name(), dir_name.c_str(), d_name.c_str());
//             if (stat(full_path, &statDat) != 0)
//             {
//                 closedir(dirp);
//                 return false;
//             }
//             property["full_path"] = full_path;
//             property["mod_time"] = statDat.st_mtime;
//             property["access_time"] = statDat.st_atime;
//             property["size"] = statDat.st_size;
//             property["is_dir"] = (0 != (statDat.st_mode & 0x4000));
//             property["is_symlink"] = false;
//             property["sync_op"] = FileOP::ADD;
//             obj[d_name] = property;
//         }
//     }
//     closedir(dirp);

//     return obj;
// }
