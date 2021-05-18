#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "languages.h"

using namespace std;

void ld(string arg) {
    string main_command = "ld " + arg;
    const char *command = main_command.c_str();
    system(command);
}

void print(string text) {
    cout << text << endl;
}

int main() {
    ifstream file;
    file.open("NewBuild");
    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            size_t p1, p2;

            if (((p1 = line.find('(')) == string::npos) ||
                ((p2 = line.find(')', p1+1)) == string::npos))
                cout << "invalid line" << line << endl;
            else {
                string fn = line.substr(0, p1);

                static const map<string, void (*)(string)> cargo_fn = { {"cargo", cargo} };
                static const map<string, void (*)(string)> gcc_fn = { {"gcc", gcc} };
                static const map<string, void (*)(string)> as_fn = { {"as", as} };
                static const map<string, void (*)(string)> ld_fn = { {"ld", ld} };
                static const map<string, void (*)(string)> print_fn = { {"print", print} };

                map<string, void (*)(string)>::const_iterator cargo_arg = cargo_fn.find(fn);
                map<string, void (*)(string)>::const_iterator gcc_arg = gcc_fn.find(fn);
                map<string, void (*)(string)>::const_iterator as_arg = as_fn.find(fn);
                map<string, void (*)(string)>::const_iterator ld_arg = ld_fn.find(fn);
                map<string, void (*)(string)>::const_iterator print_arg = print_fn.find(fn);

                if ((cargo_arg = cargo_fn.find(fn)) != cargo_fn.end()) {
                    if (((p1 = line.find('"', p1+1)) == string::npos) ||
                        ((p2 = line.find('"', p1+1)) == string::npos))
                        cout << "No string argument found in " << line << endl;
                    else
                        cargo_arg -> second(line.substr(p1+1, p2 - p1 -1));
                } else if ((gcc_arg = gcc_fn.find(fn)) != gcc_fn.end()) {
                    if (((p1 = line.find('"', p1 + 1)) == string::npos) ||
                        ((p2 = line.find('"', p1 + 1)) == string::npos))
                        cout << "No string argument found in " << line << endl;
                    else
                        gcc_arg -> second(line.substr(p1 + 1, p2 - p1 - 1));
                } else if ((as_arg = as_fn.find(fn)) != as_fn.end()) {
                    if (((p1 = line.find('"', p1 + 1)) == string::npos) ||
                        ((p2 = line.find('"', p1 + 1)) == string::npos))
                        cout << "No string argument found in " << line << endl;
                    else
                        as_arg -> second(line.substr(p1 + 1, p2 - p1 - 1));
                } else if ((ld_arg = ld_fn.find(fn)) != ld_fn.end()) {
                    if (((p1 = line.find('"', p1 + 1)) == string::npos) ||
                        ((p2 = line.find('"', p1 + 1)) == string::npos))
                        cout << "No string argument found in " << line << endl;
                    else
                        ld_arg -> second(line.substr(p1 + 1, p2 - p1 - 1));
                } else if ((print_arg = print_fn.find(fn)) != print_fn.end()) {
                    if (((p1 = line.find('"', p1 + 1)) == string::npos) ||
                        ((p2 = line.find('"', p1 + 1)) == string::npos))
                        cout << "No string argument found in " << line << endl;
                    else
                        print_arg -> second(line.substr(p1 + 1, p2 - p1 - 1));
                } else {
                    cout << "Unknown function " << fn << endl;
                }
            }
        }
    }

    file.close();
}
