#include "types.h"

extern s32 D_00465D70[];

typedef struct T_003D19A0 {
    u8 pad0[0x20];
    s8 arr[1];
} T_003D19A0;

typedef struct S_003D19A0 {
    u8 pad0[0x18];
    T_003D19A0 *f18;
} S_003D19A0;

s8 InsectItemSetStat_3d19a0(S_003D19A0 *self, s32 i, s32 v)
{
    if (i < 0) goto zero;
    if (i < 6) goto g2;
zero:
    return 0;
g2:
    if (v < 0) {
        v = 0;
    } else if (D_00465D70[0] < v) {
        v = D_00465D70[0];
    }
    self->f18->arr[i] = v;
    return self->f18->arr[i];
}
