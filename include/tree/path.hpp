#include <iostream>

#ifndef _H_VECTOR
#include <vector>
#define _H_VECTOR
#endif

#ifndef _H_DIRENT
#include <dirent.h>
#define _H_DIRENT
#endif

#ifndef _H_SYS_STAT
#include <sys/stat.h>
#define _H_SYS_STAT
#endif

using namespace std;

vector<string>split(string s,char c);

string dirName(string path);
string joinPath(string path1, string path2);
string joinPath(vector<string> paths);

string getFormat(string fileName);

bool isFile(string Path);
bool isFolder(string Path);
