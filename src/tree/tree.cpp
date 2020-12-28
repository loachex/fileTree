#include "../../include/tree/tree.hpp"

using namespace std;

Tree::Tree(string irootPath)
{
    depth = 0;
    includeFolderNum=0;
    includeFileNum=0;
    _MemoryUsage=0.;

    rootPath = irootPath;
    rootFolder = new folder(rootPath, depth);
    rootFolder->dirFolder = NULL;

    
    //构建
    build();
}
Tree::~Tree()
{
    destory();
}

void Tree::build()
{
#ifdef DEBUG
    clock_t st, et;

    st = clock();
#endif
    cout << "Building Tree of folder: " << rootFolder->folderName << endl;
    //前序遍历，构建树
    folder *curFolder = rootFolder;
    folder *cacheSubFolder;
    folder *curDirFolder;
    file *cacheFile;

    string curFileName;
    string curSubFolderName;
    string curFolderPath;

    do
    {
        curFolderPath = curFolder->folderPath;
        //构建文件
        while (curFolder->_unBuildFileNum)
        {
            curFileName = curFolder->files[curFolder->files.size() - curFolder->_unBuildFileNum];
            cacheFile = new file(joinPath(curFolderPath.c_str(), curFileName.c_str()), true); //为了解决某个未知的BUG，这里用了c_str()
            curFolder->pfiles.push_back(cacheFile);
            curFolder->_unBuildFileNum--;

            apflattenFiles.push_back(cacheFile); //向展开文件指针列表里添加

            ++includeFileNum;                  //文件数量计数
            //cout<<"File Num:"<<to_string(includeFileNum)<<endl;
            _MemoryUsage += sizeof(*cacheFile); //内存用量计数
        }
        //构建子文件夹 (前序遍历)
        if (curFolder->_depth && !curFolder->_unBuildSubFoldersNum)
        {
            //当文件夹没有未构建的子文件夹，并且深度不为0时
            //将当前文件夹设为上级文件夹（向上）
            if (depth < curFolder->_depth)
                depth = curFolder->_depth;
            curFolder = curFolder->dirFolder;
        }
        else
        {
            if (!rootFolder->subFolders.size())
                break; //防止根文件夹里没有子文件夹，报错（似乎会影响性能）

            //新建子文件夹，并将其添加至当前文件夹的psubFolders中
            curSubFolderName = curFolder->subFolders[curFolder->subFolders.size() - curFolder->_unBuildSubFoldersNum];
            cacheSubFolder = new folder(joinPath(curFolderPath, curSubFolderName), curFolder->_depth + 1);
            if(!cacheSubFolder->_ok)//若是坏文件夹，则跳过
            {
                --curFolder->_unBuildSubFoldersNum;
                continue;
                //也许会造成内存泄露？
            }

            cacheSubFolder->dirFolder = curFolder;
            curFolder->psubFolders.push_back(cacheSubFolder);
            //当前文件夹的未构建子文件夹数-1
            --curFolder->_unBuildSubFoldersNum;
            //更新当前文件夹（向下）
            curFolder = cacheSubFolder;

            apflattenFolders.push_back(cacheSubFolder); //向展开文件夹指针列表中添加

            ++includeFolderNum;                     //文件夹数量计数
            //cout<<"Folder Num:"<<to_string(includeFolderNum)<<endl;
            _MemoryUsage += sizeof(*cacheSubFolder); //内存用量计数
        }

    } while (curFolder->_depth || curFolder->_unBuildSubFoldersNum);

    cout << "include " << to_string(includeFolderNum) << " folders and " << to_string(includeFileNum) << " files" << endl;
    cout << "Memory Usage:" << to_string(_MemoryUsage / 1024) << " KB" << endl;

#ifdef DEBUG
    et = clock();
    cout << "创建Tree实例：" << this << ",cost:" << to_string((double)(et - st) / CLOCKS_PER_SEC) << " s" << endl;
#endif
}
void Tree::destory()
{
    
    vector<folder *>::iterator apFoldersIter = apflattenFolders.begin();
    vector<file *>::iterator apFilesIter = apflattenFiles.begin();

    for (; apFilesIter != apflattenFiles.end(); apFilesIter++)
    {
        delete (*apFilesIter);
        *apFilesIter=NULL;
    }
    for (; apFoldersIter != apflattenFolders.end(); apFoldersIter++)
    {
        delete (*apFoldersIter);
        *apFoldersIter=NULL;
    }
    delete rootFolder;
    rootFolder=NULL;

    vector<folder *>().swap(apflattenFolders);
    vector<file *>().swap(apflattenFiles);

}