/* rgp:protos */
#define RGP_SELF_CharaSetStatA8_3b7b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P { u8 pad0[0xA8]; s16 fA8[4][2]; } P;

void CharaSetStatA8_3b7b60(P *p, s32 a, s16 v, s32 b)
{
    if (b >= 0 && b < 2 && a >= 0 && a < 4) {
        p->fA8[a][b] = v;
    }
}
