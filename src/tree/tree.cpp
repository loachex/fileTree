#include "../../include/tree/tree.hpp"

using namespace std;

Tree::Tree(string irootPath)
{
    //属性值初始化
    depth = 0;
    includeFolderNum = 0;
    includeFileNum = 0;
    //根文件夹初始化
    rootPath = irootPath;
    rootFolder = new folder(rootPath, depth);
    rootFolder->pdirFolder = NULL;
    if (!rootFolder->_ok)
    {
        cout << "Please check the path of rootFolder." << endl;
        return;
    }
    //过滤器初始化
    useFliter = true;
    //构建
    build();
}
Tree::~Tree()
{
    destory();
}

void Tree::build()
{
    //防止根目录里没有子目录
    if (!rootFolder->subFoldersPath.size())
        return;
    //计时以及初始信息输出
    clock_t st, et;
    st = clock();
    cout << "Building fileTree of folder:'" << rootFolder->folderPath << "'" << endl;
    //前序遍历，构建树
    folder *curFolder = rootFolder; //工作本目录指针
    folder *cacheSubFolder;         //（用于添加至列表中的）暂存目录指针
    folder *curDirFolder;           //工作父目录指针
    file *cacheFile;                //暂存文件指针

    string curFileName;      //工作文件名称
    string curSubFolderName; //工作子目录名称
    string curFolderPath;    //工作本目录路径

    do
    {
        curFolderPath = curFolder->folderPath; //给工作本目录路径赋值，方便后续路径操作
        //构建文件
        while (curFolder->_unBuildFileNum)
        {
            //在工作本目录中有未构建的文件，则构建文件
            curFileName = curFolder->filesPath[curFolder->filesPath.size() - curFolder->_unBuildFileNum];
            cacheFile = new file(joinPath(curFolderPath.c_str(), curFileName.c_str())); //为了解决某个未知的BUG，这里用了c_str()
            curFolder->pfiles.push_back(cacheFile);
            curFolder->_unBuildFileNum--;
            //向展开文件指针列表里添加
            apflattenFiles.push_back(cacheFile);
        }
        //构建子目录
        if (curFolder->_depth && !curFolder->_unBuildSubFoldersNum)
        {
            //（向上）
            //当目录没有未构建的子目录，并且深度不为0时
            //将当前目录设为上级目录（向上）
            if (depth < curFolder->_depth)
                depth = curFolder->_depth;
            curFolder = curFolder->pdirFolder;
        }
        else
        {
            //（向右）
            //新建子目录，并将其添加至当前目录的子目录指针列表中
            curSubFolderName = curFolder->subFoldersPath[curFolder->subFoldersPath.size() - curFolder->_unBuildSubFoldersNum];
            cacheSubFolder = new folder(joinPath(curFolderPath, curSubFolderName), curFolder->_depth + 1);
            //若是坏目录，则跳过
            if (!cacheSubFolder->_ok)
            {
                --curFolder->_unBuildSubFoldersNum;
                delete cacheSubFolder;
                cacheSubFolder = NULL;
                continue;
            }
            //若是正常目录，则将暂存目录的父目录设置为工作目录
            cacheSubFolder->pdirFolder = curFolder;
            curFolder->psubFolders.push_back(cacheSubFolder);
            //工作目录的未构建子目录数-1
            --curFolder->_unBuildSubFoldersNum;
            //更新工作目录（向下）
            curFolder = cacheSubFolder;
            //添加至展开子目录指针列表
            apflattenFolders.push_back(cacheSubFolder);
        }

    } while (curFolder->_depth || curFolder->_unBuildSubFoldersNum);

    //计数
    includeFolderNum = apflattenFolders.size();
    includeFileNum = apflattenFiles.size();
    //构建迭代器
    freshIterEdge();
    seekIter(ITER, IterBegin);
    //构建路径-指针字典
    while (folderIter != folderIterEnd)
    {
        folderPathMap.insert(pair<string, folder *>((*folderIter)->folderPath, *folderIter));
        folderIter++;
    }
    while (fileIter != fileIterEnd)
    {
        filePathMap.insert(pair<string, file *>((*fileIter)->filePath, *fileIter));
        fileIter++;
    }
    seekIter(ITER, IterBegin);
    //构建过滤器
    fitFolderNum = apflattenFolders.size();
    fitFileNum = apflattenFiles.size();
    //结果报告
    et = clock();
    cout << "Build finished in " << to_string((double)(et - st) / CLOCKS_PER_SEC) << "s" << endl;
    cout << "include " << to_string(includeFolderNum) << " folders and " << to_string(includeFileNum) << " files" << endl;
}
void Tree::destory()
{

    vector<folder *>::iterator apFoldersIter = apflattenFolders.begin();
    vector<file *>::iterator apFilesIter = apflattenFiles.begin();

    for (; apFilesIter != apflattenFiles.end(); apFilesIter++)
    {
        delete (*apFilesIter);
        *apFilesIter = NULL;
    }
    for (; apFoldersIter != apflattenFolders.end(); apFoldersIter++)
    {
        delete (*apFoldersIter);
        *apFoldersIter = NULL;
    }
    delete rootFolder;
    rootFolder = NULL;

    vector<folder *>().swap(apflattenFolders);
    vector<file *>().swap(apflattenFiles);
    map<string, folder *>().swap(folderPathMap);
    map<string, file *>().swap(filePathMap);
}

void Tree::freshIterEdge()
{
    folderIterBegin = apflattenFolders.begin();
    folderIterEnd = apflattenFolders.end();
    fileIterBegin = apflattenFiles.begin();
    fileIterEnd = apflattenFiles.end();
}
void Tree::seekIter(int whichIter, int position)
{
    position %= 2;
    if (whichIter == FILEITER || whichIter == ITER)
    {
        if (position == IterBegin)
            fileIter = fileIterBegin;
        else
            fileIter = fileIterEnd;
    }
    if (whichIter == FOLDERITER || whichIter == ITER)
    {
        if (position == IterBegin)
            folderIter = folderIterBegin;
        else
            folderIter = folderIterEnd;
    }
}
file *Tree::nextFile(bool recycle = false)
{
    if (fileIter == fileIterEnd)
    {
        if (recycle && (*fileIter)->_fit) //防止出现死循环
        {
            seekIter(FILEITER, IterBegin);
        }
        else
        {
            return NULL;
        }
    }
    if (useFliter)
    {
        while (!((*fileIter)->_fit))
        {
            fileIter++;
            if (fileIter == fileIterEnd)
                return NULL;
        }
    }

    return *(fileIter++); //先return,再++（保证第一个数据也可以输出）
}
folder *Tree::nextFolder(bool recycle = false)
{
    if (folderIter == folderIterEnd)
    {
        if (recycle && (*folderIter)->_fit) //防止出现死循环
        {
            seekIter(FOLDERITER, IterBegin);
        }
        else
        {
            return NULL;
        }
    }
    if (useFliter)
    {
        while (!((*folderIter)->_fit))
        {
            folderIter++;
            if (folderIter == folderIterEnd)
                return NULL;
        }
    }

    return *(folderIter++); //先return,再++（保证第一个数据也可以输出）
}

void Tree::initFliter()
{
    //重置过滤结果
    seekIter(ITER, IterBegin);
    fitFileNum = apflattenFiles.size();
    fitFolderNum = apflattenFolders.size();
    //重置文件过滤结果
    for (; fileIter != fileIterEnd; fileIter++)
    {
        (*fileIter)->_fit = true;
    }
    //重置目录过滤结果
    for (; folderIter != folderIterEnd; folderIter++)
    {
        (*folderIter)->_fit = true;
    }
    seekIter(ITER, IterBegin);
}
void Tree::closeFliter()
{
    useFliter = false;
}
void Tree::openFilter()
{
    useFliter = true;
}
void Tree::fliter()
{
    initFliter();
    //过滤文件
    file *cachefile;
    while ((cachefile = nextFile(false)) != NULL)
    {
        if (!intFileFliter.RuleMap.empty())
            intFileFliter.fliter(cachefile);
        if (!doubleFileFliter.RuleMap.empty())
            doubleFileFliter.fliter(cachefile);
        if (!stringFileFliter.RuleMap.empty())
            stringFileFliter.fliter(cachefile);
        if (cachefile->_fit)
            fitFileNum++;
    }
    seekIter(ITER, IterBegin);

    //过滤目录
}

void Tree::buildfileTaskPool(int threadNum)
{
    seekIter(FILEITER, IterBegin);
    vector<file *> curvTask; //当前任务列表
    file *curfile;
    int taskNumPerV = fitFileNum / threadNum;
    int vNum = 0;

    while ((curfile = nextFile(false)) != NULL)
    {            
        curvTask.push_back(curfile);
        if (curvTask.size() >= taskNumPerV && vNum != threadNum - 1)
        {
            fileTaskPool.push_back(curvTask);
            curvTask.clear();
            ++vNum;
        }
    }
    fileTaskPool.push_back(curvTask);
}