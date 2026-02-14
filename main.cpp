#include <iostream>
#include <string>
#include <random>

using namespace std;

string passgen(int level);

int main(int argc, char* argv[]) {
    random_device rd;

    if(argc < 2) {
        cerr << "Usage:" << endl;
        cerr << argv[0] << " -e [entropy level (1-100)]" << endl;
        cerr << "For help: " << argv[0] << " -h" << endl;
        return 1;
    }

    string opt = argv[1];

    if(opt == "-h") {
        cout << "To use this script, you must provide the necessary arguments for it." << endl;
        cout << "Example of use: " << argv[0] << " -e 10" << endl;
        cout << "The previous command provides a 10 of entropy level and generate your pass." << endl;
        return 0;
    }

    if(opt == "-e") {
        if(argc < 3) {
            cerr << "Missing entropy level." << endl;
            return 1;
        }

        try {
            int level = stoi(argv[2]);
            if(level < 1 || level > 100) {
                cerr << "Error: Entropy level must be between 1 and 100" << endl;
                return 1;
            }
            cout << "Generated pass: " << passgen(level) << endl;
        } catch(...) {
            cerr << "Invalid argument." << endl;
            return 1;
        }
    } else {
        cerr << "Invalid option." << endl;
        return 1;
    }

    return 0;
}

string passgen(int level) {
    const string valid_chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, valid_chars.size()-1);

    string result;
    int length = 10 + level;

    for(int i = 0; i < length; i++) {
        result += valid_chars[dis(gen)];
    }

    return result;
}
