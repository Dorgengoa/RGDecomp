/* rgp:protos */
#define RGP_SELF_ModelObjBaseInitNoMotion_186f60 1
#include "port/game_protos.h"
#line 1
/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] on a READ-ONLY extern.
   The barrier removed is the PROLOGUE's $sp stores, not a write to the
   symbol -- `const` + `__attribute__((section(".sdata")))` together, and
   on this unit EVERY gp float the function reads has to be const'd: doing
   only D_0047E040 is 4 bad, worse than the 2-bad park. */
#include "types.h"

/*rgp*/
extern f32 D_0047E040 __attribute__((section(".sdata")));
extern f32 D_0047E050 __attribute__((section(".sdata")));

void ModelObjBaseInitNoMotion_186f60(void *arg0)
{
    f32 floatA;
    f32 floatB;
    f32 negOne;

    ModelInit_151d50((void *)arg0);
    *(s32 *)((u8 *)arg0 + 0x1C4) = 0;
    *(s32 *)((u8 *)arg0 + 0x1C0) = 1;
    floatA = D_0047E040;
    *(s32 *)((u8 *)arg0 + 0x1C8) = 0;
    negOne = -1.0f;
    *(s32 *)((u8 *)arg0 + 0x1D0) = 0;
    floatB = D_0047E050;
    *(f32 *)((u8 *)arg0 + 0x1D4) = negOne;
    *(f32 *)((u8 *)arg0 + 0x1D8) = negOne;
    *(s32 *)((u8 *)arg0 + 0x1DC) = 0;
    *(s32 *)((u8 *)arg0 + 0x1E0) = 0;
    *(f32 *)((u8 *)arg0 + 0x1E4) = floatA;
    *(f32 *)((u8 *)arg0 + 0x1E8) = floatB;
    *(s32 *)((u8 *)arg0 + 0x1CC) = 0;
}
