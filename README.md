# QuantCast_Coding_Exercise

## Overview

Given a cookie log file in the following format:

```bat
cookie,timestamp
AtY0laUfhglK3lC7,2018-12-09T14:19:00+00:00
SAZuXPGUrfbcn5UA,2018-12-09T10:13:00+00:00
5UAVanZf6UtGyKVS,2018-12-09T07:25:00+00:00
AtY0laUfhglK3lC7,2018-12-09T06:19:00+00:00
SAZuXPGUrfbcn5UA,2018-12-08T22:03:00+00:00
4sMM2LxV07bPJzwf,2018-12-08T21:30:00+00:00
fbcn5UAVanZf6UtG,2018-12-08T09:30:00+00:00
4sMM2LxV07bPJzwf,2018-12-07T23:30:00+00:00
```

Wrote a command line program in C++ to process the log file and return the most active cookie for specified day.

## Usage

**NOTE** : It is better to compile the program using C++ 17 in order to avoid dependency warnings.
Command to compile the program:

```bat
g++ -std=c++17 -g most_active_cookie.cpp -o most_active_cookie
```

We can now run the program as follows:

```bat
./most_active_cookie cookie_log.csv -d 2018-12-09
```

## Implementation Details

* The code throws and error if the imput file is not present.
* Validations are present to check for the validity of the date as well as its UTC format.
* If multiple cookies are deemed to be most active for a specific day, we output all of them (No ordering is guaranteed for the results here)

# Tests

The test suite is written using gtest. It contains test cases for both valid and invalid inputs.

## Installing gtest in Mac

```bat
brew install cmake
cd ~/  
git clone https://github.com/google/googletest.git
cd googletest 
mkdir install 
cd install 
cmake ../  #creates a make file 
make #compiles Google Test
sudo make install #installs Google Testecho
"export CPLUS_INCLUDE_PATH=/usr/local/include" >> ~/.bash_profileecho
"export LIBRARY_PATH=/usr/local/lib" >> ~/.bash_profile
 source ~/.bash_profile 
```

## Running the tests.

```bat
g++ -std=c++17 test_suite.cpp -o test_suite -lgtest -lgtest_main -pthread
./test_suite
```

