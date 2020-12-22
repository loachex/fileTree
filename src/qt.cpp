#include <dirent.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;
int main()
{
    struct dirent *dp;
    string s="/home/loachex/prog/cpp/proj/imgTree/src/cmake";

    struct stat buffer;
    if(stat(s.c_str(),&buffer)==0 && S_ISDIR(buffer.st_mode))cout<<"is a folder";
}