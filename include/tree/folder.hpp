#define _H_FOLDER

#ifndef _H_FILE
#include "file.hpp"
#endif

using namespace std;

class folder
{
public:
    vector<string> subFoldersPath; //子目录路径列表
    vector<string> filesPath;      //子文件路径列表

    folder *pdirFolder;           //只能由Tree对象添加和删除：父目录指针
    vector<folder *> psubFolders; //只能由Tree对象添加和删除：子目录指针列表
    vector<file *> pfiles;        //只能由Tree对象添加和删除：子文件指针列表

    string folderPath; //本目录路径
    string folderName; //本目录名称
    string folderDir;  //本目录的上级路径

    bool _ok;                  //本目录是否正常
    int _depth;                //相对于顶目录的深度
    int _unBuildSubFoldersNum; //没有构建的子目录数量
    int _unBuildFileNum;       //没有构建的子文件数量

    folder(string Path, int depth); 
    ~folder();

    void show();//展示本目录中的子目录名称和子文件名称
private:
    void read();
};