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
bool func2(file *f, string value)
{
    if (f->filePath == value)
        return true;
    else
        return false;
}
int main()
{
    /*
    Tree t("/home/loachex/prog/cpp/proj/fileTree/src");
    file *f1;

    fileFliter<string> filefs1(LOGIC_NOT);
    rule<string> r1{func, "main.cpp"};
    rule<string> r2{func2, "/hoe/loachex/prog/cpp/proj/fileTree/src/main/main.cpp"};
    filefs1.addRule("filename", r1);
    filefs1.addRule("filepath", r2);

    while ((f1 = t.nextFile(false)) != NULL)
    {
        bool result = filefs1.fliter(f1);
        if (result)
            cout << f1->fileName << endl;
    }
    */
   file f("/home/loachex/prog/cpp/proj/fileTree/src/main/main.cpp");
   
}
