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

typedef struct
{
    string name;
    string format;

    bool show;

} file;

typedef struct folder
{
    vector<folder *> *subFolders;
    vector<file *> *files;

    string folderPath;
    string upFolderPath;

    int _depth;                   //相对于顶文件夹的深度
    int _unGenerateSubFoldersNum; //没有迭代的子folder数量
} folder;


string joinPath(string path1, string path2);
string joinPath(vector<string> paths);

bool isFile(string Path);

folder *initFolder(string Path, string upPath = ".");
void destoryFolder(folder *f);
bool isFolder(string Path);
void readFolder(string Path, folder &f);