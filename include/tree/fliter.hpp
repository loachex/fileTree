#define _H_FLITER

#include <iostream>

#ifndef _H_SSTREAM
#include <sstream>
#endif

#ifndef _H_FILE
#include "file.hpp"
#endif

#ifndef _H_PATH
#include "path.hpp"
#endif

#ifndef _H_MAP
#include <map>
#define _H_MAP
#endif

#ifndef _H_TYPEINFO
#include <typeinfo>
#define _H_TYPEINFO
#endif

#define LOGIC_OR 0
#define LOGIC_AND 1

using namespace std;

template <class T1>
struct rule
{
    bool (*func)(file *f, T1 value);
    T1 standardValue;
};

class fileFliter
{
private:
    bool _or;
    bool _and;

public:
/*
map<string,rule<T>
    1.string:项目名称：必须是文件属性字典中的键，用于索引文件的值与标准值比较
    2.rule<T>规则模板，包含标准值和判断函数
*/
    map<string, rule<int>> intRuleMap;
    map<string, rule<double>> doubleRuleMap;
    map<string, rule<char>> charRuleMap;
    map<string, rule<string>> stringRuleMap;

    map<string, rule<vector<int>>> vintRuleMap;
    map<string, rule<vector<double>>> vdoubleRuleMap;
    map<string, rule<vector<char>>> vcharRuleMap;
    map<string, rule<vector<string>>> vstringRuleMap;

    int result[8];//-1:过滤器未使用；0：false；1：true

    fileFliter(int logic);
    ~fileFliter();

    void reviseLogic();
    bool cacuLogic(vector<bool> resultVec);
    bool cacuLogic(int resultArr[]);

    template <class T2>
    void addRule(string item, rule<T2> rule);
    void delRule(string item);

    bool fliter(file *f);
};