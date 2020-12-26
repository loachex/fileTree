#include <iostream>

#ifndef _H_PATH
#include "path.hpp"
#define _H_PATH
#endif

using namespace std;

class file
{

public:
    string fileName;
    string filePath;
    string format;

    bool _show;

    file(string ifilePath, bool show);
    ~file();
};
