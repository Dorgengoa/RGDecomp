#include "types.h"

typedef struct E_00422830 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x16];
} E_00422830;

typedef struct S_00422830 {
    u8 pad0[0x7C];
    s16 f7C;
    u8 pad7E[0xE];
    E_00422830 *f8C;
} S_00422830;

E_00422830 *ProgressTableFindRowMaybe_422830(S_00422830 *self, s32 key)
{
    E_00422830 *p = self->f8C;
    s32 n;
    s32 j;
    if (p == 0) goto zero;
    n = self->f7C;
    if (n > 0) goto ok;
zero:
    return 0;
ok:
    j = 0;
    while (j < n) {
        if (p->f8 == key) return p;
        j++;
        p++;
    }
    return 0;
}
