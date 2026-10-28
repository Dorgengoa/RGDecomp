/* rgp:protos */
#define RGP_SELF_ModelObjBaseInit_1867b0 1
#include "port/game_protos.h"
#line 1
/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] -- the gp float load
   retail schedules ABOVE the prologue's `sq $sN,K($sp)` stores.  Fires on a
   READ-ONLY extern (the barrier is the $sp stores, not a write), and it is
   PER-EXTERN: const the symbol whose load is misplaced, not every gp float
   the unit reads. */
#include "types.h"

/*rgp*/
/*rgp*/
extern f32 D_0047E040 __attribute__((section(".sdata")));
extern f32 D_0047E050 __attribute__((section(".sdata")));

void ModelObjBaseInit_1867b0(void *arg0)
{
    f32 floatA;
    f32 floatB;
    s32 negOne;

    ModelInit_151d50((void *)arg0);
    *(s32 *)((u8 *)arg0 + 0x1C4) = 0;
    *(s32 *)((u8 *)arg0 + 0x1C0) = 1;
    floatA = D_0047E040;
    negOne = 0xBF800000;
    *(s32 *)((u8 *)arg0 + 0x1C8) = 0;
    *(s32 *)((u8 *)arg0 + 0x1D0) = 0;
    floatB = D_0047E050;
    *(s32 *)((u8 *)arg0 + 0x1D4) = negOne;
    *(s32 *)((u8 *)arg0 + 0x1D8) = negOne;
    *(s32 *)((u8 *)arg0 + 0x1DC) = 0;
    *(s32 *)((u8 *)arg0 + 0x1E0) = 0;
    *(f32 *)((u8 *)arg0 + 0x1E4) = floatA;
    *(f32 *)((u8 *)arg0 + 0x1E8) = floatB;
    *(s32 *)((u8 *)arg0 + 0x1CC) = 0;
    MotionListInit_1726f0((u8 *)arg0 + 0x1F0);
}
