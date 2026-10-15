#include "types.h"

typedef struct Ent {
    const char *name;
    s16         len;
    s16         pad06;
} Ent;

extern Ent D_0044EB20[];
extern s32 strncmp(const char *a, const char *b, s32 n);

Ent *TextSymbolTagFind_26efe0(const char *str)
{
    Ent *e;
    const char *s;

    if (str == 0) {
        return 0;
    }
    for (e = D_0044EB20; (s = e->name) != 0; e++) {
        if (*str == *s) {
            if (strncmp(str, *(const char **)e, e->len) == 0) {
                return e;
            }
        }
    }
    return 0;
}
