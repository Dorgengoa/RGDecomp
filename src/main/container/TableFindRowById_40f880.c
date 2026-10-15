#include "types.h"

typedef struct E_0040f880 {
    u8 pad0[4];
    s32 f4;
    u8 pad8[52];
} E_0040f880;

typedef struct S_0040f880 {
    u8 pad0[0x7C];
    s16 f7C;
    u8 pad7E[0xE];
    E_0040f880 *f8C;
} S_0040f880;

E_0040f880 *TableFindRowById_40f880(S_0040f880 *self, s32 key)
{
    E_0040f880 *p = self->f8C;
    E_0040f880 *e;
    s32 n;
    s32 j;
    if (p == 0) goto zero;
    n = self->f7C;
    if (n > 0) goto ok;
zero:
    return 0;
ok:
    for (j = 0; j < n; j++) {
        e = &p[j];
        if (e == 0) goto zero2;
        if (e->f4 == key) return e;
    }
zero2:
    return 0;
}
