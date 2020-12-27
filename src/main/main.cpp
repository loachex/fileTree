#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

using namespace std;
int main()
{
    string testFolderPath="/media/loachex/SGS 1T/1";
    Tree *tp=new Tree(testFolderPath);
    delete tp;
}