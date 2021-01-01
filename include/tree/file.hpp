#define _H_FILE

#include <iostream>

#ifndef _H_PATH
#include "path.hpp"
#endif

#ifndef _H_MAP
#define _H_MAP
#include <map>
#endif

#ifndef _H_TYPEINFO
#include <typeinfo>
#define _H_TYPEINFO
#endif

using namespace std;

class file
{
public:
    string filePath; //文件路径
    string fileName; //文件名称

    map<string, int> intValueMap;
    map<string, double> doubleValueMap;
    map<string, string> stringValueMap;

    bool _fit; //文件是否通过过滤器

    file(string ifilePath)
    {
        filePath = ifilePath;
        fileName = split(filePath, '/').back();

        _fit = true;

        //添加文件基本属性
        string format=getFormat(fileName);
        addStringProperty("format", format);
    }
    ~file() {}

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
};
