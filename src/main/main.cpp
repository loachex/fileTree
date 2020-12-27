#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

using namespace std;
int main()
{
    string testFolderPath="/media/loachex/SGS 1T/1";
    Tree *tp=new Tree(testFolderPath);
    cout<<"include "<<to_string(tp->includeFolderNum)<<" folders and "<<to_string(tp->includeFileNum)<<" files"<<endl;


}