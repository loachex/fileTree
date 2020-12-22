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
    vector<string> subFolders;
    vector<string> files;
    
    vector<folder*> psubFolders;
    vector<file*> pfiles;

    string folderPath;
    
    int _depth;                   //相对于顶文件夹的深度
    int _unGenerateSubFoldersNum; //没有迭代的子folder数量

    folder(string Path, int depth);
    ~folder();

    void show();

private:
    void read();
    void build();
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