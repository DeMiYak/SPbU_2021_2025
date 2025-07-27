//
// Created by vadim on 18.03.2022.
//

#include "StrToArr.h"
#include <string.h>

size_t ToArr(char *str, char *arr[100]) {
    const char del[10] = ". ,/:;?!\n";
    char *words = strtok(str, del);
    size_t i = 0;
    while (words != NULL) {
        arr[i] = words;
        ++i;
        words = strtok(NULL, del);
    }
    return i;
}