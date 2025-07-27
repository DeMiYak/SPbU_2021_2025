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
Что нужно сделать?
Полностью прочитать textf из жёсткого носителя
и перенести его в оперативную память.
Пользуясь ftell и fseek, вернуть позицию последнего элемента файла (длину файла),
затем прочитать в память, заведя строку динамически.
Перемещаться по строке, пользуясь strchr.
Два указателя перемещать по диезам,
пока они не дойдут до конца строки.

В функции getParam прочитать имя параметра
Если подходит: прочитать позицию и длину, вернуть истину.
Если не подходит: прочитать два int.
Если достиг конца строки: вернуть ложь.
*/