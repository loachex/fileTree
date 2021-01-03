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

double aveV(vector<double> v)
{
    int i = 0;
    double sum;
    for (i = 0; i < v.size(); ++i)
    {
        sum += v[i];
    }

    return sum / v.size();
}
void processFunc(fileArgs<int, vector<double>> fas)
{
    string curImgPath;
    cv::Mat img, channel1, channel2, channel3;
    vector<cv::Mat> channels;
    double aveR, aveG, aveB = 0.;
    for (int i = 0; i < fas.vf.size(); i++)
    {
        curImgPath = fas.vf[i]->filePath;
        img = cv::imread(curImgPath);

        split(img, channels);
        channel1 = channels[0];
        channel2 = channels[1];
        channel3 = channels[2];

        aveR = ave(channel1);
        aveG = ave(channel2);
        aveB = ave(channel3);

        mtx.lock();
        (*fas.result)[0] = (*fas.result)[0] + aveR;
        (*fas.result)[1] = (*fas.result)[1] + aveG;
        (*fas.result)[2] = (*fas.result)[2] + aveB;
        (*fas.result)[3]++;

        cout << "img:" << to_string(int((*fas.result)[3])) << "/" << fas.args << "--|| R:" << to_string(aveR) << "|| G:" << to_string(aveG) << " || B:" << to_string(aveB) << endl;
        mtx.unlock();
    }
}

int main(int argc, char *argv[])
{
    time_t st, et;
    st = clock();

    vector<double> *resultV = new vector<double>();
    (*resultV) = {0., 0., 0., 0.};
    string path = "/media/loachex/d500g/imgAnalyse/";

    Tree *t = new Tree(path);
    t->stringFileFliter.addRule("format_jpg", fliterFunc_format, "jpg");
    t->stringFileFliter.addRule("format_png", fliterFunc_format, "jpeg");
    t->stringFileFliter.addRule("format_jpeg", fliterFunc_format, "png");
    t->stringFileFliter.addRule("format_JPG", fliterFunc_format, "JPG");
    t->stringFileFliter.addRule("format_bmp", fliterFunc_format, "bmp");
    t->stringFileFliter.addRule("format_JPEG", fliterFunc_format, "JPEG");

    t->stringFileFliter.reviseLogic(LOGIC_OR);
    t->fliter();

    t->MfileProcess(processFunc, t->fitFileNum, resultV, 4);
    cout << "Ave R:" << (*resultV)[0] / t->fitFileNum << ",G:" << (*resultV)[1] / t->fitFileNum << ",B:" << (*resultV)[2] / t->fitFileNum << endl;
    et = clock();

    cout << "Cost time:" << to_string(double((et - st) / CLOCKS_PER_SEC)) << " s" << endl;
    return 0;
}