#include "../../include/tree/path.hpp"

bool isFile(string Path)
{
    struct stat buffer;
    return (stat(Path.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
}

folder *initFolder(string Path, string upPath = ".")
{
    folder *f=new folder;

    f->folderPath=Path;
    f->upFolderPath=upPath;

    f->subFolders=new vector<folder*>;
    f->files=new vector<file*>;

    f->_depth=0;
    f->_unGenerateSubFoldersNum=f->subFolders->size();
}
void destoryFolder
bool isFolder(string Path)
{
    struct stat buffer;
    return (stat(Path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

void readFolder(string Path, folder &f)
{
    /*
    读取Path指向的文件夹
    给f的:
            subFolders;
            files;
    赋值
    */
    DIR *dir;
    struct dirent *ptr;

    dir = opendir(Path.c_str());
}