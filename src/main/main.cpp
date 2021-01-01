#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

#include <typeinfo>
using namespace std;

void process_func(vector<file *> vf)
{
    for (int i = 0; i < vf.size(); ++i)
    {
        cout << vf[i]->fileName << endl;
    }
}

int main()
{
    string path = "/media/loachex/SGS 1T/1";
    Tree *t = new Tree(path);
    int i = 0;
    double *j;
    t->MfileProcess(process_func,30);
}
