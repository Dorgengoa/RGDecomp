/* rgp:protos */
#define RGP_SELF_CharaEffEntrySetWorkFlt_230160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void CharaEffEntrySetWorkFlt_230160(void *p, s32 i, f32 v)
{
    if (i < 0 || i >= 6) return;
    *(u16 *)((s32)p + 0x60) |= 0x20;
    *(f32 *)((s32)p + i * 4) = v;
}
