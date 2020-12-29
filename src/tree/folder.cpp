#include "../../include/tree/folder.hpp"

folder::folder(string Path, int depth)
{
    includeFilesNum = 0;
    includeSubFoldersNum = 0;

    _ok = true;
    _fit = 0;
    _depth = depth;
    _unBuildSubFoldersNum = 0;
    _unBuildFileNum = 0;

    folderPath = Path;
    folderName = split(Path, '/').back();
    folderDir = dirPath(Path);

    read();
}

folder::~folder()
{
    vector<string>().swap(filesPath);
    vector<string>().swap(subFoldersPath);
}

void folder::read()
{
    DIR *dir;           //目录结构体指针
    struct dirent *ptr; //用于遍历目录中的指针

    char *curTargetName;   //当前对象的名称（用于直接获取d_name）
    string scurTargetName; //当前对象的名称（转化为string，方便后续路径操作）
    string curTargetPath;  //当前对象路径

    dir = opendir(folderPath.c_str()); //打开目录，成功返回目录结构体指针，不成功返回NULL
                                       //错误码：
                                       //1、EACCESS 权限不足。
                                       //2、EMFILE 已达到进程可同时打开的文件数上限。
                                       //3、ENFILE 已达到系统可同时打开的文件数上限。
                                       //4、ENOTDIR 参数name 非真正的目录。
                                       //5、ENOENT 参数name 指定的目录不存在, 或是参数name 为一空字符串。
                                       //6、ENOMEM 核心内存不足。
    if (dir == NULL)
    {
        //无法打开目录，则输出信息，并将其正常值设为false
        cout << "Can not read folder:" << folderPath << endl;
        _ok = false;
        return; //直接跳出
    }
    while ((ptr = readdir(dir)) != NULL) //当ptr指向的对象不是NULL时，遍历目录
    {
        curTargetName = ptr->d_name;
        if (curTargetName[0] == '.') //跳过. ..两个目录
            continue;
        curTargetPath = joinPath(folderPath, curTargetName);
        //判断目录或文件，并分别添加到相应的列表
        if (isFolder(curTargetPath))
            subFoldersPath.push_back(curTargetName);
        else
            filesPath.push_back(curTargetName);
    }
    //更新未构建的子目录数量和文件数量
    _unBuildSubFoldersNum = subFoldersPath.size();
    _unBuildFileNum = filesPath.size();
    includeSubFoldersNum = subFoldersPath.size();
    includeFilesNum = filesPath.size();
    //!!!一定要关闭dir句柄，否则会导致进程调用文件句柄过多而引发段错误!!!
    closedir(dir);
}

void folder::show()
{
    //显示目录信息
    cout << "Folder:" << folderPath << endl;
    cout << "Content:" << to_string(subFoldersPath.size()) << " folders and " << to_string(filesPath.size()) << " files" << endl;

    string space7dot1 = "       -";
    string space7dot2 = "       --";

    for (int subFolderNum = 0; subFolderNum < subFoldersPath.size(); ++subFolderNum)
    {
        cout << space7dot1 + subFoldersPath[subFolderNum] << endl;
    }
    for (int fileNum = 0; fileNum < filesPath.size(); ++fileNum)
    {
        cout << space7dot2 + filesPath[fileNum] << endl;
    }
}