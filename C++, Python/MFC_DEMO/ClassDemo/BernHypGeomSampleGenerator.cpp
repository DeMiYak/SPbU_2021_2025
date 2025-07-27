
#include "BernHypGeomSampleGenerator.h"

void BernHypGeomSampleGenerator::Simulate(const Distribution& dis, int _samVol)
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
