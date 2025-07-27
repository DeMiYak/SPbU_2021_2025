#include "files.h"
// Punt Gun

int main()
{
    CreateIndFile("Text.txt", "IndexFile.txt");
    ChangeTextByName("Text.txt", "IndexFile.txt", "bi", "Jeronimo-o-o-o");
    ChangeTextByName("Text.txt", "IndexFile.txt", "pp", "Europa Barbarorum, quius puella pulchra est?Europa Barbarorum, quius puella pulchra est?");
}