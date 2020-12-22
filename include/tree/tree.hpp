#include "path.hpp"

using namespace std;

class folder
{
    
}

class Tree
{
    private:
        folder *headFolder;
        
        void generate();
    public:
        int depth;
        string headFolderPath;

        Tree(string Path);
        ~Tree();

};