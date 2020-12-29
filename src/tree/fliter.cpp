#include "../../include/tree/fliter.hpp"

fileFliter::fileFliter(int logic)
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
fileFliter::~fileFliter() {}

void fileFliter::reviseLogic()
{
    _or = !_or;
    _and = !_and;

    result[8] = {-1};
}

bool fileFliter::cacuLogic(vector<bool> results)
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
}
bool fileFliter::cacuLogic(int resultArr[])
{
    int ran = 0;
    if (_or)
    {
        for (ran = 0; ran < 8; ++ran)
        {
            if (resultArr[ran] == -1)
                continue;
            else if (resultArr[ran])
                return true;
        }
        return false;
    }
    else if (_and)
    {
        for (ran = 0; ran < 8; ++ran)
        {
            if (resultArr[ran] == -1)
                continue;
            else if (!resultArr[ran])return false;
        }
        return true;
    }
}

template <class T2>
void fileFliter::addRule(string item, rule<T2> arule)
{
    string itype = typeid(arule).name();
    switch (itype)
    {
    case typeid(rule<int>).name():
        intRuleMap.insert(pair<string, rule<int>>(item, arule));
        break;
    case typeid(rule<double>).name():
        doubleRuleMap.insert(pair<string, rule<double>>(item, arule));
        break;
    case typeid(rule<char>).name():
        charRuleMap.insert(pair<string, rule<char>>(item, arule));
        break;
    case typeid(rule<string>).name():
        stringRuleMap.insert(pair<string, rule<string>>(item, arule));
        break;
    case typeid(rule<vector<int>>).name():
        vintRuleMap.insert(pair<string, rule<vector<int>>>(item, arule));
        break;
    case typeid(rule<vector<double>>).name():
        vdoubleRuleMap.insert(pair<string, rule<vector<double>>>(item, arule));
        break;
    case typeid(rule<vector<char>>).name():
        vcharRuleMap.insert(pair<string, rule<vector<char>>>(item, arule));
        break;
    case typeid(rule<vector<string>>).name():
        vstringRuleMap.insert(pair<string, rule<vector<string>>>(item, arule));
        break;
    default:
        break;
    }
}

void fileFliter::delRule(string item)
{
}

bool fileFliter::fliter(file *f)
{
    vector<bool> curResult;

    if (!intRuleMap.empty())
    {
        map<string, rule<int>>::iterator intIter = intRuleMap.begin();
        for (; intIter != intRuleMap.end(); intIter++)
        {
            if (intIter->second.func(f, intIter->second.standardValue))
                curResult.push_back(true);
            else
                curResult.push_back(false);
        }
        result[0] = (cacuLogic(curResult)) ? 1 : 0;
        curResult.clear();
    }
    if (!doubleRuleMap.empty())
    {
        map<string, rule<double>>::iterator doubleIter = doubleRuleMap.begin();
        for (; doubleIter != doubleRuleMap.end(); doubleIter++)
        {
            if (doubleIter->second.func(f, doubleIter->second.standardValue))
                curResult.push_back(true);
            else
                curResult.push_back(false);
        }
        result[1] = (cacuLogic(curResult)) ? 1 : 0;
        curResult.clear();
    }
    if (!charRuleMap.empty())
    {
        map<string, rule<char>>::iterator charIter = charRuleMap.begin();
        for (; charIter != charRuleMap.end(); charIter++)
        {
            if (charIter->second.func(f, charIter->second.standardValue))
                curResult.push_back(true);
            else
                curResult.push_back(false);
        }
        result[2] = (cacuLogic(curResult)) ? 1 : 0;
        curResult.clear();
    }
    if (!stringRuleMap.empty())
    {
        map<string, rule<string>>::iterator stringIter = stringRuleMap.begin();
        for (; stringIter != stringRuleMap.end(); stringIter++)
        {
            if (stringIter->second.func(f, stringIter->second.standardValue))
                curResult.push_back(true);
            else
                curResult.push_back(false);
        }
        result[3] = (cacuLogic(curResult)) ? 1 : 0;
        curResult.clear();
    }
    if (!vintRuleMap.empty())
    {
        map<string, rule<vector<int>>>::iterator vintIter = vintRuleMap.begin();
        for (; vintIter != vintRuleMap.end(); vintIter++)
        {
            if (vintIter->second.func(f, vintIter->second.standardValue))
                curResult.push_back(true);
            else
                curResult.push_back(false);
        }
        result[4] = (cacuLogic(curResult)) ? 1 : 0;
        curResult.clear();
    }
    if (!vdoubleRuleMap.empty())
    {
        map<string, rule<vector<double>>>::iterator vdoubleIter = vdoubleRuleMap.begin();
        for (; vdoubleIter != vdoubleRuleMap.end(); vdoubleIter++)
        {
            if (vdoubleIter->second.func(f, vdoubleIter->second.standardValue))
                curResult.push_back(true);
            else
                curResult.push_back(false);
        }
        result[5] = (cacuLogic(curResult)) ? 1 : 0;
        curResult.clear();
    }
    if (!vcharRuleMap.empty())
    {
        map<string, rule<vector<char>>>::iterator vcharIter = vcharRuleMap.begin();
        for (; vcharIter != vcharRuleMap.end(); vcharIter++)
        {
            if (vcharIter->second.func(f, vcharIter->second.standardValue))
                curResult.push_back(true);
            else
                curResult.push_back(false);
        }
        result[6] = (cacuLogic(curResult)) ? 1 : 0;
        curResult.clear();
    }
    if (!vstringRuleMap.empty())
    {
        map<string, rule<vector<string>>>::iterator vstringIter = vstringRuleMap.begin();
        for (; vstringIter != vstringRuleMap.end(); vstringIter++)
        {
            if (vstringIter->second.func(f, vstringIter->second.standardValue))
                curResult.push_back(true);
            else
                curResult.push_back(false);
        }
        result[7] = (cacuLogic(curResult)) ? 1 : 0;
        curResult.clear();
    }

    return cacuLogic(result);
}