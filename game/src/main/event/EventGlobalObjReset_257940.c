/* rgp:protos */
#define RGP_SELF_EventGlobalObjReset_257940 1
#include "port/game_protos.h"
#line 1
/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] on a READ-ONLY extern --
   the gp `lwc1 D_0047DADC` has to schedule above the prologue store. */
#include "types.h"
#include "vec.h"

/*rgp*/
extern f32 D_0047DADC __attribute__((section(".sdata")));

void EventGlobalObjReset_257940(void *arg0)
{
    s32 var_5;
    f32 temp_f0;
    u8 *temp_4;

    *(s32 *)((u8 *)arg0 + 0x0) = 0;
    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    *(s32 *)((u8 *)arg0 + 0x10) = 0;
    *(s32 *)((u8 *)arg0 + 0x18) = 0;
    *(s32 *)((u8 *)arg0 + 0x14) = 0;
    *(u32 *)((u8 *)arg0 + 0x1C) = 0x3F800000;
    *(s32 *)((u8 *)arg0 + 0x24) = 0;
    *(s32 *)((u8 *)arg0 + 0x20) = 0;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(s32 *)((u8 *)arg0 + 0x28) = 0;
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    *(s32 *)((u8 *)arg0 + 0x34) = 0;
    *(s32 *)((u8 *)arg0 + 0x38) = 1;
    *(s32 *)((u8 *)arg0 + 0x3C) = 0;
    *(s32 *)((u8 *)arg0 + 0x40) = 0;
    *(s32 *)((u8 *)arg0 + 0x44) = 0;
    *(s32 *)((u8 *)arg0 + 0x48) = 0;
    EventGlobalObjSubReset_257a50((u8 *)arg0 + 0x4C);
    *(s32 *)((u8 *)arg0 + 0x6C) = 0;
    *(s32 *)((u8 *)arg0 + 0x68) = 2;
    *(s32 *)((u8 *)arg0 + 0x70) = 0;
    temp_f0 = D_0047DADC;
    var_5 = 0;
    *(s32 *)((u8 *)arg0 + 0x74) = 0;
    *(f32 *)((u8 *)arg0 + 0x78) = temp_f0;
    do {
        temp_f0 = (f32)var_5;
        temp_4 = (u8 *)arg0 + (var_5 * 0x10);
        *(u128 *)(temp_4 + 0x80) = 0;
        var_5 += 1;
        *(u128 *)(temp_4 + 0x280) = 0;
        *(u128 *)(temp_4 + 0x480) = 0;
        *(f32 *)(temp_4 + 0x8C) = temp_f0;
        *(f32 *)(temp_4 + 0x28C) = temp_f0;
        *(f32 *)(temp_4 + 0x48C) = temp_f0;
    } while (var_5 < 0x20);
}
