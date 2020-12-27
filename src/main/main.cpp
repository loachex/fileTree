#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

using namespace std;
int main()
{
    string testFolderPath="/home/loachex/software";
    Tree *tp=new Tree(testFolderPath);
    delete tp;
    
}