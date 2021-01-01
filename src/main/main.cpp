#include "../../include/fileTree.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

bool fliterFunc_format(file *f, string value)
{
    if (f->findStringProperty("format") == value)
        return true;
    else
        return false;
}

mutex mtx;
double ave(cv::Mat m)
{
    int r = m.rows;
    int c = m.cols;

    double row_ave = 0.;
    double mat_ave = 0.;

    for (int rn = 0; rn < r; rn++)
    {
        for (int cn = 0; cn < c; cn++)
        {
            row_ave += (double)*((uchar *)(m.data + m.step[0] * rn + cn * m.step[1]));
        }
        row_ave /= double(c);
        mat_ave += row_ave;
        row_ave = 0.;
    }
    return mat_ave / double(r);
}
void processFunc(fileArgs<int, vector<double>> fas)
{
    string curImgPath;
    cv::Mat img;
    double aveResult = 0.;
    for (int i = 0; i < fas.vf.size(); i++)
    {
        curImgPath = fas.vf[i]->filePath;
        img = cv::imread(curImgPath);
        aveResult = ave(img);

        mtx.lock();
        fas.result->push_back(aveResult);
        cout << to_string(fas.result->size()) << "/" << fas.args << endl;
        mtx.unlock();
    }
}

int main(int argc, char *argv[])
{
    vector<double> *resultV = new vector<double>();
    string path = "/media/loachex/SGS 1T/1/游戏";

    Tree *t = new Tree(path);
    t->stringFileFliter.addRule("format_jpg", fliterFunc_format, "jpg");
    t->stringFileFliter.addRule("format_png", fliterFunc_format, "jpeg");
    t->stringFileFliter.addRule("format_jpeg", fliterFunc_format, "png");
    t->stringFileFliter.addRule("format_JPG", fliterFunc_format, "JPG");
    t->stringFileFliter.addRule("format_bmp", fliterFunc_format, "bmp");

    t->stringFileFliter.reviseLogic(LOGIC_OR);
    t->fliter();

    t->MfileProcess(processFunc, t->fitFileNum, resultV, 5);
    
    return 0;
}