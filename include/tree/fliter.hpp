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

template <class T>
struct rule
{
    /*判断规则*/
    bool (*func)(file *f, T value); //判断函数
    T standardValue;               //标准值
};

template <class T>
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
    map<string, rule<T>> RuleMap;
    vector<bool> results;

    fileFliter(int logic)
    {
        if (logic == LOGIC_OR)
        {
            _or = true;
            _and = false;
        }
        else if (logic == LOGIC_AND)
        {
            _or = false;
            _and = true;
        }
    }
    ~fileFliter();

    //逻辑学操作
    void reviseLogic()
    {
        _or = !_or;
        _and = !_and;

        result[8] = {-1};
    }
    bool cacuLogic(vector<bool> resultVec)
    {
        vector<bool>::iterator iter = results.begin();
        if (_or)
        {
            for (; iter != results.end(); iter++)
            {
                if (*iter)
                {
                    return true;
                }
            }
            return false;
        }
        else if (_and)
        {
            for (; iter != results.end(); iter++)
            {
                if (!*iter)
                {
                    return false;
                }
                return true;
            }
        }
        return NULL;
    }

    //增加、删除规则
    void addRule(string item, rule<T> arule)
    {
        RuleMap[item] = arule;
    }
    void delRule(string item)
    {
        map<string, rule<T>>::iterator iter = RuleMap.find(item);
        if (iter != RuleMap.end())
            RuleMap.erase(iter);
    }
    //过滤
    bool fliter(file *f)
    {
        if (!RuleMap.empty())
        {
            map<string, rule<T>>::iterator iter = RuleMap.begin();
            for (; iter != RuleMap.end(); iter++)
            {
                if (iter->second.func(f, iter->second.standardValue))
                    results.push_back(true);
                else
                    results.push_back(false);
            }
        }
        return cacuLogic(results);
    }
};