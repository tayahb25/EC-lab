#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

// Function declarations
double extractNumeric(string str); // Check if the string is a valid number
string trimSpaces(string str);     // Remove spaces at the start and end of the string

// A function to test the program with predefined cases
void runTests() {
    cout << "Running tests...\n";

    struct Test {
        string input;
        double expected;
    };

    Test testCases[] = {
        {"12.34", 12.34},
        {"  -123.45", -123.45},
        {"0.", 0.0},
        {"abc123", -999999.99},
        {"  12.34  ", 12.34},
        {"12.34.", -999999.99},
        {"+-12.34", -999999.99},
        {"", -999999.99},
        {"END", -999999.99}
    };

    for (const auto& test : testCases) {
        double result = extractNumeric(trimSpaces(test.input));
        if (result == test.expected) {
            cout << "Passed: \"" << test.input << "\"\n";
        } else {
            cout << "Failed: \"" << test.input << "\". Expected: " << test.expected
                 << ", Got: " << result << "\n";
        }
    }

    cout << "Tests done.\n";
}

int main() {
    runTests();

    string input;
    while (true) {
        cout << "Enter a string (or type 'END' to quit): ";
        getline(cin, input);

        input = trimSpaces(input);
        if (input == "END") {
            break;
        }

        double result = extractNumeric(input);
        if (result != -999999.99) {
            cout << "Valid number: " << fixed << setprecision(4) << result << "\n";
        } else {
            cout << "Invalid input. Try again.\n";
        }
    }

    return 0;
}

// Function to check if the string is a valid number and convert it
double extractNumeric(string str) {
    bool decimal = false;
    if (str.empty()) return -999999.99;

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        if ((c == '+' || c == '-') && i == 0) continue;
        if (c == '.' && !decimal) {
            decimal = true;
            continue;
        }
        if (!isdigit(c)) return -999999.99;
    }

    try {
        return stod(str);
    } catch (...) {
        return -999999.99;
    }
}

// Function to remove spaces from the beginning and end of the string
string trimSpaces(string str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    if (start == string::npos || end == string::npos) return "";
    return str.substr(start, end - start + 1);
}
