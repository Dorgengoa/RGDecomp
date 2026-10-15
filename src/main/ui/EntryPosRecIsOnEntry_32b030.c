#include "types.h"

typedef struct O_0032b030 {
    u8 pad2C[0x2C];
    s32 f2C;
} O_0032b030;

typedef struct S_0032b030 {
    u8 padC[0xC];
    O_0032b030 *fC;
} S_0032b030;

s32 EntryPosRecIsOnEntry_32b030(S_0032b030 *self, O_0032b030 *other)
{
    s32 t;
    if (other == 0) goto zero;
    if (self->fC != 0) goto ok;
zero:
    return 0;
ok:
    t = *(volatile s32 *)&self->fC->f2C;
    return other->f2C == t;
}
