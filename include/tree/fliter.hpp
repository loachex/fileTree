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
    /*判断规则*/
    bool (*func)(file *f, T1 value); //判断函数
    T1 standardValue;                //标准值
};

class fileFliter
{
private:
    //逻辑学操作
    bool _or;  //并
    bool _and; //与

public:
    /*
map<string,rule<T>:
判断规则字典
    1.string:项目名称：必须是文件属性字典中的键，用于索引文件的值与标准值比较
    2.rule<T>规则模板，包含标准值和判断函数
*/
    map<string, rule<int>> intRuleMap;
    map<string, rule<double>> doubleRuleMap;
    map<string, rule<string>> stringRuleMap;

    map<string, rule<vector<int>>> vintRuleMap;
    map<string, rule<vector<double>>> vdoubleRuleMap;
    map<string, rule<vector<string>>> vstringRuleMap;

    //记录六个规则字典的判断结果数组
    int result[6]; //-1:过滤器未使用；0：false；1：true

    fileFliter(int logic);
    ~fileFliter();

    //逻辑学操作
    void reviseLogic();
    bool cacuLogic(vector<bool> resultVec);
    bool cacuLogic(int resultArr[]);

    //增加、删除规则
    void addIntRule(string item, rule<int> arule);
    void addDoubleRule(string item, rule<double> arule);
    void addStringRule(string item, rule<string> arule);
    void addVIntRule(string item, rule<vector<int>> arule);
    void addVDoubleRule(string item, rule<vector<double>> arule);
    void addVStringRule(string item, rule<vector<string>> arule);

    void delRule(string item);

    //过滤
    bool fliter(file *f);
};