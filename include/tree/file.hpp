#include <iostream>

#define _H_FILE

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
    string filePath;//文件路径
    string fileName;//文件名称
    string format;//文件格式（后缀名）

    map<string,int> intValueMap;
    map<string,double> doubleValueMap;
    map<string,string> stringValueMap;

    bool _fit;//文件是否通过过滤器

    file(string ifilePath);
    ~file();

    template <class T>
    void addProperty(string item,T value);
    void delProperty(string item);
};
