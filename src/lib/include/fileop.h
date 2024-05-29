#pragma once

#include <json.hpp>

namespace dropbox
{
    using json = nlohmann::json;


    bool scan_dir(const std::string& path, json& dir_listing);
}