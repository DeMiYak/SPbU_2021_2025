
#include "Chi2Histogram.h"
#include<utility>

/// <summary>
/// Конструктор класса
/// </summary>
/// <param name="bsg">Выборка (после эксперимента)</param>
/// <param name="dis">Распределение</param>
ChiSqHistogram::ChiSqHistogram(const BaseSampleGenerator* bsg, const Distribution& dis) : 
    freqLen(0),
    empFreq(nullptr), 
    thFreq(nullptr),
    pLevel(0),
    chiSq(0),
    dof(0)
{
    SetData(bsg, dis);
}

ChiSqHistogram::ChiSqHistogram(const ChiSqHistogram& csh) :
    freqLen(csh.freqLen),
    chiSq(csh.chiSq),
    dof(csh.dof),
    pLevel(csh.pLevel)
{
    empFreq = new int[freqLen];
    thFreq = new double[freqLen];
    for (int i = 0; i < freqLen; i++) {
        empFreq[i] = csh.empFreq[i];
        thFreq[i] = csh.thFreq[i];
    }
}

ChiSqHistogram::ChiSqHistogram(ChiSqHistogram&& csh):
    freqLen(std::exchange(csh.freqLen, 0)),
    chiSq(std::exchange(csh.chiSq, 0)),
    dof(std::exchange(csh.dof, 0)),
    pLevel(std::exchange(csh.pLevel, 0)),
    empFreq(std::move(csh.empFreq)),
    thFreq(std::move(csh.thFreq))
{
    csh.empFreq = nullptr;
    csh.thFreq = nullptr;
}

ChiSqHistogram& ChiSqHistogram::operator=(const ChiSqHistogram& csh)
{
    if (this != &csh) {
        freqLen = csh.freqLen;
        dof = csh.dof;
        pLevel = csh.pLevel;
        chiSq = csh.chiSq;
        empFreq = new int[freqLen];
        thFreq = new double[freqLen];
        for (int i = 0; i < freqLen; i++) {
            empFreq[i] = csh.empFreq[i];
            thFreq[i] = csh.thFreq[i];
        }
    }
    return *this;
}
ChiSqHistogram& ChiSqHistogram::operator=(ChiSqHistogram&& csh)
{
    if (this != &csh) {
        freqLen = std::exchange(csh.freqLen, 0);
        chiSq = std::exchange(csh.chiSq, 0);
        dof = std::exchange(csh.dof, 0);
        pLevel = std::exchange(csh.pLevel, 0);
        empFreq = std::move(csh.empFreq);
        thFreq = std::move(csh.thFreq);
        csh.empFreq = nullptr;
        csh.thFreq = nullptr;
    }
    return *this;
}


/// <summary>
/// Запись новых данных
/// </summary>
/// <param name="bsg">Выборка (после эксперимента)</param>
/// <param name="dis">Распределение</param>
void ChiSqHistogram::SetData(const BaseSampleGenerator* bsg, const Distribution& dis)
{
    int maxVal = 0;
    int samVol = bsg->GetSamVol();
    const int* sample = bsg->GetSample();
    int disLen = dis.GetPickNum() + 1;
    for (int i = 0; i < samVol; i++) {
        if (maxVal < sample[i]) {
            maxVal = sample[i];
        }
    }
    if(maxVal > disLen){
        chiSq = -1;
        dof = -1;
        pLevel = 0;
    }
    else {
        chiSq = 0;
        dof = 0;
        pLevel = 0;
    }
    Resize(std::max(maxVal, disLen));
    // Будет ли забиваться память?
    CountThFreq(dis, samVol);
    CountEmpFreq(bsg);
}

/// <summary>
/// Пересчёт диапазона частотных значений
/// </summary>
/// <param name="_freqLen">Диапазон частот</param>
void ChiSqHistogram::Resize(int _freqLen)
{
    if (freqLen == _freqLen) {
        return;
    }
    freqLen = _freqLen;
    delete[] empFreq;
    delete[] thFreq;
    empFreq = new int[_freqLen];
    thFreq = new double[_freqLen];
}

/// <summary>
/// Вычисление степени свободы, значения хи-квадрата и порогового уровня
/// по теоретической и эмпирической частотам.
/// </summary>
void ChiSqHistogram::CalcChiSq()
{
    if (dof == -1) {
        return;
    }
    chiSq = 0;
    pLevel = 0;
    dof = 0;

    int groupLen = 0;
    double sum_tf = 0;
    int sum_freq = 0;
    double* groupThFreq = new double [freqLen];
    int* groupEmpFreq = new int[freqLen];
    for (int i = 0; i < freqLen; i++) {
        sum_tf += thFreq[i];
        sum_freq += empFreq[i];
        if (sum_tf >= 5) {
            groupThFreq[groupLen] = sum_tf;
            groupEmpFreq[groupLen] = sum_freq;
            groupLen++;
            sum_tf = 0;
            sum_freq = 0;
        }
    }
    if (sum_tf) {
        // Будет инициализированно, так как там уже есть конкретные значения.
        groupThFreq[groupLen-1] += sum_tf;
        groupEmpFreq[groupLen-1] += sum_freq;
    };

    dof = groupLen - 1;
    for (int i = 0; i < groupLen; i++)
        chiSq += pow((groupThFreq[i] - groupEmpFreq[i]), 2) / groupThFreq[i];
    pLevel = 1 - pChi(chiSq, dof);
    delete[] groupThFreq;
    delete[] groupEmpFreq;
}

void ChiSqHistogram::CountThFreq(const Distribution& dis, int _samVol)
{
    double* thPr = dis.GetThProb();
    for (int i = 0; i < freqLen; i++) {
        thFreq[i] = thPr[i] * _samVol;
    }
}

void ChiSqHistogram::CountEmpFreq(const BaseSampleGenerator* bsg)
{
    for (int i = 0; i < freqLen; i++) {
        empFreq[i] = 0;
    }
    int* sample = bsg->GetSample();
    int samVol = bsg->GetSamVol();
    for (int k = 0; k < samVol; k++) {
        empFreq[sample[k]]++;
    }
}

std::ostream& operator<<(std::ostream& os, const ChiSqHistogram& csh)
{
    os << std::endl << "Значение хи-квадрата: " << csh.chiSq;
    os << ", число степеней свободы: " << csh.dof;
    os << ", пороговый уровень (p-level): " << csh.pLevel;
    os << "\nЭмпирические частоты: [" << csh.empFreq[0];
    for (int i = 1; i < csh.freqLen; i++) {
        os << ", " << csh.empFreq[i];
    }
    os << "]" << std::endl;
    os << "\nТеоретические частоты: [" << csh.thFreq[0];
    for (int i = 1; i < csh.freqLen; i++) {
        os << ", " << csh.thFreq[i];
    }
    os << "]" << std::endl;
    return os;
}
