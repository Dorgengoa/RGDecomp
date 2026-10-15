#include "types.h"

typedef struct Obj_FUN_00162b20 {
    s32 n;
    s32 a[0x30];
    s32 b[0x30];
    s32 c[0x60];
    s32 d[0x1];
} Obj_FUN_00162b20;

void TexAnimSeqResetAll_162b20(Obj_FUN_00162b20 *o)
{
    s32 i;

    for (i = 0; i < o->n; i++) {
        if (i >= 0 && i < o->n) {
            o->a[i] = 0;
            o->c[i] = o->b[i];
            o->d[i] = 0;
        }
    }
}
