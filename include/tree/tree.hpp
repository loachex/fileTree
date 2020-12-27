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
    vector<folder *> stack;

    void build();
    void buildByStack();
    void destory();

public:
    int depth;
    int includeFolderNum;
    int includeFileNum;
    double _MemoryUsage;

    string rootPath;
    folder *rootFolder;

    Tree(string irootPath);
    ~Tree();

    void reload();
    void show();
    void flatten();
    void flitter();
};