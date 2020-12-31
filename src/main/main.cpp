#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

#include <typeinfo>
using namespace std;

bool func(file *f, string value)
{
    if (f->fileName == value)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int main()
{
    fileFliter ff(LOGIC_AND);
    string item="name";
    rule<string> r1{func,"fliter.cpp"};
    ff.addStringRule(item,r1);
}
