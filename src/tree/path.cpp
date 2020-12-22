#include "../../include/tree/path.hpp"

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

