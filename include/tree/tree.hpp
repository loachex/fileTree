#include <iostream>

#ifndef _H_VECTOR
#include <vector>
#define _H_VECTOR
#endif

#ifndef _H_DIRENT
#include <dirent.h>
#define _H_DIRENT
#endif

using namespace std;

typedef struct
{
    vector<string> *subFolder;
    vector<string> *files;

    string folderName;
    string dirPath;

    int _depth; //相对于顶级文件夹的深度
    int _uGSFN; //没有迭代的子文件夹数量(unGenerateSubFoldersNum)
} folder;

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