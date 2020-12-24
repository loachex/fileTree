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

    vector<folder *> psubFolders; //只能由Tree对象添加和删除
    vector<file *> pfiles;        //只能由Tree对象添加和删除

    string folderPath;
    string folderName;

    int _depth;                   //相对于顶文件夹的深度
    int _unGenerateSubFoldersNum; //没有迭代的子folder数量

    folder(string Path, int depth);
    ~folder();

    void show();

private:
    void read();
    void build();
};