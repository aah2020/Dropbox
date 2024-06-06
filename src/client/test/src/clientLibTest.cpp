#include <gtest/gtest.h>
#include <vector>
#include <dropboxClient.h>
#include "serverSocket.h"
#include <thread>


/**
 * A unit test to validate scan directory functionality
 * in the ClientLib.
 */
class ClientLibTest: public ::testing::Test
{
public:
    ClientLibTest()
    {
        // initialization code here
    }

    void SetUp()
    {
        // code here will execute just before the test ensues
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~ClientLibTest()
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

    void socket_process()
    {
        dropbox::ServerSocket ss("127.0.0.1", 8052);
        ss.bind_socket();
        ss.set_listen_set();
        auto connect_sock = ss.accept_connection();
    }

    void client_process()
    {
        dropbox::DropboxClient client("data", "127.0.0.1", 8052, 10);
        client.start();
    }

    std::thread server_thread;  // Server thread handle
    std::thread client_thread;  // Client thread handle
};

// This test start the client process, wait for while
// and then stop client process to verify the connection
// start and stop process functionality.
TEST_F (ClientLibTest, StartAndStopProcess)
{
    // Start the dropbox server instance
    try
    {
        server_thread = std::thread(std::bind(&ClientLibTest::socket_process, this));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::this_thread::sleep_for (std::chrono::seconds(1));


    // Start the dropbox client instance
    try
    {
        client_thread = std::thread(std::bind(&ClientLibTest::client_process, this));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    // Wait for the threads to finish
    client_thread.join();
    server_thread.join();
}
