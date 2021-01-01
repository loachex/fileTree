#include "../../include/tree/tree.hpp"
#include "../../include/tree/path.hpp"

#include <typeinfo>
using namespace std;

mutex mtx;
void process_func(fileArgs<int, vector<string>> fs)
{
    for (int i = 0; i < fs.vf.size(); ++i)
    {
        mtx.lock();
        fs.result->push_back(fs.vf[i]->filePath);
        cout << to_string(fs.result->size()) << "/" << fs.args << endl;
        mtx.unlock();
    }
}

int main()
{
    vector<string> *v = new vector<string>();//result一定要初始化
    string path = "/media/loachex/SGS 1T/1";
    Tree *t = new Tree(path);

    t->MfileProcess(process_func, t->fitFileNum, v, 30);
}
