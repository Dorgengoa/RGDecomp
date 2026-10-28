/* rgp:protos */
#define RGP_SELF_CharaEvObjContactFlag10Related_2148a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P { u8 pad0[0xB5C]; u32 fB5C; s16 fB60; s16 fB62; } P;

s32 CharaEvObjContactFlag10Related_2148a0(P *p)
{
    return p->fB60 >= 0 && p->fB5C != 0 && (p->fB62 & 0x10) != 0;
}
