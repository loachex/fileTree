#include "../../include/tree/file.hpp"

file::file(string ifilePath)
{
    filePath = ifilePath;
    fileName = split(filePath, '/').back();

    format = getFormat(fileName);
    _fit = true;

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
