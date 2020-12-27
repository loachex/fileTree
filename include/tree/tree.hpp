#ifndef _H_FOLDER
#include "folder.hpp"
#define _H_FOLDER
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
    string rootPath;
    folder *rootFolder;

    Tree(string irootPath);
    ~Tree();

    void reload();
    void show();
    void flatten();
    void flitter();
};