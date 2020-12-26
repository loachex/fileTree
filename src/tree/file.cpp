#include "../../include/tree/file.hpp"

file::file(string ifilePath, bool show = true)
{
    filePath=ifilePath;
    fileName=split(filePath,'/').back();
    
    format = getFormat(fileName);
    _show = show;

#ifdef DEBUG
    cout << "创建file实例：" << this << "--" << this->fileName << endl;
#endif
}

file::~file()
{
#ifdef DEBUG
    cout << "销毁file实例：" << this << "--" << this->fileName << endl;
#endif
}
