#ifndef _H_FILE
#include "file.hpp"
#define _H_FILE
#endif

using namespace std;

class folder
{
public:
    vector<string> subFolders;
    vector<string> files;

    folder *dirFolder;            //只能由Tree对象添加和删除
    vector<folder *> psubFolders; //只能由Tree对象添加和删除
    vector<file *> pfiles;        //只能由Tree对象添加和删除

    string folderPath; //文件夹路径
    string folderName; //文件夹名称
    string folderDir;  //文件夹的上级路径

    int _depth;                //相对于顶文件夹的深度
    int _unBuildSubFoldersNum; //没有构建的子folder数量
    int _unBuildFileNum;       //没有构建的文件数量

    folder(string Path, int depth); //根文件夹用这个
    ~folder();

    void show();

private:
    void read();
    void build();
};