#ifndef IO_H
#define IO_H

#include <string>
#include <iostream>
using namespace std;

class IO {
public:
    static void print(string str);
    static void println(string str);

    template <typename T>
    static void scan(T &var);

    static void error(string message);

    static string readFile(string fileName);
    static void writeFile(string fileName, string data);
};

template <typename T>
void IO::scan(T &var) {
    cin >> var;
}

#endif // IO_H
