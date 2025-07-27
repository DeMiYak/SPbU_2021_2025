
#include "InvFunHypGeomSampleGenerator.h"

void InvFunHypGeomSampleGenerator::Simulate(const Distribution& dis, int _samVol)
{
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
