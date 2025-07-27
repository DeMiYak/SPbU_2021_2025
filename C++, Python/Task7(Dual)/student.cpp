#include"student.h"
int input_all(STUDENT* l) {
    for (int i = 0; i < NSTUDENT; ++i) {
        // Stop condition: the name is empty ('\n')
        std::cin.getline(l[i].name, NSYMB);

        if (!strlen(l[i].name)) return i;

        for (int j = 0; j < NMARK; ++j) std::cin >> l[i].mark[j];
        std::cin.get();
    }
    return NSTUDENT;
}

void comput_avr(STUDENT* l, int n) {
    for (int i = 0; i < n; ++i) {
        int sum = 0, count = 0;
        for (int j = 0; j < NMARK; ++j) {
            int temp = l[i].mark[j];
            if (MAXMARK >= temp && temp > NULLMARK) {
                sum += temp;
                ++count;
            }
            else l[i].mark[j] = NULLMARK;
        }
        if (count) l[i].avr = double(sum) / count;
        else l[i].avr = NULLMARK;
    }
}

int cmp_name(const STUDENT& sOne, const STUDENT& sTwo) {
    return strcmp(sOne.name, sTwo.name);
}

int cmp_mark(const STUDENT& sOne, const STUDENT& sTwo) {
    for (int i = 0; i < NMARK; ++i) {
        if (sOne.mark[i] < sTwo.mark[i]) return -1;
        else if (sOne.mark[i] > sTwo.mark[i]) return 1;
    }
    return 0;
}

int cmp_avr(const STUDENT& sOne, const STUDENT& sTwo) {
    if (sOne.avr < sTwo.avr) return -1;
    else if (sOne.avr > sTwo.avr) return 1;
    return 0;
}

void sort(STUDENT* l, int n, int (*compare)(const STUDENT&, const STUDENT&)) {
    for (int i = n - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (compare(l[j], l[j + 1]) == 1) {
                STUDENT temp = l[j];
                l[j] = l[j + 1];
                l[j + 1] = temp;
            }
        }
    }
}

void to_file(const char* fname, STUDENT* l, int n) {
    FILE* fst = fopen(fname, "rb");
    if (!fst) exit(1);
    fclose(fst);
    fst = fopen(fname, "wb");
    fwrite(&n, sizeof(int), 1, fst);
    fwrite(l, sizeof(STUDENT), n, fst);
    fclose(fst);
}

void from_file(const char* fname, STUDENT* l, int& pn) {
    FILE* fst = fopen(fname, "rb");
    if (!fst) exit(1);
    fread(&pn, sizeof(int), 1, fst);
    fread(l, sizeof(STUDENT), pn, fst);
    fclose(fst);
}

STUDENT* search(const STUDENT& ls, STUDENT* l, int n, int (*compare)(const STUDENT&, const STUDENT&)) {
    // compare(l[0], ls) == compare(ls, l[n-1]) - checks if ls is within [l[0], l[n-1]].
    if (!n || compare(l[0], ls) == compare(ls, l[n - 1])) return nullptr;
    sort(l, n, compare);
    int start = 0, mid = n / 2, end = n;

    // if start is lower than end - swap them
    // to do a binsearch
    if (compare(l[start], l[end]) < 0) {
        end = 0;
        start = n;
    }
    
    int seVal;
    
    // binsearch
    while (start != end) {
        seVal = compare(ls, l[mid]);
        if (seVal == 1) start = mid + 1;
        else if (seVal == -1) end = mid - 1;
        else return &l[mid];
        mid = (start + end) / 2;
    }

    // in case start == end
    if (!compare(ls, l[start])) return &l[start];
    return nullptr;
}

void print_one(const STUDENT& ls) {
    std::cout << "Name: " << ls.name << std::endl;
    std::cout << "Grades: "; std::copy(ls.mark, ls.mark + NMARK, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nAverage grade: " << ls.avr << std::endl << std::endl;
}

void print_all(STUDENT* l, int n) {
    for (int i = 0; i < n; ++i) print_one(l[i]);
}
