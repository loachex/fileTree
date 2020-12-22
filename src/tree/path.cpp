#include "../../include/tree/path.hpp"

vector<string>split(string s,char c)
{
    const char *cString=s.c_str();
    string curString="";
    vector<string> splitResult;

    for(int stringcharnum=0;stringcharnum<s.size();++stringcharnum)
    {
        if(s[stringcharnum]!=c)
        {
            curString=curString+s[stringcharnum];
        }
        else if(!curString.empty())
        {
            splitResult.push_back(curString);
            curString.clear();
        }        
    }

    if(!curString.empty())
    {
        splitResult.push_back(curString);
    }

    return splitResult;

}

string dirPath(string path)
{

}

inline string joinPath(string path1,string path2)
{
    return path1+"/"+path2;
}

string joinPath(vector<string> paths)
{
    string path="";
    for(int pathsnum=0;pathsnum<paths.size();++pathsnum)
    {
        path+=paths[pathsnum];
    }

    return path;
}

string getFormat(string name)
{
    const char *c_name = name.c_str();
    string revertFormat , format = "";

    //获得revertFormat 拓展名（以"."）为分割
    for (int namecharnum = name.size(); c_name[namecharnum] != '.'; --namecharnum)
    {
        revertFormat = revertFormat + c_name[namecharnum];
    }
    //反转format
    for (int formatcharnum = revertFormat.size();formatcharnum;--formatcharnum)
    {
        format+=revertFormat[formatcharnum];
    }

    return format;
}

bool isFile(string Path)
{
    struct stat buffer;
    return (stat(Path.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
}

bool isFolder(string Path)
{
    struct stat buffer;
    return (stat(Path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

