#include "../../include/tree/tree.hpp"

Tree::Tree(string irootPath)
{
    rootPath = irootPath;
    depth = 0;
    build();
}

void Tree::build()
{
    //加载根文件夹
    rootFolder = new folder(rootPath, depth);
    //前序遍历，构建树
    folder *curFolder=rootFolder;
    folder *cacheSubFolder;
    folder *curDirFolder;
    file *cacheFile;

    string curFileName;
    string curSubFolderName;
    string curFolderPath;

    do
    {
        curFolderPath=curFolder->folderPath;
        //构建文件
        for(int unBuildFilesNum=curFolder->files.size();unBuildFilesNum;--unBuildFilesNum)
        {
            curFileName=curFolder->files[curFolder->files.size()-unBuildFilesNum];
            cacheFile=new file(joinPath(curFolderPath.c_str(),curFileName.c_str()),true);
            curFolder->pfiles.push_back(cacheFile);
        }
        //构建子文件夹 (前序遍历)
        if (curFolder->_depth && !curFolder->_unBuildSubFoldersNum)
        {
            curFolder=curFolder->dirFolder;
        }
        else
        {
            if(!rootFolder->subFolders.size())break;
            
            //新建子文件夹，并将其添加至当前文件夹的psubFolders中
            curSubFolderName=curFolder->subFolders[curFolder->subFolders.size() - curFolder->_unBuildSubFoldersNum];
            cacheSubFolder = new folder(joinPath(curFolderPath,curSubFolderName), curFolder->_depth + 1);
            curFolder->psubFolders.push_back(cacheSubFolder);
            //当前文件夹的未构建子文件夹数-1
            --curFolder->_unBuildSubFoldersNum;
        
            curFolder = cacheSubFolder;//更新当前文件夹
        }
      
    } while (curFolder->_depth || curFolder->_unBuildSubFoldersNum);
}
