#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

typedef struct node node;

void arrFill(char *, size_t); // ������� ���������� �������

/*
int compare(char *, char *); // ������� ��������� ���� ����
*/

void whereTo(const char *, node *); // ������� ���������� ������ �������

node *mapInsert(char *, node *);

node *createMap(char **);

node *createNode(char *);

size_t transferArr(char *, char **);

void printStr(node *, size_t *);

#endif // HEAD_H_INCLUDED
