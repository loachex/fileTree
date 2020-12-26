#ifndef _H_FOLDER
#include "folder.hpp"
#define _H_FOLDER
#endif

using namespace std;

class Tree
{
private:    
    string rootPath;
    int depth;    
    
    folder *rootFolder;

    void build();
    void destory();
public:
    Tree(string irootPath);
    ~Tree();

    void reload();
    void show();
    void flatten();
    void flitter();
};