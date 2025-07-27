#include "files.h";

// creates index file from text file
void CreateIndFile(const char* textName, const char* indName)
{
    FILE* indf = fopen(indName, "wb");
    FILE* textf = fopen(textName, "r");
    
    // New: copying the text from textf to char array
    fseek(textf, 0, SEEK_END);
    int len = ftell(textf);
    char* line = new char[len];
    fseek(textf, 0, SEEK_SET);
    fread(line, sizeof(char), len, textf);

    // New: reading lines with two pointers
    char* ptrF = line, *ptrS = line;
    while (ptrF = strchr(ptrF, '#')) {
        // Read param and move a second pointer
        fwrite(ptrS, sizeof(char), 2, indf);
        ptrS += 2;

        // Write position and sentence length
        int pos = ptrS - line, len = ptrF - ptrS;
        fwrite(&pos, sizeof(int), 1, indf);
        fwrite(&len, sizeof(int), 1, indf);
        
        // Move first pointer to avoid #
        // and assign second pointer to the first one 
        ++ptrF;
        ptrS = ptrF;
    }
    delete[] line;
    fclose(indf);
    fclose(textf);
}



// returns the parameter of the line before diez
bool getParam(const char* name, int& pos, int& len, FILE* fileName) {
    while (!feof(fileName)) {
        char fName[3];
        fName[2] = '\0';
        fread(fName, sizeof(char), 2, fileName);
        if (!strcmp(name, fName)) {
            // New: pos, len moved
            fread(&pos, sizeof(int), 1, fileName);
            fread(&len, sizeof(int), 1, fileName);
            return true;
        }
        // New. Moving a pointer
        fseek(fileName, 2*sizeof(int), SEEK_CUR); 
    }
    return false;
}

// changes one of the line in the text file using ind file 
// by implementing parameter and sentence
void ChangeTextByName(const char* textName, const char* indName, const char* cName, const char* cSentence) {
    int pos, len, sentlen = strlen(cSentence);
    FILE* indf = fopen(indName, "rb");
    FILE* textf = fopen(textName, "r+");
    if (getParam(cName, pos, len, indf)) {

        // New: added block reading
        char* replacer = new char[len];
        strncpy(replacer, cSentence, len);
        for (int i = sentlen; i < len; replacer[i++] = ' ');
        fseek(textf, pos, SEEK_SET);
        fwrite(replacer, sizeof(char), len, textf);
        delete[] replacer;
        printf("\nSuccess\n");
    }
    else printf("\nFailure\n");
    fclose(indf);
    fclose(textf);
}