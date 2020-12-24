#include "../../include/tree/folder.hpp"

folder::folder(string Path, int depth)
{

    folderPath = Path;

    _depth = depth;
    _unGenerateSubFoldersNum = 0;
    read();

#ifdef DEBUG
    cout << "创建folder实例：" << this << endl;
#endif
}

folder::~folder()
{
    vector<string>().swap(files);
    vector<string>().swap(subFolders);

#ifdef DEBUG
    cout << "销毁folder实例：" << this << endl;
#endif
}

void folder::read()
{
    DIR *dir;
    struct dirent *ptr;

    char *curTargetName;
    string scurTargetName;
    string curTargetPath;

    dir = opendir(folderPath.c_str());
    while ((ptr = readdir(dir)) != NULL)
    {
        curTargetName = ptr->d_name;
        if (curTargetName[0] == '.')
            continue;
        curTargetPath = joinPath(folderPath, curTargetName);

        if (isFolder(curTargetPath))
            subFolders.push_back(curTargetName);
        else
            files.push_back(curTargetName);
    }
}

void folder::show()
{
    cout << "Folder:" << folderPath << endl;
    cout << "Content:" << to_string(subFolders.size()) << " folders and " << to_string(files.size()) << " files" << endl;

    string space7dot1 = "       -";
    string space7dot2 = "       --";

    for (int subFolderNum = 0; subFolderNum < subFolders.size(); ++subFolderNum)
    {
        cout << space7dot1 + subFolders[subFolderNum] << endl;
    }
    for (int fileNum = 0; fileNum < files.size(); ++fileNum)
    {
        cout << space7dot2 + files[fileNum] << endl;
    }
}