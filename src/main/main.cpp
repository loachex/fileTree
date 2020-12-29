#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

#include <typeinfo>
using namespace std;
int main()
{
    
    vector<double> v1,v2,v3;
    cout<<typeid(v1).name()<<endl<<typeid(v2).name()<<endl<<typeid(v3).name()<<endl;

}
