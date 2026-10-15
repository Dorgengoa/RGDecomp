#include "types.h"

typedef struct P { u8 pad0[0x840]; s8 f840[0x40]; } P;

s32 ItemGroupUnlockProgressGet_3cbc20(P *p, s32 i)
{
    if (i < 0 || 0x40 <= i) return -1;
    return p->f840[i];
}
