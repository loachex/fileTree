#include <typeinfo>
#include <iostream>
#include <sstream>
#include <map>

int main()
{
    using namespace std;
    map<string,int> m;
    m["1"]=1;
    m["2"]=2;

    map<string,int>::iterator iter=m.find("2");
    cout<<iter->second<<endl;
    
}