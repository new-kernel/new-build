#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

void cargo(string arg) {
    string main_command = "cargo " + arg;
    const char *command = main_command.c_str();
    system(command);
}

int main(int argc, char *argv[]) {
    ifstream file;
    file.open(argv[1]);
    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            size_t p1, p2;

            if (((p1 = line.find('(')) == string::npos) ||
                ((p2 = line.find(')', p1+1)) == string::npos))
                cout << "invalid line" << line << endl;
            else {
                string fn = line.substr(0, p1);

                static const map<string, void (*)(string)> stringarg = { {"cargo", cargo} };

                map<string, void (*)(string)>::const_iterator itstr = stringarg.find(fn);

                if ((itstr = stringarg.find(fn)) != stringarg.end()) {
                    if (((p1 = line.find('"', p1+1)) == string::npos) ||
                        ((p2 = line.find('"', p1+1)) == string::npos))
                        cout << "No string argument found in " << line << endl;
                    else
                        itstr->second(line.substr(p1+1, p2 - p1 -1));
                }
                else
                    cout << "Unknown function " << fn << endl;
            }
        }
    }

    file.close();
}
