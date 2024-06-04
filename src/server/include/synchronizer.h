#pragma once

#include <string>
#include <thread>
#include <chrono>

#include "fileop.h"
#include "json.hpp"
#include "log.hpp"

#define SEGMENT_SIZE 1024   // Maximum buffer length for reading/writing operation.

namespace dropbox
{
    using json = nlohmann::json;

    class Synchronizer
    {
        char buffer[SEGMENT_SIZE];

        public:
        void operator()(std::string dir_name, int socket, bool &quit)
        {
            std::ofstream ofs;
            std::string fname;
            while(!quit)
            {
                auto read_len = read_from(socket, buffer, SEGMENT_SIZE-1);
                LOG(DEBUG) << "\n\nData received:" << std::endl;
                LOG(DEBUG) << buffer << std::endl;
                if (read_len > 0)
                {
                    buffer[read_len] = '\0';
                    try
                    {
                        auto msg = json::parse(buffer);
                        for (const auto& entry : msg.items())
                        {
                            if (entry.value()["msg_type"] == MsgType::META_DATA)
                            {
                                std::string rel_path = entry.value()["full_path"];
                                fname = dir_name + rel_path;
                                if(entry.value()["sync_op"] == Opcode::DELETE)
                                {
                                    dropbox::remove_all(fname);
                                }
                                else
                                {
                                    if(entry.value()["is_dir"] == 1)
                                    {
                                        dropbox::create_dir(fname);
                                        continue;
                                    }
                                    else
                                    {
                                        if (!ofs.is_open())
                                        {
                                            LOG(DEBUG) << "Trying to create a file: " << fname << std::endl;
                                            ofs = open(fname);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                LOG(DEBUG) << "received file content" << std::endl;
                                if (ofs.is_open())
                                {
                                    ofs << entry.value()["content"];
                                    if (entry.value()["eof"] == 1) // Check the end of file flag.
                                    {
                                        ofs.close();
                                    }
                                }
                                else
                                {
                                    LOG(WARNING) << "Cannot write to " << fname << "; it is not opened." << std::endl;
                                }
                            }
                        }
                    }
                    catch(const std::exception& e)
                    {
                        LOG(ERROR) << e.what() << std::endl;
                    }
                }
                else
                {
                    LOG(WARNING) << "Closing server socket." << std::endl;
                    break;
                }
                memset(buffer, 0, sizeof buffer);
            }
        }
    };
}