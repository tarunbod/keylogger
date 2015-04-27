
#ifndef _UTILS_H
#define _UTILS_H

#define _WIN32_WINNT 0x0500
#define FILEEXT ".txt"
#define DEBUG

#include <string>
#include <windows.h>
#include <stdlib.h>

using namespace std;

string intToString(int);
string getCurrDir();
string getSelfPath();
string dirBasename(string);

#endif /* _UTILS_H */
