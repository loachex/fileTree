#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

#include <typeinfo>
using namespace std;

void filter_func(vector<file *> vf)
{
    for (int i = 0; i < vf.size(); ++i)
    {
        cout << vf[i]->fileName << endl;
    }
}

void process_func(file *f)
{
    cout << "File name:" << f->fileName << endl;
}

int main()
{
    string path = "/media/loachex/SGS 1T/1";
    Tree *t = new Tree(path);
    int i = 0;
    double *j;
    t->MfileProcess(filter_func,30);
}
