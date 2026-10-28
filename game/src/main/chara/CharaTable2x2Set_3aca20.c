/* rgp:protos */
#define RGP_SELF_CharaTable2x2Set_3aca20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P { u8 pad0[0x260]; f32 f260[2][2]; } P;

void CharaTable2x2Set_3aca20(P *p, s32 a, s32 b, f32 v)
{
    if (a < 0 || 2 <= a || b < 0 || 2 <= b) return;
    p->f260[a][b] = v;
}
