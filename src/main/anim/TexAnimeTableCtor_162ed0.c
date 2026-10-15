#include "types.h"

typedef struct Obj_FUN_00162ed0 {
    s32 n;
    s32 a[0x30];
    s32 b[0x30];
    s32 c[0x30];
    s32 e[0x30];
    s32 d[0x30];
} Obj_FUN_00162ed0;

Obj_FUN_00162ed0 *TexAnimeTableCtor_162ed0(Obj_FUN_00162ed0 *o)
{
    s32 i;

    o->n = 0x30;
    for (i = 0; i < 0x30; i++) {
        if (i < 0) {
            continue;
        }
        if (i >= o->n) {
            continue;
        }
        if (i >= 0 && i < o->n) {
            o->a[i] = 0;
            o->c[i] = o->b[i];
            o->d[i] = 0;
        }
        o->b[i] = 0;
        o->c[i] = 0;
        o->e[i] = 0;
        o->d[i] = 0;
    }
    return o;
}
