#include "../../include/tree/path.hpp"

vector<string> split(string s, char c)
{
    const char *cString = s.c_str();
    string curString = "";
    vector<string> splitResult;

    for (int stringcharnum = 0; stringcharnum < s.size(); ++stringcharnum)
    {
        if (s[stringcharnum] != c)
        {
            curString = curString + s[stringcharnum];
        }
        else if (!curString.empty())
        {
            splitResult.push_back(curString);
            curString.clear();
        }
    }

    if (!curString.empty())
    {
        splitResult.push_back(curString);
    }

    return splitResult;
}

string dirPath(string path)
{
    vector<string> splitResult = split(path, '/');
    splitResult.pop_back();
    if (!splitResult.size())
        return "..";
    else
        return joinPath(splitResult);
}

string joinPath(string path1, string path2)
{
    return path1 + "/" + path2;
}
string joinPath(string path1, char *path2)
{
    string spath2;
    const char *cpath2 = path2;
    spath2 = cpath2;
    return path1 + "/" + spath2;
}
string joinPath(char *path1, char *path2)
{
    string spath1, spath2;
    const char *cpath1, *cpath2;
    cpath1 = path1;
    cpath2 = path2;
    spath1 = cpath1;
    spath2 = cpath2;

    return spath1 + spath2;
}
string joinPath(vector<string> paths)
{
    if (paths.size() == 1)
    {
        return paths[0];
    }
    else
    {
        string path = "";
        int pathsnum;
        for (pathsnum = 0; pathsnum < paths.size() - 1; ++pathsnum)
        {
            path += paths[pathsnum];
            path += "/";
        }
        return path + paths[pathsnum];
    }
}

string getFormat(string name)
{
    string format="";
    string reverseformat;
    for (int nn = name.size() - 1; name[nn] != '.'; nn--)
    {
        reverseformat = reverseformat + name[nn];
    }
    for (int rn = reverseformat.size() - 1; rn > -1; rn--)
    {
        format = format + reverseformat[rn];
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
