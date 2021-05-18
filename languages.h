#ifndef NEW_BUILD_LANGUAGES_H
#define NEW_BUILD_LANGUAGES_H

#include <iostream>

using namespace std;

void cargo(string arg) {
    string main_command = "cargo " + arg;
    const char *command = main_command.c_str();
    system(command);
}

void gcc(string arg) {
    string main_command = "gcc " + arg;
    const char *command = main_command.c_str();
    system(command);
}

void as(string arg) {
    string main_command = "as " + arg;
    const char *command = main_command.c_str();
    system(command);
}

#endif //NEW_BUILD_LANGUAGES_H
