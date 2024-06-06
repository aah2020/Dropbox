#include <gtest/gtest.h>
#include <vector>
#include "fileop.h"

/**
 * A unit test to validate scan directory functionality
 * in the CommonLib.
 */
class CommonLibTest: public ::testing::Test
{
public:
    CommonLibTest()
    {}

    void SetUp()
    {}

    void TearDown()
    {}

    ~CommonLibTest()
    {}
};

/** 
 * this test scan a given folder containning a set of
 * files and directory. And then compare the 
 * scanned list with the expected list.
*/
TEST_F (CommonLibTest, DirectoryScan)
{

    // Initialize a vector containing expected
    // list of files in the test directory.
    std::vector<std::string> expected_list {
                "file_1.txt",
                "file_2.txt",
                "file_3.txt",
                "test_dir1",
                "test_dir2"
    };

    // Scan the target directory and get list of files
    dropbox::DirEntries entry_list;
    bool is_success = scan_dir("data", entry_list);

    // Expect the scan operation is succesful.
    EXPECT_TRUE(is_success);

    // First compared that expect and actual file counts are same.
    EXPECT_EQ(expected_list.size(), entry_list.size());

    // Now compare the name of each entry.
    int ctr = 0;
    for(const auto& i: entry_list)
    {
        EXPECT_EQ(expected_list[ctr], i.first);
        ctr++;
    }
}
