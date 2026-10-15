#include "types.h"

s32 NameEqualBeforeDashes_14c710(const char *a, const char *b)
{
    const char *p;
    const char *q;
    s32 ca;
    s32 cb;
    s32 i;
    char c;

    if (a == 0 || b == 0) {
        return 0;
    }
    p = a;
    q = b;
    ca = 0;
    cb = 0;
    while ((c = *p) != 0) {
        if (c == '-' && p[1] == '-') {
            break;
        }
        ca++;
        p++;
    }
    while ((c = *q) != 0) {
        if (c == '-' && q[1] == '-') {
            break;
        }
        cb++;
        q++;
    }
    if (ca != cb) {
        return 0;
    }
    for (i = 0; i < ca; a++, b++, i++) {
        if (*a != *b) {
            return 0;
        }
    }
    return 1;
}
