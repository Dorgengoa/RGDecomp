#include "types.h"
typedef struct R4 { u8 a, b, c, d; } R4;
typedef struct T { u8 pad0[4]; u8 *base; s32 n; } T;

static inline s32 g4(u8 *p)
{
    R4 r;
    if (*(s8 *)p == 2) {
        r.a = p[1];
        r.b = p[2];
        r.c = p[3];
        r.d = p[4];
        return *(s32 *)&r;
    }
    return 0;
}
s32 ScriptCallGetArgStr_302940(T *arg0, s32 arg1)
{
    u8 *p;
    if (arg0->base == NULL || arg1 < 0 || arg0->n <= arg1) {
        p = NULL;
    } else {
        p = arg0->base + arg1 * 5;
    }
    if (p == NULL) {
        return 0;
    }
    return g4(p);
}
