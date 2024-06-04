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
 * This test adds multilpe files in the source directory
 * and expect that file to be copied into destination
 * directory by dropbox application.
 */
class FileDeletion: public ::testing::Test
{
public:
    /// Class constructor.
    FileDeletion()
    {
        src_dir = "./test_srcDir/";
        dst_dir = "./test_dstDir/";
    }

    // Prepare the test setup by creating source and destination directories.
    void SetUp()
    {
        create_dir(src_dir);
        create_dir(dst_dir);
        system("pwd");
        system("cp -r ../../test_integration/data/test_srcDir/*.txt ./test_srcDir/");
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    void server_process()
    {
        DropboxServer server(dst_dir, "127.0.0.1", 8054, 50);
        std::cerr << "Starting server" << std::endl;
        server.start();
    }

    void client_process()
    {
        DropboxClient client(src_dir, "127.0.0.1", 8054, 50);
        client.start();
    }

    ~FileDeletion()
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
    std::thread server_thread;  // Server thread handle
    std::thread client_thread;  // Client thread handle
};

TEST_F (FileDeletion, FileDelete)
{
    // Start the dropbox server instance
    try
    {
        server_thread = std::thread(std::bind(&FileDeletion::server_process, this));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::this_thread::sleep_for (std::chrono::seconds(1));

    // Start the dropbox client instance
    try
    {
        client_thread = std::thread(std::bind(&FileDeletion::client_process, this));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    // Wait for a while for initial syncup
    std::this_thread::sleep_for (std::chrono::seconds(20));

    // Now delete the file in Source Directory
    system("rm ./test_srcDir/file1.txt");

    // Wait for a while for next syncup
    std::this_thread::sleep_for (std::chrono::seconds(20));

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
        std::cerr << "Searching for " << i.first << std::endl;
        ASSERT_TRUE(dst_entries.find(i.first) != dst_entries.end());
    }
}
