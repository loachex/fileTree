#include "../../include/tree/tree.hpp"

using namespace std;
int main()
{
    /*
    string name1="./usr/include";
    string name2="tree/tree.cpp";

    vector<string> v;
    for(int i=0;i<3;i++)
    {
        v.push_back(name1);
    }
    cout<<joinPath(v)<<endl;
    

   string a="";
   vector<string> v;
   for(int i=0;i<10;++i)
   {
       a=a+'a';
       v.push_back(a);
   }

   for(int i=0;i<10;++i)
   {
       cout<<v[i]<<endl;
   }
   */

  string a="hello.world.if.it.is.ok.";
  vector<string> v=split(a,'.');
  cout<<"!";

}