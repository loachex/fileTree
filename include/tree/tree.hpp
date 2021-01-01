#define _H_TREE

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

#ifndef _H_THREAD
#include <thread>
#define _H_THREAD
#endif

#ifndef _H_MUTEX
#include <mutex>
#define _H_MUTEX
#endif

using namespace std;

template <class T1>
struct fileArgs
{
    vector<file *> vf;
    T1 *result;
};

class Tree
{
private:
    //构建与析构
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

    //处理器操作

public:
    int depth;            //树的深度
    int includeFolderNum; //包含的子目录数量
    int includeFileNum;   //包含的子文件数量

    string rootPath;    //根目录路径
    folder *rootFolder; //根目录指针

    vector<folder *> apflattenFolders; //展开的所有子目录指针列表
    vector<file *> apflattenFiles;     //展开的所有子文件指针列表

    map<string, folder *> folderPathMap; //路径-目录指针 字典
    map<string, file *> filePathMap;     //路径-文件指针 字典

    vector<folder *>::iterator folderIter;      //展开的所有子目录指针列表迭代器
    vector<folder *>::iterator folderIterBegin; //展开的所有子目录指针列表迭代器:首端
    vector<folder *>::iterator folderIterEnd;   //展开的所有子目录指针列表迭代器：末端
    vector<file *>::iterator fileIter;          //展开的所有子文件指针列表迭代器
    vector<file *>::iterator fileIterBegin;     //展开的所有子文件指针列表迭代器：首端
    vector<file *>::iterator fileIterEnd;       //展开的所有子文件指针列表迭代器：末端

    bool useFliter;                      //过滤器开关
    int fitFileNum;                      //通过过滤的文件数量
    int fitFolderNum;                    //通过过滤的目录数量
    fileFliter<int> intFileFliter;       //文件int过滤器
    fileFliter<double> doubleFileFliter; //文件double过滤器
    fileFliter<string> stringFileFliter; //文件string过滤器

    vector<thread> threadPool;           //（简易的）线程池
    vector<vector<file *>> fileTaskPool; //文件任务池
    //构建与析构
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

    /*过滤器操作:操作类型为逻辑与，即三种过滤器都通过才设定为fit*/
    void initFliter();
    void closeFliter();
    void openFilter();
    void fliter();

    /*处理器操作*/
    //单线程
    template <class T1, class T2>
    void fileProcess(void (*func)(file *f, T1 args, T2 &result), T1 args, T2 &result)
    {
        file *curfile;
        while ((curfile = nextFile(false)) != NULL)
        {
            func(curfile, args, result);
        }
    }
    template <class T1>
    void fileProcess(void (*func)(file *f, T1 args), T1 args)
    {
        file *curfile;
        while ((curfile = nextFile(false)) != NULL)
        {
            func(curfile, args);
        }
    }
    template <class T1>
    void fileProcess(void (*func)(file *f, T1 &result), T1 &result)
    {
        file *curfile;
        while ((curfile = nextFile(false)) != NULL)
        {
            func(curfile, result);
        }
    }
    void fileProcess(void (*func)(file *f))
    {
        file *curfile;
        while ((curfile = nextFile(false)) != NULL)
        {
            func(curfile);
        }
    }

    //多线程
    void buildfileTaskPool(int threadNum);

    void MfileProcess(void (*func)(vector<file *> vf), int threadNum)
    {
        //！在func中一定对result加锁！
        buildfileTaskPool(threadNum);
        for (int fTPN = 0; fTPN < fileTaskPool.size(); fTPN++)
        {
            threadPool.push_back(thread(func, fileTaskPool[fTPN]));
            cout << "Thread:" << to_string(fTPN) << " Start.";
        }
        for (int tPN = 0; tPN < threadPool.size(); tPN++)
        {
            threadPool[tPN].join();
        }
    }
};