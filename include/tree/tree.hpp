#include "path.hpp"

using namespace std;

/*----------class file----------*/
class file
{
public:
    string name;
    string format;

    bool _show;

    file(string name,bool show);
    ~file();
};

/*----------class folder----------*/
class folder
{
public:
    vector<string> *subFolders;
    vector<string> *files;

    string folderPath;
    string upFolderPath;

    int _depth;                   //相对于顶文件夹的深度
    int _unGenerateSubFoldersNum; //没有迭代的子folder数量

    folder(string Path, int depth);
    ~folder();
    //释放内存时只释放folder中的file列表指针、所有file指针和subFolder列表指针
    //关联的子Folder指针不会被释放
    void show();

private:
    void read();
};

/*----------class Tree----------*/
class Tree
{
private:
    folder *headFolder;

    void generate();

public:
    int depth;
    string headFolderPath;

    Tree(string Path);
    ~Tree();
};