#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

using namespace std;
int main()
{
    string testFolderPath="/home/loachex/software/opencv-3.4.12";
    Tree *tp=new Tree(testFolderPath);
    cout<<"include "<<to_string(tp->includeFolderNum)<<" folders and "<<to_string(tp->includeFileNum)<<" files"<<endl;
    cout<<"Memory Usage:"<<to_string(tp->_MemoryUsage/1024)<<"KB"<<endl;

}