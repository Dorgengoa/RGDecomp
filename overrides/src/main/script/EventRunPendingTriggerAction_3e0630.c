/* rg-override: replaces game/src/main/script/EventRunPendingTriggerAction_3e0630.c sha256 50576b380249b18f3550d2a110a8db4f470bd6f248c4a992af870015e8a94d5d
 * why: `s` (the 64-entry variant pool, sp+0x20) was declared 0xE08 bytes; VariantPoolReset_3e01f0 /
 * ScriptExecOpStream_3dffa0 write its count / flag words at +0xE08..+0xE0C (retail: the pool runs to the
 * frame top, 0xE10 bytes) -- the same pool and bug as CharaResolveActionHitMaybe_3b28d0's L430
 * (static census tools/census/localsize_census.py, lane localsize 2026-11-09).  Adds the 8-byte tail. */
/* rgp:protos */
#define RGP_SELF_EventRunPendingTriggerAction_3e0630 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_loop_invariants off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_0048399C;
extern u8 D_004E9740[];

s32 EventRunPendingTriggerAction_3e0630(void) {
    struct { u8 a[8]; u8 b[0xE00]; u8 tail[8]; } s;   /* rg-override: 0xE10 bytes (sp+0x20..0xE30) */
    u8 *p;

    if (D_0048399C == 0) {
        return 0;
    }
    p = s.b;
    do {
        VariantInit_36ff00((u32)p);
        p += 0x38;
    } while ((u32)p < (u32)(s.b + 0xE00));
    VariantPoolReset_3e01f0(s.a);
    ScriptExecOpStream_3dffa0(s.a, *(s16 *)((u8 *)D_0048399C + 0xE),
                 *(s32 *)((u8 *)D_0048399C + 0x1C), D_004E9740);
    D_0048399C = 0;
    ActionPacketClear_3e3e90(D_004E9740);
    return 1;
    return 0;
}
