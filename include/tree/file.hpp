#include <iostream>

#define _H_FILE

#ifndef _H_PATH
#include "path.hpp"
#endif

using namespace std;

class file
{
public:    
    string filePath;
    string fileName;
    string format;

    bool _show;

    file(string ifilePath, bool show);
    ~file();
};
