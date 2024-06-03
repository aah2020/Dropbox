#include <gtest/gtest.h>
#include <dropboxServer.h>
#include <dropboxClient.h>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace dropbox;

/**
 * This framework for Dropbox integration test.
 */
class SyncTest: public ::testing::Test
{
public:
    SyncTest()
    {
        int returnCode = system("mkdir -p ~/test_srcDir"); 
        returnCode = system("mkdir -p ~/test_dstDir");
        returnCode = system("touch ~/test_srcDir/abc.txt"); 
        returnCode = system("touch ~/test_srcDir/abc.txt"); 
        returnCode = system("touch courrent_directory.txt"); 
    }

    void SetUp()
    {
        auto returnCode = system("../src/server/DropboxServer ~/test_srcDir/");
        // server->start();
        // std::this_thread::sleep_for(std::chrono::milliseconds(5));
        // code here will execute just before the test ensues
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
        // delete sb;
    }

    ~SyncTest()
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
    // DropboxServer* server = new DropboxServer("/home/kratos/test_dstDir/", "127.0.0.1", 8050);
    // DropboxClient* client = new DropboxClient("/home/kratos/test_srcDir/", "127.0.0.1", 8050);
};

TEST_F (SyncTest, AddFile)
{
    // auto returnCode = system("../src/client/DropboxClient ~/test_dstDir/");
}
