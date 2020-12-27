#include "../../include/tree/tree.hpp"

Tree::Tree(string irootPath)
{
    rootPath = irootPath;
    depth = 0;
    build();
}

void Tree::build()
{

    cout << "构建树中..." << endl;

    //加载根文件夹
    rootFolder = new folder(rootPath, depth);
    rootFolder->dirFolder = NULL;
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
            
            ++includeFileNum;//文件数量计数
        }
        //构建子文件夹 (前序遍历)
        if (curFolder->_depth && !curFolder->_unBuildSubFoldersNum)
        {
            //当文件夹没有未构建的子文件夹，并且深度不为0时
            //将当前文件夹设为上级文件夹（向上）
            curFolder = curFolder->dirFolder;
        }
        else
        {
            if (!rootFolder->subFolders.size())
                break; //防止根文件夹里没有子文件夹，报错（似乎会影响性能）

            //新建子文件夹，并将其添加至当前文件夹的psubFolders中
            curSubFolderName = curFolder->subFolders[curFolder->subFolders.size() - curFolder->_unBuildSubFoldersNum];
            cacheSubFolder = new folder(joinPath(curFolderPath, curSubFolderName), curFolder->_depth + 1);
            cacheSubFolder->dirFolder = curFolder;
            curFolder->psubFolders.push_back(cacheSubFolder);
            //当前文件夹的未构建子文件夹数-1
            --curFolder->_unBuildSubFoldersNum;
            //更新当前文件夹（向下）
            curFolder = cacheSubFolder;

            ++includeFolderNum;//文件夹数量计数
        }

    } while (curFolder->_depth || curFolder->_unBuildSubFoldersNum);

    cout << "树" << this << "构建完毕" << endl;
}
