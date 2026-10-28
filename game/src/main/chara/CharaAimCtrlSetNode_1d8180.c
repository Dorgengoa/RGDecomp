/* rgp:protos */
#define RGP_SELF_CharaAimCtrlSetNode_1d8180 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct A1D8180 { u8 pad000[0x4]; s32 m04; } A1D8180;
typedef struct P1D8180 { u8 pad000[0x18]; A1D8180 *m18; s32 m1C; } P1D8180;
void CharaAimCtrlSetNode_1d8180(P1D8180 *p, A1D8180 *v)
{
    p->m18 = v;
    p->m1C = 0;
    if (p->m18 != 0) {
        p->m1C = p->m18->m04;
    }
}
