#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <random>
#include <string>

const int BUFFER_SIZE = 4096;

void CreateIndFile(const char* textName, const char* indName);

void ChangeTextByName(const char* textName, const char* indName, const char* cName, const char* cSentence);

bool getParam(const char* name, int& pos, int& len, FILE* fileName);

/*
��� ����� �������?
��������� ��������� textf �� ������� ��������
� ��������� ��� � ����������� ������.
��������� ftell � fseek, ������� ������� ���������� �������� ����� (����� �����),
����� ��������� � ������, ������ ������ �����������.
������������ �� ������, ��������� strchr.
��� ��������� ���������� �� ������,
���� ��� �� ������ �� ����� ������.

� ������� getParam ��������� ��� ���������
���� ��������: ��������� ������� � �����, ������� ������.
���� �� ��������: ��������� ��� int.
���� ������ ����� ������: ������� ����.
*/