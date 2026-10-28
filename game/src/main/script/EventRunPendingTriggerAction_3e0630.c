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
    struct { u8 a[8]; u8 b[0xE00]; } s;
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
