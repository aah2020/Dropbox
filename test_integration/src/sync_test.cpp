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

using namespace dropbox;

/**
 * This framework for Dropbox integration test.
 */
class SyncTest: public ::testing::Test
{
public:
    SyncTest()
    {
    }

    void SetUp()
    {
        create_dir("./test_srcDir/");
        create_dir("./test_dstDir/");
        std::ofstream ofs_src;
        ofs_src.open ("./test_srcDir/test.txt", std::ofstream::out | std::ofstream::app);
        ofs_src.close();
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    void server_process()
    {
        DropboxServer server("./test_dstDir/", "127.0.0.1", 8050, 10);
        std::cerr << "Starting server" << std::endl;
        server.start();
    }

    void client_process()
    {
        DropboxClient client("./test_srcDir/", "127.0.0.1", 8050, 10);
        client.start();
    }

    ~SyncTest()
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

        std::thread t1;
        std::thread t2;
};

TEST_F (SyncTest, SingleFile)
{
    try
    {
        t1 = std::thread(std::bind(&SyncTest::server_process, this));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::this_thread::sleep_for (std::chrono::seconds(1));

    try
    {
        t2 = std::thread(std::bind(&SyncTest::client_process, this));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    t2.join();
    t1.join();
}
