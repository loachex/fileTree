#ifndef _H_FOLDER
#include "folder.hpp"
#define _H_FOLDER
#endif

#ifndef _H_TIME
#include <time.h>
#define _H_TIME
#endif

using namespace std;

class Tree
{
private:
    void build();
    void destory();

public:
    int depth;
    int includeFolderNum;
    int includeFileNum;
    double _MemoryUsage;

    string rootPath;
    folder *rootFolder;

    vector<folder *> apflattenFolders; //展开的所有Folder*列表
    vector<file *> apflattenFiles;     //展开的所有file*列表

    Tree(string irootPath);
    ~Tree();

    void reload();
    void show();
    void flatten();
    void flitter();
};