#include "types.h"
typedef struct S003d9ff0 {
    u8 pad[0xE0A];
    s16 cnt;                  /* +0xE0A */
} S003d9ff0;

s16 VariantPoolScopeLeave_3d9ff0(S003d9ff0 *s)
{
    s16 v;
    s16 r;

    v = s->cnt;
    if (v <= 0) {
        r = 0;
    } else {
        v = v - 1;
        s->cnt = v;
        r = v;
    }
    return r;
}
