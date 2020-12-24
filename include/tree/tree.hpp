#ifndef _H_FOLDER
#include "folder.hpp"
#define _H_FOLDER
#endif

using namespace std;

class Tree
{
private:
    folder *headFolder;

    void generate();

public:
    int depth;
    string headFolderPath;

    Tree(string Path);
    ~Tree();
};