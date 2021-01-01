#define _H_PATH

#include <iostream>

#ifndef _H_VECTOR
#include <vector>
#define _H_VECTOR
#endif

#ifndef _H_STRING
#include <string.h>
#define _H_STRING
#endif

#ifndef _H_SSTREAM
#include <sstream>
#define _H_SSTREAM
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

vector<string> split(string s, char c);

string dirPath(string path);

string joinPath(string path1, string path2);
string joinPath(string path1, char *path2);
string joinPath(char *path1, char *path2);
string joinPath(vector<string> paths);

string getFormat(string fileName); //获取文件格式（拓展名）（例：abc.txt->txt）

bool isFile(string Path);
bool isFolder(string Path);
