#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

#include <typeinfo>
using namespace std;
int main()
{
    Tree t("/opt");
    file *f;
    int i = 0;
    while ((f = t.nextFile(false)) != NULL)
    {
        cout << f->filePath << endl;
        i++;
    }
    cout << i << endl;
}
