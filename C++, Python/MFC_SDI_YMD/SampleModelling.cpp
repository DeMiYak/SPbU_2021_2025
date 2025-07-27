#include "pch.h"
#include "SampleModelling.h"

// Исправление 1.
//if (_samVol != samVol) {
//    samVol = _samVol;
//    delete[] sample;
//    sample = new int[samVol];
//}
// Вместо
    /*
    delete[] sample;
    sample = new int[samVol];
    */
void InverseFunctionSample::Simulate(Distribution dis, int _samVol)
{
    // Исправление
    int whBalls = dis.GetWhBalls();
    int blBalls = dis.GetBlBalls();
    int pickNum = dis.GetPickNum();
    if (_samVol != samVol) {
        samVol = _samVol;
        delete[] sample;
        sample = new int[samVol];
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0, 1);

    for (int k = 0; k < samVol; ++k) {
        int i = 0;
        int n = whBalls + blBalls;
        double p = 1;

        for (int m = 0; m < pickNum; ++m) {
            p *= (blBalls - m);
            p /= (n - m);
        }

        double l = p;
        double alpha = distr(gen);

        while (alpha >= l) {
            p = p * (whBalls - i) * (pickNum - i) / ((i + 1) * (blBalls - pickNum + i + 1));
            l += p;
            ++i;
        }
        sample[k] = i;
    }
}

void BernoulliSample::Simulate(Distribution dis, int _samVol)
{
    // Исправление
    int whBalls = dis.GetWhBalls();
    int blBalls = dis.GetBlBalls();
    int pickNum = dis.GetPickNum();
    // Исправление
    if (_samVol != samVol) {
        samVol = _samVol;
        delete[] sample;
        sample = new int[samVol];
    }
    /*delete[] sample;
    sample = new int[samVol];*/
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0, 1);

    for (int k = 0; k < samVol; ++k) {
        int i = 0, j = 0;
        int n = whBalls + blBalls;
        double alpha = distr(gen);

        do {
            if (alpha < double(whBalls - j) / (n - i)) j++;
            i++;
            alpha = distr(gen);
        } while (i < pickNum);
        sample[k] = j;
    }
}

void Histogram::CountSampleFrequency(SampleModelling* samMod, Distribution dis)
{
    // Число вытаскиваний + 1 != множеству принимаемых значений 
    if (dis.GetPickNum() + 1 != empLen) {
        empLen = dis.GetPickNum() + 1;
        delete[] empFreq;
        empFreq = new int[empLen];
    }
    NullifyEmpFrequency();
    for (int i = 0; i < samMod->samVol; ++i) {
        ++empFreq[samMod->sample[i]];
    }
}

void Histogram::NullifyEmpFrequency()
{
    if (empLen < 1)
        return;
    for (int i = 0; i < empLen; ++i) {
        empFreq[i] = 0;
    }
}