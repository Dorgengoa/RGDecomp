#include "types.h"

typedef struct P { u8 pad[0x4B4]; u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; u8 b4 : 1; u8 b5 : 1; u8 b6 : 1; u8 b7 : 1; } P;

void CharaSetCannotLeadMaybe_3ae330(P *p, s32 v)
{
    if (v != 0) p->b0 = 1;
    else p->b0 = 0;
}
