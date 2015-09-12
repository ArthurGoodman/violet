#include "io.h"

#include <fstream>
#include <sstream>

void IO::print(string str) {
    cout << str;
}

void IO::println(string str) {
    cout << str << endl;
}

void IO::error(string message) {
    cout << "error: " << message << endl;
}

string IO::readFile(string fileName) {
    ifstream file(fileName.data());

    if (!file) {
        error("cannot open file '" + fileName + "'");
        return "";
    }

    ostringstream buffer;
    buffer << file.rdbuf();

    file.close();

    return buffer.str();
}

void IO::writeFile(string fileName, string data) {
    ofstream file(fileName.data());

    if (!file)
        error("cannot open file '" + fileName + "'");

    ostringstream buffer(data);
    file << buffer.str();

    file.close();
}
