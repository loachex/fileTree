#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"


using namespace std;
int main()
{
    
    string p1="/proc";
    /*
    string p2="/opt";
    string p3="/media/loachex/WD 500G/imgAnalyse";
    string p4="/media/loachex/SGS 1T/1";

    Tree *t1,*t2,*t3,*t4,*t5;
    t1=new Tree(p1);
    t2=new Tree(p1);
    t3=new Tree(p1);
    t4=new Tree(p1);
    t5=new Tree(p1);
    */

    Tree *t=new Tree(p1);
    folder("/dev/fd/6",0);

}