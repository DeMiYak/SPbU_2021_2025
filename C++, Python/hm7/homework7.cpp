#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int NSIMB = 10;
const int NSTUDENT = 100;

const char STOP_CHAR = '0';

struct Person {
	char name[NSIMB];
	char surname[NSIMB];
	int age;
};

struct Student {
	Person student;
	int group;
};
	

// ввод студентов, пока не превысятся пределы массива или не будет введён спец символ для остановки
int input_all(Student* l) {
    int n = 0;
    char stop_char = ' ';
    while (n < NSTUDENT && stop_char != STOP_CHAR) {
        cout << "Enter student name: ";
        cin >> l[n].student.name;

        cout << "Enter student surname: ";
        cin >> l[n].student.surname;

        cout << "Enter student age: ";
        cin >> l[n].student.age;

        cout << "Enter student group: ";
        cin >> l[n].group;

        cout << "Enter " << STOP_CHAR << " to stop: ";
        cin >> stop_char;
        ++n;
    }

    return n;
}


// вывод студентов в консоль
void print_one(const Student& ls) {
    cout << "------------------------" << endl;
    cout << "Student name: " << ls.student.name << endl;
    cout << "Surname:" << setw(14-8) << " " << ls.student.surname << endl;
    cout <<"Age:" << setw(10) << " " << ls.student.age << endl;
    cout <<"Group:" << setw(14 - 6) << " " << ls.group << endl;
    cout << "------------------------" << endl;
}

void print_all(const Student* l, const int n) {
    for (int i = 0; i < n; ++i) {
        print_one(l[i]);
    }
    cout << endl;
}

void print_all(Student** l, const int n) {
    for (int i = 0; i < n; ++i) {
        print_one(*l[i]);
    }
    cout << endl;
}


// сортировка студентов
void fill_pointer_arr(Student* in, Student** out, const int n) {
    for (int i = 0; i < n; ++i)
        out[i] = &in[i];
}

// сортировка пузырьком
void sort(Student** l, const int n, int (*compare)(const Student*, const Student*)) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(l[j], l[j + 1]) > 0) {
                Student* tmp = l[j + 1];
                l[j + 1] = l[j];
                l[j] = tmp;
            }
        }
    }
}

int cmp_name(const Student* s1, const Student* s2) {
    return strncmp(s1->student.surname, s2->student.surname, NSIMB);
}

int cmp_age(const Student* s1, const Student* s2) {
    if (s1->student.age > s2->student.age)
        return 1;
    else if (s1->student.age == s2->student.age)
        return 0;
    return -1;
}

int cmp_group(const Student* s1, const Student* s2) {
    if (s1->group > s2->group)
        return 1;
    else if (s1->group == s2->group)
        return 0;
    return -1;
}



// последовательный поиск
Student* search(Student& ls, Student** l, const int n, int (*compare)(const Student*, const Student*)) {
    Student* pl = &ls;
    for (int i = 0; i < n; ++i)
    {
        if (!compare(pl, l[i]))
            return l[i];
    }

    return nullptr;
}


void to_file(const char* fname, Student** l, int n) {
    ofstream out(fname, ios::binary);
    for (int i = 0; i < n; ++i)
    {
        out.write(reinterpret_cast<const char*>(*(l+i)), sizeof(Student));
    }
}

void from_file(const char* fname, Student* l, int& pn) {
    ifstream in(fname);
    if (!in.is_open()) {
        cerr << "Error in opening file " << endl;
        return;
    }

    pn = 0;
    while (pn != NSTUDENT) {
        in.read(reinterpret_cast<char*>(l+pn), sizeof(Student));
        if (in.eof())
            return;
        ++pn;
    }
}


int main()
{
    Student studs[NSTUDENT];
    int n = input_all(studs);
    cout << endl << "All students:" << endl;
    print_all(studs, n);


    cout << endl << "Students sorted by surname:" << endl;
    Student* pstuds[NSTUDENT]; fill_pointer_arr(studs, pstuds, n);
    sort(pstuds, n, cmp_name);
    print_all(pstuds, n);
    to_file("sorted_by_surname.txt", pstuds, n);

    cout << "Find student with surname Gonzalez: " << endl;
    Student s = Student{ {"", "Gonzalez", 4}, 1 };
    Student* req = search(s, pstuds, n, cmp_name);
    if (req != nullptr) print_one(*req);
    else cout << "There are no students on this request" << endl;

    cout << "Find student with surname AAAAA: " << endl;
    s = Student{ {"", "AAAAA", 4}, 1 };
    req = search(s, pstuds, n, cmp_name);
    if (req != nullptr) print_one(*req);
    else cout << "There are no students on this request" << endl;


    cout << endl << "Students sorted by age:" << endl;
    sort(pstuds, n, cmp_age);
    print_all(pstuds, n);
    to_file("sorted_by_age.txt", pstuds, n);

    cout << "Find a student who is 10 years old : " << endl;
    s = Student{ {"", "AAAAA", 10}, 1 };
    req = search(s, pstuds, n, cmp_age);
    if (req != nullptr) print_one(*req);
    else cout << "There are no students on this request" << endl;

    cout << "Find a student who is 21 years old : " << endl;
    s = Student{ {"", "AAAAA", 21}, 1 };
    req = search(s, pstuds, n, cmp_age);
    if (req != nullptr) print_one(*req);
    else cout << "There are no students on this request" << endl;
    
    cout << endl << "Students sorted by group:" << endl;
    sort(pstuds, n, cmp_group);
    print_all(pstuds, n);
    to_file("sorted_by_group.txt", pstuds, n);



    cout << endl << endl << "Students saved to file and loaded again:" << endl;
    cout << endl << "Students sorted by surname:" << endl;
    from_file("sorted_by_surname.txt", studs, n);
    print_all(studs, n);

    cout << endl << "Students sorted by age:" << endl;
    from_file("sorted_by_age.txt", studs, n);
    print_all(studs, n);

    cout << endl << "Students sorted by group:" << endl;
    from_file("sorted_by_group.txt", studs, n);
    print_all(studs, n);

}


/* Тестовые студенты

Emily
Taylor
20
2
1
Harry
Jackson
20
4
1
Bob
Smith
20
1
1
Jack
Gonzalez
18
1
1
Alice
Jonson
19
2
1
Ivan
Lopatkov
21
4
1
Grace
Brown
19
3
1
Charles
Davis
18
1
1
Loki
Amberdolf
20
1
1
Barbara
Miller
20
3
1
Frank
Thomas
18
1
1
Isabella
Lopez
19
2
1
Nastya
Zimina
19
2
1
David
Wilson
19
4
0


*/