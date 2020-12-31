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
#define LOGIC_NOT 2

using namespace std;

/*----------*Struct rule----------**/
template <class T>
struct rule
{
    /*判断规则*/
    bool (*func)(file *f, T value); //判断函数
    T standardValue;                //标准值
};

/*----------Class fileFliter----------*/
template <class T>
class fileFliter
{
private:
    //逻辑值
    bool _or;  //或
    bool _and; //与
    bool _not; //非

public:
    map<string, rule<T>> RuleMap;
    vector<bool> results;

    fileFliter()
    {
        //默认采用并的逻辑
        _or = false;
        _and = true;
        _not = false;
    }
    fileFliter(int logic)
    {
        //采用指定的方式
        initLogic();
        reviseLogic(logic);
    }
    ~fileFliter(){};

    //逻辑学操作
    void initLogic()
    {
        _or = _and = _not = false;
    }
    void reviseLogic(int logic)
    {
        initLogic();
        switch (logic)
        {
        case LOGIC_OR:
            _or = true;
            break;
        case LOGIC_AND:
            _and = true;
            break;
        case LOGIC_NOT:
            _not = true;
        default:
            break;
        }
    }
    bool cacuLogic(vector<bool> resultVec)
    {
        //根据结果列表与逻辑关系，计算布尔值
        vector<bool>::iterator iter = results.begin();

        if (_or)
        {
            for (; iter != results.end(); iter++)
            {
                if (*iter)
                    return true;
            }
            return false;
        }
        else if (_and)
        {
            for (; iter != results.end(); iter++)
            {
                if (!*iter)
                    return false;
            }
            return true;
        }
        else if (_not)
        {
            for (; iter != results.end(); iter++)
            {
                if (*iter)
                    return false;
            }
            return true;
        }
        return NULL;
    }

    //增加、删除规则
    void addRule(string item, rule<T> arule)
    {
        //增加规则，项目重名时替换规则
        RuleMap[item] = arule;
    }
    void addRule(string item, bool (*func)(file *f, T value), T standardValue)
    {
        //直接输入项目名、判断函数与标准值，添加规则
        rule<T> r{func, standardValue};
        RuleMap[item] = r;
    }
    void delRule(string item)
    {
        //根据项目删除规则
        typename map<string, rule<T>>::iterator iter = RuleMap.find(item);
        if (iter != RuleMap.end())
            RuleMap.erase(iter);
    }
    //过滤
    bool fliter(file *f)
    {
        //过滤：将文件利用规则字典中的每一条规则进行判断，将所有结果存入results列表中
        //根据逻辑关系进行输出
        results.clear();
        if (!RuleMap.empty())
        {
            typename map<string, rule<T>>::iterator iter = RuleMap.begin();
            for (; iter != RuleMap.end(); iter++)
            {
                if (iter->second.func(f, iter->second.standardValue))
                    results.push_back(true);
                else
                    results.push_back(false);
            }
        }
        f->_fit = cacuLogic(results);
        return f->_fit;
    }
};