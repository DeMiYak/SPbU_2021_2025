#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

#include "db.h"
#include "srt.h"

int main()
{
    friendr *db;
    size_t n;
    size_t s = 1 , e = 5;
    n = 0;

    db = init_DB();

    fill_DB_from_file(db, "friends.txt", &n);

    show_DB(db, &n);

    rect_diagram(db, s, e, n);

    return 0;
}
