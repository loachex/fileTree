#include "../../include/tree/file.hpp"

file::file(string ifilePath)
{
    filePath = ifilePath;
    fileName = split(filePath, '/').back();

    format = getFormat(fileName);
    _fit = true;
}
file::~file(){};

template <class T>
void file::addProperty(string item, T value)
{
    string valueType = typeid(value).name();

    switch (valueType)
    {
    case typeid(int).name():
        intValueMap[item] = value;
        break;
    case typeid(double).name():
        doubleValueMap[item] = value;
        break;
    case typeid(string).name():
        stringValueMap[item] = value;
        break;
    default:
        cout << "Unsupport value type:" << valueType << endl;
        break;
    }
}