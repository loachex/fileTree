#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

using namespace std;
int main()
{

    
    string p1 = "/media/loachex/WD 500G/imgAnalyse";
    Tree *t1;

    t1 = new Tree(p1);
    folder *f;
    int i=0;
    folder *f1=t1->apflattenFolders.back();
    folder *f2=*(t1->folderIterEnd);
    while ((f = t1->nextFolder(false)) != NULL)
    {
        cout << f->folderPath << endl;
        ++i;
    }
    cout<<i<<endl;
   

}
