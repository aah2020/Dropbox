#include <iostream>
#include <thread>
#include <string>

#include "fileop.h"
#include "log.hpp"
#include "json.hpp"

#define SEGMENT_SIZE 1024   // Maximum buffer length for reading/writing operation.

namespace dropbox
{
    using json = nlohmann::json;

    class Synchronizer
    {
        private:
            ClientSocket socket;
            DirEntries cur_entries, prev_entries;

            std::string get_content(std::string fname)
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

            bool synchronize_dir(std::string dir_name, DirEntries &target_state)
            {
                try
                {
                    for (auto &entry: target_state)
                    {
                        json msg;
                        if(entry.second.sync_op != Opcode::SKIP)
                        {
                            // First send the meta data of the file
                            json meta;
                            meta["msg_type"] = MsgType::META_DATA;
                            meta["size"] = entry.second.size;
                            meta["is_dir"] = (entry.second.is_dir)? 1 : 0;
                            meta["sync_op"] = entry.second.sync_op;
                            meta["mod_time"] = entry.second.mod_time;
                            std::string rel_path = entry.second.full_path;
                            meta["full_path"] = rel_path.erase(0, dir_name.length());
                            msg[entry.first] = meta;

                            std::string data_sent = msg.dump();
                            socket.send_to(data_sent.c_str(), data_sent.length());
                            LOG(DEBUG) << "\n\nSending meta data:" << std::endl;
                            LOG(DEBUG) << data_sent.c_str() << std::endl;

                            if (entry.second.is_dir == false && (entry.second.sync_op != Opcode::DELETE))
                            {
                                // Then keep sending the actual content of the file.
                                json msg2;
                                json payload;
                                payload["msg_type"] = MsgType::PAYLOAD;
                                int tx_size = entry.second.size;
                                while (tx_size >= 0)
                                {
                                    payload["eof"] = (tx_size > (SEGMENT_SIZE-1)) ? 0 : 1;
                                    payload["content"] = dropbox::read_file(entry.second.full_path);
                                    msg2[entry.first] = payload;
                                    std::string buffer = msg2.dump();

                                    socket.send_to(buffer.c_str(), buffer.length());
                                    tx_size = tx_size - (SEGMENT_SIZE-1);
                                    LOG(DEBUG) << "\nSending payload:" << std::endl;
                                    LOG(DEBUG) << buffer.c_str() << std::endl;
                                }
                            }
                        }
                    }
                }
                catch(const std::exception& e)
                {
                    LOG(ERROR) << e.what() << std::endl;
                    return false;
                }
            }

        public:
            Synchronizer(ClientSocket socket) : socket(socket) {}

            void operator()(std::string dir_name, bool &quit)
            {
                while(!quit)
                {
                    // Scan source dir to get current state
                    scan_dir(dir_name, cur_entries);
                    display_entries(cur_entries);

                    // Compare with the old list and detect changes
                    get_diff(cur_entries, prev_entries);
                    display_entries(cur_entries);

                    // Synchronize remote directory
                    bool res = synchronize_dir(dir_name, cur_entries);

                    std::this_thread::sleep_for(std::chrono::seconds(10));
                    prev_entries = cur_entries;
                }
            }
    };
}