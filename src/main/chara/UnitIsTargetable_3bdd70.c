#include "types.h"

typedef struct P { u8 pad[0x408]; u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; u8 b4 : 1; u8 b5 : 1; u8 b6 : 1; u8 b7 : 1; } P;

extern s32 CharaIsTargetable_3b67c0(P *p);

s32 UnitIsTargetable_3bdd70(P *p)
{
    return CharaIsTargetable_3b67c0(p) != 0 ? p->b1 : 0;
}
