/* rgp:protos */
#define RGP_SELF_OverlayCdSeek_1c32b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma tailcall off

extern s32 D_004A6F80[8];
extern void sceCdSeek_12a908(s32 v);

void OverlayCdSeek_1c32b0(s32 i)
{
    if (i < 0 || i >= 7) return;
    sceCdSeek_12a908(D_004A6F80[i]);
}
