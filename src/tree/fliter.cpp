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
    return NULL;
}
bool fileFliter::cacuLogic(int resultArr[])
{
    int ran = 0;
    if (_or)
    {
        for (ran = 0; ran < 6; ++ran)
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
        for (ran = 0; ran < 6; ++ran)
        {
            if (resultArr[ran] == -1)
                continue;
            else if (!resultArr[ran])
                return false;
        }
        return true;
    }

    return NULL;
}

void fileFliter::addIntRule(string item, rule<int> arule)
{
    intRuleMap[item] = arule;
}
void fileFliter::addDoubleRule(string item, rule<double> arule)
{
    doubleRuleMap[item] = arule;
}
void fileFliter::addStringRule(string item, rule<string> arule)
{
    stringRuleMap[item] = arule;
}
void fileFliter::addVIntRule(string item, rule<vector<int>> arule)
{
    vintRuleMap[item] = arule;
}
void fileFliter::addVDoubleRule(string item, rule<vector<double>> arule)
{
    vdoubleRuleMap[item] = arule;
}
void fileFliter::addVStringRule(string item, rule<vector<string>> arule)
{
    vstringRuleMap[item] = arule;
}
void fileFliter::delRule(string item)
{
    map<string, rule<int>>::iterator iIter = intRuleMap.find(item);
    map<string, rule<double>>::iterator dIter = doubleRuleMap.find(item);
    map<string, rule<string>>::iterator sIter = stringRuleMap.find(item);
    map<string, rule<vector<int>>>::iterator viIter = vintRuleMap.find(item);
    map<string, rule<vector<double>>>::iterator vdIter = vdoubleRuleMap.find(item);
    map<string, rule<vector<string>>>::iterator vsIter = vstringRuleMap.find(item);

    if (iIter != intRuleMap.end())
        intRuleMap.erase(iIter);
    if (dIter != doubleRuleMap.end())
        doubleRuleMap.erase(dIter);
    if (sIter != stringRuleMap.end())
        stringRuleMap.erase(sIter);
    if (viIter != vintRuleMap.end())
        vintRuleMap.erase(viIter);
    if (vdIter != vdoubleRuleMap.end())
        vdoubleRuleMap.erase(vdIter);
    if (vsIter != vstringRuleMap.end())
        vstringRuleMap.erase(vsIter);
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

    f->_fit = cacuLogic(result);
    return f->_fit;
}