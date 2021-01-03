#define _H_FOLDER

#ifndef _H_FILE
#include "file.hpp"
#endif

using namespace std;

class folder
{
public:
    int includeSubFoldersNum; //包含的子目录数量
    int includeFilesNum;      //包含的子文件数量

    bool _ok;                  //本目录是否正常
    bool _fit;                 //本目录是否通过过滤器
    int _depth;                //相对于顶目录的深度
    int _unBuildSubFoldersNum; //没有构建的子目录数量
    int _unBuildFileNum;       //没有构建的子文件数量

    string folderPath; //本目录路径
    string folderName; //本目录名称
    string folderDir;  //本目录的上级路径

    vector<string> subFoldersPath; //子目录路径列表
    vector<string> filesPath;      //子文件路径列表

    folder *pdirFolder;           //只能由Tree对象添加和删除：父目录指针
    vector<folder *> psubFolders; //只能由Tree对象添加和删除：子目录指针列表
    vector<file *> pfiles;        //只能由Tree对象添加和删除：子文件指针列表

    map<string, int> intValueMap;
    map<string, double> doubleValueMap;
    map<string, string> stringValueMap;

    folder(string Path, int depth);
    ~folder();

    void show(); //展示本目录中的子目录名称和子文件名称
    void addIntProperty(string item, int value)
    {
        intValueMap[item] = value;
    }
    void addDoubleProperty(string item, double value)
    {
        doubleValueMap[item] = value;
    }
    void addStringProperty(string item, string value)
    {
        stringValueMap[item] = value;
    }
    void delProperty(string item)
    {
        //将删除三个字典中所有为item的项
        map<string, int>::iterator iIter = intValueMap.find(item);
        map<string, double>::iterator dIter = doubleValueMap.find(item);
        map<string, string>::iterator sIter = stringValueMap.find(item);

        if (iIter != intValueMap.end())
            intValueMap.erase(iIter);
        if (dIter != doubleValueMap.end())
            doubleValueMap.erase(dIter);
        if (sIter != stringValueMap.end())
            stringValueMap.erase(sIter);
    }
    int findIntProperty(string item)
    {
        //寻找Int属性值
        map<string, int>::iterator iIter = intValueMap.find(item);
        if (iIter != intValueMap.end())
            return iIter->second;
        else
            return NULL;
    }
    double findDoubleProperty(string item)
    {
        //寻找Double属性值
        map<string, double>::iterator dIter = doubleValueMap.find(item);
        if (dIter != doubleValueMap.end())
            return dIter->second;
        else
            return NULL;
    }
    string findStringProperty(string item)
    {
        //寻找Int属性值
        map<string, string>::iterator sIter = stringValueMap.find(item);
        if (sIter != stringValueMap.end())
            return sIter->second;
        else
            return NULL;
    }
private:
    void read();
};