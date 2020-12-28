#ifndef _H_FOLDER
#include "folder.hpp"
#endif

#ifndef _H_TIME
#include <time.h>
#define _H_TIME
#endif

#ifndef _H_STACK
#include <stack>
#define _H_STACK
#endif

using namespace std;

class Tree
{
private:
    /*完全构建目录，包括：
        1.基本信息
        2.展开的子目录指针列表
        3.展开的子文件指针列表
        4.目录以及文件之间的树结构
    */
    void build();

    /*销毁对象*/
    void destory();

public:
    int depth;            //树的深度
    int includeFolderNum; //包含的子目录数量
    int includeFileNum;   //包含的子文件数量
    double _MemoryUsage;  //内存占用

    string rootPath;    //根目录路径
    folder *rootFolder; //根目录指针

    vector<folder *> apflattenFolders; //展开的所有子目录指针列表
    vector<file *> apflattenFiles;     //展开的所有子文件指针列表

    Tree(string irootPath,int option);
    ~Tree();
};