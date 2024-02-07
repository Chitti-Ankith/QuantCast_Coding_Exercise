#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>

using namespace std;

// Test fixture for testing the most active cookie function
class MostActiveCookieTest : public ::testing::Test {
protected:
    virtual void SetUp() override {
    }

    virtual void TearDown() override {
    }
};

TEST_F(MostActiveCookieTest, ValidationTests) {
    // Test for an invalid file.
    string invalid_file_name = "./invalid_file.csv";
    string expected_result = "Can't open file " + invalid_file_name + ". Please check if the file exists.\n";
    stringstream command;
    command << "./most_active_cookie " << invalid_file_name << " -d 2018-12-09 2>&1";

    FILE* pipe = popen(command.str().c_str(), "r");
    if (!pipe) {
        FAIL() << "popen failed";
    }
    char buffer[128];
    string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            result += buffer;
        }
    }
    pclose(pipe);
    EXPECT_EQ(result, expected_result);

    // Test for an invalid date.
    string file_name = "cookie_log.csv";
    expected_result = "Incorrect date format. Please use the UTC date format YYYY-MM-DD.\n";
    stringstream command_2;
    command_2 << "./most_active_cookie " << file_name << " -d 12-2-2028 2>&1";

    pipe = popen(command_2.str().c_str(), "r");
    if (!pipe) {
        FAIL() << "popen failed";
    }
    result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            result += buffer;
        }
    }
    pclose(pipe);
    EXPECT_EQ(result, expected_result);

    // Test for an invalid date format.
    expected_result = "Invalid date: 2018-12-32. Please input a valid date.\n";
    stringstream command_3;
    command_3 << "./most_active_cookie " << file_name << " -d 2018-12-32 2>&1";

    pipe = popen(command_3.str().c_str(), "r");
    if (!pipe) {
        FAIL() << "popen failed";
    }
    result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            result += buffer;
        }
    }
    pclose(pipe);
    EXPECT_EQ(result, expected_result);
}

TEST_F(MostActiveCookieTest, MostActiveCookieForDate) {
    // Test for a single active cookie.
    string expected = "AtY0laUfhglK3lC7";
    string test_file_name = "cookie_log.csv";

    // Run the program with the test log file and date
    stringstream command;
    command << "./most_active_cookie " << test_file_name << " -d 2018-12-09";
    FILE* pipe = popen(command.str().c_str(), "r");
    if (!pipe) {
        FAIL() << "popen failed";
    }

    char buffer[128];
    string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            result += buffer;
        }
    }
    pclose(pipe);

    // Check if the output matches the expected result
    EXPECT_EQ(result, "AtY0laUfhglK3lC7\n");

    // Test for multiple active cookies.
    stringstream command_2;
    command_2 << "./most_active_cookie " << test_file_name << " -d 2018-12-08";
    pipe = popen(command_2.str().c_str(), "r");
    if (!pipe) {
        FAIL() << "popen failed";
    }

    result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            result += buffer;
        }
    }
    pclose(pipe);
    // Since the order isn't guaranteed. Check if the string contains the expected results.
    EXPECT_TRUE(result.find("SAZuXPGUrfbcn5UA") != string::npos);
    EXPECT_TRUE(result.find("4sMM2LxV07bPJzwf") != string::npos);
    EXPECT_TRUE(result.find("fbcn5UAVanZf6UtG") != string::npos);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}