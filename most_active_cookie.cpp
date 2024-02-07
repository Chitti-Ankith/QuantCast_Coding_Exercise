#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>


using namespace std;

// Function to validate input file and date.
bool ValidateFileAndDate(const string& filename, const string& date) {
    // Check if file exists.
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Can't open file " << filename << ". Please check if the file exists." << endl;
        return false;
    }

    // Check if date is in UTC format.
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        cerr << "Incorrect date format. Please use the UTC date format YYYY-MM-DD." << endl;
        return false;
    }

    // Check if the date is valid.
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (month < 1 || month > 12 || day < 1 || day > 31) {
        cerr << "Invalid date: " << date << ". Please input a valid date." << endl;
        return false;
    }

    bool validate_date = true;
    if (month == 2) {
        // Check for leap year.
        if (day > 29) {
            validate_date = false;
        } else if (day == 29 && (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))) {
            validate_date = false;
        }
    } else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        validate_date = false;
    }

    if (!validate_date) {
        cerr << "Invalid date: " << date << ". Please input a valid date." << endl;
        return false;
    }

    return true;
}

// Function to split the string based on delimiter.
vector<string> Split(const string& s, const string& delimiter) {
    size_t start = 0, end, delim_len = delimiter.size();
    string token;
    vector<string> res;

    while ((end = s.find(delimiter, start)) != string::npos) {
        token = s.substr(start, end - start);
        start = end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(start));
    return res;
}

void MostActiveCookie(const string& filename, const string& input_date) {
    ifstream file(filename);
    unordered_map<string /* cookie */, int /* count */> cookie_count;

    string line;
    getline(file, line); // Ignore the first line containing the headers.

    while (getline(file, line)) {     // File validation has already been done.
        auto tokens = Split(line, ",");
        if (tokens.size() != 2) {
            cerr << "Invalid line found: " << line << ". Not processing this row." << endl;
            continue;
        }

        const string& cookie = tokens[0];
        const string& date_time = tokens[1];
        const string& date = date_time.substr(0, 10);
        // const string& time = date_time.substr(11, 8);
        if (date == input_date) {
            ++cookie_count[cookie];
        }
    }

    vector<string> max_count_cookies;
    int max_count = 0;

    // Find the most active cookies.
    for (const auto& iter : cookie_count) {
        const auto& cookie = iter.first;
        const auto& count = iter.second;
        if (count > max_count) {
            max_count = count;
            max_count_cookies.clear();
            max_count_cookies.push_back(cookie);
        } else if (count == max_count) {
            max_count_cookies.push_back(cookie);
        }
    }

    // Print the most active cookies.
    for (const auto& cookie : max_count_cookies) {
        cout << cookie << endl;
    }
}

int main(int argc, char* argv[]) {
    // Check the number of arguments and format.
    if (argc != 4 || static_cast<string>(argv[2]) != "-d") {
        cerr << "Incorrect Syntax!" << endl << "Usage: ./most_active_cookie <filename> -d <date>" << endl;
        return 1;
    }

    const string& filename = argv[1];
    const string& date = argv[3];

    // Validate the input file and date.
    if (!ValidateFileAndDate(filename, date)) {
        return 1;
    }

    // Find the most active cookies.
    MostActiveCookie(filename, date);

    return 0;
}