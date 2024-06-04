#include <gtest/gtest.h>
#include <dropboxServer.h>
#include <dropboxClient.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>
#include <fstream>
#include "fileop.h"

#include "testUtils.h"

using namespace dropbox;

/**
 * This framework for Dropbox integration test.
 * This test adds a single file in the source directory
 * and expect that file to be copied into destination
 * directory by dropbox application.
 */
class SingleFileAddition: public ::testing::Test
{
public:
    /// Class constructor.
    SingleFileAddition()
    {
        src_dir = "./test_srcDir/";
        dst_dir = "./test_dstDir/";
        src_file = src_dir + "test_file1.txt";
    }

    // Prepare the test setup by creating source and destination directories.
    void SetUp()
    {
        create_dir(src_dir);
        create_dir(dst_dir);
        std::ofstream ofs_src;
        ofs_src.open (src_file, std::ofstream::out | std::ofstream::app);
        ofs_src.close();
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    void server_process()
    {
        DropboxServer server(dst_dir, "127.0.0.1", 8050, 10);
        std::cerr << "Starting server" << std::endl;
        server.start();
    }

    void client_process()
    {
        DropboxClient client(src_dir, "127.0.0.1", 8050, 10);
        client.start();
    }

    ~SingleFileAddition()
    {
        // cleanup any pending stuff, but no exceptions allowed
        try
        {
            remove_all(src_dir);
            remove_all(dst_dir);
        }
        catch(const std::exception&)
        {}
    }

    std::string src_dir;        // Source directory for the client
    std::string dst_dir;        // Destination directory for the server
    std::string src_file;       // A sample file to be added during test
    std::thread server_thread;  // Server thread handle
    std::thread client_thread;  // Client thread handle
};

TEST_F (SingleFileAddition, SingleFile)
{
    // Start the dropbox server instance
    try
    {
        server_thread = std::thread(std::bind(&SingleFileAddition::server_process, this));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::this_thread::sleep_for (std::chrono::seconds(1));

    // Start the dropbox client instance
    try
    {
        client_thread = std::thread(std::bind(&SingleFileAddition::client_process, this));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    // Wait for the threads to finish
    client_thread.join();
    server_thread.join();

    // Verify the result
    DirEntries src_entries, dst_entries;
    bool is_success = scan_dir(src_dir, src_entries);
    EXPECT_TRUE(is_success);
    is_success = scan_dir(dst_dir, dst_entries);
    EXPECT_TRUE(is_success);

    // Verify that the destination folder contains desired file(s).
    for(const auto& i: src_entries)
    {
        ASSERT_TRUE(dst_entries.find(i.first) != dst_entries.end());
    }
}
