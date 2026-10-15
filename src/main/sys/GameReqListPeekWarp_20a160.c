#include "types.h"

typedef struct T_0020a160 {
    s32 f0;
    u8 pad4[4];
    s32 f8;
    s16 fC;
    s16 fE;
    s16 f10;
    u8 f12;
} T_0020a160;

typedef struct O_0020a160 {
    s32 f0;
    s16 f4;
    s16 f6;
    s16 f8;
    u8 fA;
} O_0020a160;

typedef struct S_0020a160 {
    T_0020a160 *f0;
    s16 f4;
} S_0020a160;

s32 GameReqListPeekWarp_20a160(S_0020a160 *self, O_0020a160 *out)
{
    T_0020a160 *p = self->f0;
    if (p == 0) goto zero;
    if (self->f4 > 0) goto g1;
zero:
    return 0;
g1:
    if (p->f0 == 11) goto ok;
    return 0;
ok:
    if (out != 0) {
        out->f0 = p->f8;
        out->f4 = p->fC;
        out->f6 = p->fE;
        out->f8 = p->f10;
        out->fA = p->f12;
    }
    return 1;
}
