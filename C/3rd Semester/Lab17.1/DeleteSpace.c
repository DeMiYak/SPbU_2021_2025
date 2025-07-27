//
// Created by vadim on 04.03.2022.
//

#include "DeleteSpace.h"

void DeleteSpace(char *s) {
    char *j = s;
    for (char *i = s; *i != '\0'; ++i) {
        while (*i == ' ' && *(i + 1) == ' ') {
            ++i;
        }
        *j = *i;
        ++j;
    }
    *j='\0';
}
