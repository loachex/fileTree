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

#ifndef _H_FLITER
#include "../../include/tree/fliter.hpp"
#endif

using namespace std;

class Tree
{
private:
    /*完全构建目录，包括：
        1.基本信息        
        2.目录以及文件之间的树结构
        3.展开的子目录指针列表
        4.展开的子文件指针列表
        5.迭代器
        6.路径-指针字典
    */
    void build();

    /*销毁对象*/
    void destory();

public:
    int depth;            //树的深度
    int includeFolderNum; //包含的子目录数量
    int includeFileNum;   //包含的子文件数量

    string rootPath;    //根目录路径
    folder *rootFolder; //根目录指针

    vector<folder *> apflattenFolders; //展开的所有子目录指针列表
    vector<file *> apflattenFiles;     //展开的所有子文件指针列表

    vector<folder *>::iterator folderIter;      //展开的所有子目录指针列表迭代器
    vector<folder *>::iterator folderIterBegin; //展开的所有子目录指针列表迭代器:首端
    vector<folder *>::iterator folderIterEnd;   //展开的所有子目录指针列表迭代器：末端
    vector<file *>::iterator fileIter;          //展开的所有子文件指针列表迭代器
    vector<file *>::iterator fileIterBegin;     //展开的所有子文件指针列表迭代器：首端
    vector<file *>::iterator fileIterEnd;       //展开的所有子文件指针列表迭代器：末端

    map<string, folder *> folderPathMap; //路径-目录指针 字典
    map<string, file *> filePathMap;     //路径-文件指针 字典

    fileFliter<int> intFileFliter;       //文件int过滤器
    fileFliter<double> doubleFileFliter; //文件double过滤器
    fileFliter<string> stringFileFliter; //文件string过滤器

    Tree(string irootPath);
    ~Tree();

    /*迭代器操作*/
#define ITER 0
#define FILEITER 1
#define FOLDERITER 2
#define IterBegin 0
#define IterEnd 1

    void freshIterEdge();                       //刷新迭代器的边界
    void seekIter(int whichIter, int position); //定位迭代器位置：whichIter
    file *nextFile(bool recycle);               //返回下一个文件指针，当达到末尾时自动循环或者停止
    folder *nextFolder(bool recycle);           //返回下一个文件夹指针，当达到末尾时自动循环或者停止

    /*过滤器操作:操作类型默认为逻辑与，即三种过滤器都通过才设定为fit*/
    void fliter();
};