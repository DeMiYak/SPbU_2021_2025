
#include "Distribution.h"

/// <summary>
/// ������ ������������������� ������������� �
/// �������������� �������������
/// </summary>
/// <param name="_whBalls">����� ������</param>
/// <param name="_blBalls">׸���� ������</param>
/// <param name="_pickNum">����� ������������</param>
Distribution::Distribution(int _whBalls, int _blBalls, int _pickNum) : 
    whBalls(_whBalls), 
    blBalls(_blBalls), 
    pickNum(_pickNum), 
    thProb(nullptr)
{
    int condBall = blBalls >= pickNum && whBalls >= pickNum;
    int condPick = pickNum > 0 && blBalls > 0 && whBalls > 0;
    int error = 0;
    if (!condBall) {
        std::cout << "������: ����� ������������ �� ������ ������������ ����� ������ ��� ����� �������";
        error = 1;
    }
    if (!condPick) {
        std::cout << "������: ����� ������������, ������ � ����� ������� ������ ���� ������������� (>0)";
        error = 1;
    }
    if (error) {
        exit(1);
    }
    TheorProb();
}

/// <summary>
/// ������������� ��������� ��� �������������������� �������������
/// � ������ ������������� �����������
/// </summary>
/// <param name="_whBalls">����� ������</param>
/// <param name="_blBalls">׸���� ������</param>
/// <param name="_pickNum">����� ������������</param>
void Distribution::SetParameters(int _whBalls, int _blBalls, int _pickNum)
{
    whBalls = _whBalls;
    blBalls = _blBalls;
    pickNum = _pickNum;
    int condBall = blBalls >= pickNum && whBalls >= pickNum;
    int condPick = pickNum > 0 && blBalls > 0 && whBalls > 0;
    int error = 0;
    if (!condBall) {
        std::cout << "������: ����� ������������ �� ������ ������������ ����� ������ ��� ����� �������";
        error = 1;
    }
    if (!condPick) {
        std::cout << "������: ����� ������������, ������ � ����� ������� ������ ���� ������������� (>0)";
        error = 1;
    }
    if (error) {
        exit(1);
    }
    TheorProb();
}

/// <summary>
/// ���������� ��� �������������
/// </summary>
/// <returns>��������� �� ��� �������������</returns>
const wchar_t* Distribution::GetName()
{
    return L"������������������� �������������";
}


/// <summary>
/// ������� ������������� ����������� �������������
/// </summary>
void Distribution::TheorProb()
{
    delete[] thProb;
    thProb = new double[pickNum + 1];
    int totalBalls = whBalls + blBalls;
    double prob = 1;

    for (int k = 0; k < pickNum; k++) prob *= double(blBalls - k) / (totalBalls - k);
    thProb[0] = prob;
    for (int i = 1; i <= pickNum; i++) {
        int k = i - 1;
        prob = prob * (whBalls - k) * (pickNum - k) / ((k + 1) * (blBalls - pickNum + k + 1));
        thProb[i] = prob;
    }
}
