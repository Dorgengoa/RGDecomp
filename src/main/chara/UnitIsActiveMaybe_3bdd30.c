#include "types.h"

typedef struct P { u8 pad[0x408]; u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; u8 b4 : 1; u8 b5 : 1; u8 b6 : 1; u8 b7 : 1; } P;

extern s32 CharaIsNotDead_3b66f0(P *p);

s32 UnitIsActiveMaybe_3bdd30(P *p)
{
    return CharaIsNotDead_3b66f0(p) != 0 ? p->b2 : 0;
}
