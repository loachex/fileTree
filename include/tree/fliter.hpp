#include <iostream>
#define _H_FLITER

#ifndef _H_SSTREAM
#include <sstream>
#endif

#ifndef _H_FILE
#include "file.hpp"
#endif

#ifndef _H_PATH
#include "path.hpp"
#endif

using namespace std;

/*
class fileFliter
{
    public:
        fileFliter();
        ~fileFliter();

        T conditions;
        bool judge(file *f);
};
*/

class fileFliter_format
{
public:
    fileFliter_format();
    ~fileFliter_format();

    vector<string> conditions;
    bool judge(file *f);
};