#include <iostream>

#ifndef _H_DIRENT
#include <dirent.h>
#define _H_DIRENT
#endif

using namespace std;

typedef struct
{
    vector* subFolder;
    vector* files;
    
    int depth;
    int _uGSFN;//没有迭代的子文件夹数量(unGenerateSubFoldersNum)
}folder

class tree
{
    private:
        
    