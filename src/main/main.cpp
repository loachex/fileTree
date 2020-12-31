#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

#include <typeinfo>
using namespace std;

bool func(file *f, string value)
{
    if (f->findStringProperty("format") == value)
        return true;
    else
        return false;
}

int main()
{
    string path = "/media/loachex/SGS 1T/1";
    Tree *t = new Tree(path);
    cout << "ok" << endl;

    t->stringFileFliter.addRule("format", func, "jpg");
    t->fliter();
    file *f;
    while ((f = t->nextFile(false)) != NULL)
    {
        cout << f->filePath << " 共计：" << to_string(t->stringFileFliter.fitNum) << endl;
    }
}
