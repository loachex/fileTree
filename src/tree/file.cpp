#include "../../include/tree/file.hpp"

file::file(string name, bool show = true)
{
    name = name;
    format = getFormat(name);
    _show = show;

#ifdef DEBUG
    cout << "创建file实例：" << this << endl;
#endif
}

file::~file()
{
#ifdef DEBUG
    cout << "销毁file实例：" << this << endl;
#endif
}
