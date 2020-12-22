#include "../../include/tree/tree.hpp"

/*----------class file----------*/
file::file(string name, bool show = true)
{
    name = name;
    format = getFormat(name);
    _show = show;

#ifndef NDEBUG
    cout << "创建file实例：" << this << endl;
#endif
}
file::~file()
{
#ifndef NDEBUG
    cout << "销毁file实例：" << this << endl;
#endif
}

/*----------class folder----------*/
folder::folder(string Path, string upPath, int depth)
{
    
    folderPath = Path;
    upFolderPath = upPath;

    subFolders = new vector<folder *>;
    files = new vector<file *>;

    _depth = depth;
    _unGenerateSubFoldersNum = subFolders->size();

#ifndef NDEBUG
    cout << "创建folder实例：" << this << endl;
#endif
}

folder::~folder()
{
    for (int fn = 0; fn < files->size(); ++fn)
    {
        delete (*files)[fn];
    }
    delete files;
    delete subFolders;

#ifndef NDEBUG
    cout << "销毁folder实例：" << this << endl;
#endif
}

void folder::read()
{
    DIR *dir;
    struct dirent *ptr;

    char *curfileName;
    string scurfileName;
    while((ptr==readdir(dir))!=NULL)
    {
        curfileName=ptr->d_name;
        scurfileName=curfileName;

        if(curfileName[0]=='.')continue;
        


    }
}