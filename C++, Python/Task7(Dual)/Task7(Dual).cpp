// Условия 7-ой задачи из ТП :
// 6.
// Две структуры:
// 1) Фамилия, должность, зарплата
// 2) Номер отдела и массив из 1)
// Действия:
// - ввод из файла неупорядоченного списка из 2) структур
// - двойное упорядочивание по номеру отдела и по фамилии
// - поиск по номеру отдела
// - вывод на экран упорядоченного списка
// Как:
// - библиотечная функция сортировки по зад. критерию с использованием указателя на функцию сравнения;
// - сортировка структур по указателям
// - свой последовательный поиск

#include"student.h"
int main()
{   
    STUDENT stList[NSTUDENT] = {
        {"Jimmy", {1, 2}, 1.5},
        {"TK", {}, 0},
        {"Jimmy", {1, 2}, 1.5},
        {"Jane", {1, 3, 3, 4, 4}, 3.},
        {"Jimmy", {1, 2}, 1.5},
        {"TK", {}, 0},
        {"Bart", {2,3,3,3,3}, 0},
    };
    int stNum = 7;
    
    comput_avr(stList, stNum);
    to_file("stUnsort.txt", stList, stNum);
    sort(stList, stNum, cmp_name);
    to_file("stSort.txt", stList, stNum);
    std::cout << "Unsorted student list:\n";
    from_file("stUnsort.txt", stList, stNum);
    print_all(stList, stNum);
    // Sort tests
    std::cout << "Name sorted student list:\n";
    from_file("stSort.txt", stList, stNum);
    print_all(stList, stNum);
    std::cout << std::endl << "Mark sorted list:\n";
    sort(stList, stNum, cmp_mark);
    print_all(stList, stNum);
    std::cout << "Average mark sorted list:\n";
    sort(stList, stNum, cmp_name);
    sort(stList, stNum, cmp_avr);
    print_all(stList, stNum);


    // Search tests.
    STUDENT stL[NSTUDENT] = {
        {"MMA"},
        {"Fighter", {1,1,1,1,1}},
    };
    STUDENT stD[NSTUDENT] = {
        {"MMA"},
        {"Eerie"},
        {"Fighter", {1,1,1,1,1}},
        {"G-17"},

    };
    STUDENT stK[NSTUDENT] = {
        {"MMA"},
        {"Eerie"},
        {"Fighter", {1,1,1,1,1}},
        {"G-17"},
        {"Mary"},

    };
    
    STUDENT* stHere;
    std::cout << "Search function for Jane:\n";
    stHere = search({ "Jane" }, stList, stNum, cmp_name);
    if(stHere) print_one(*stHere);
    std::cout << "Search function for Jeremy:\n";
    stHere = search({ "Jeremy" }, stList, stNum, cmp_name);
    if (stHere) print_one(*stHere);
    else std::cout << "None\n\n";
    std::cout << "Search function 1:\n";
    stHere = search({ "Fighter" }, stL, 2, cmp_name);
    if (stHere) print_one(*stHere);
    std::cout << "Search function 2:\n";
    stHere = search({ "G-17" }, stD, 4, cmp_name);
    if (stHere) print_one(*stHere);
    std::cout << "Search function 3:\n";
    stHere = search({ "Mary" }, stK, 5, cmp_name);
    if (stHere) print_one(*stHere);
    std::cout << "Search function 4:\n";
    stHere = search({ "Kelly" }, stK, 5, cmp_name);
    if (stHere) print_one(*stHere);
    else std::cout << "None\n";
 }