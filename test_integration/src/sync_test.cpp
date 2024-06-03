#include <gtest/gtest.h>
#include <dropboxServer.h>
#include <dropboxClient.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>

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
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    void server_process()
    {
        DropboxServer* server = new DropboxServer("/home/kratos/test_dstDir/", "127.0.0.1", 8050, 10);
    }

    void client_process()
    {
        DropboxClient* client = new DropboxClient("/home/kratos/test_srcDir/", "127.0.0.1", 8050, 10);
    }

    ~SyncTest()
    {
        // cleanup any pending stuff, but no exceptions allowed
    }
};

TEST_F (SyncTest, ClientServerCommunication)
{
    int quit = false;
    std::thread t1(std::bind(&SyncTest::server_process, this));
    std::this_thread::sleep_for (std::chrono::seconds(1));
    std::thread t2(std::bind(&SyncTest::client_process, this));
    std::this_thread::sleep_for (std::chrono::seconds(10));
    quit = true;
    (void)quit;

    t2.join();
    t1.join();
}
