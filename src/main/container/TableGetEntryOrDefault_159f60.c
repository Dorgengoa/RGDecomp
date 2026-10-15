#include "types.h"

typedef struct E_00159f60 { u8 b[16]; } E_00159f60;

typedef struct S_00159f60 {
    u8 padC[0xC];
    s32 fC;
    u8 pad10[0xC];
    E_00159f60 *f1C;
    u8 f20[1];
} S_00159f60;

void *TableGetEntryOrDefault_159f60(S_00159f60 *self, s32 i)
{
    if (i != 0x7FFF) goto g1;
    return self->f20;
g1:
    if (i < 0) goto zero;
    if (i < self->fC) goto ok;
zero:
    return 0;
ok:
    return &self->f1C[i];
}
