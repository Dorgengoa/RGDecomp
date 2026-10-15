#include "types.h"

typedef struct P { u8 pad0[0x270]; f32 f270[2][2]; } P;

void CharaTable2x2Set_3ac9d0(P *p, s32 a, s32 b, f32 v)
{
    if (a < 0 || 2 <= a || b < 0 || 2 <= b) return;
    p->f270[a][b] = v;
}
