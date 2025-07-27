#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED

/**
* Функция записи строки
* останавливается при нажатии Enter (символа новой строки)
*/
char *writeLine();

/**
* Функция прочтения строки с нахождением
* нужных слов
*/
size_t readLine(char *line, char key);

#endif // READ_H_INCLUDED
