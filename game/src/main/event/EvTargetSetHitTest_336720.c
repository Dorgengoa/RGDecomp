/* rgp:protos */
#define RGP_SELF_EvTargetSetHitTest_336720 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
s32 EvTargetSetHitTest_336720(void *p, void *q)
{
    s32 r;

    if (TargetRefGetObj_2e7110((void *)((s32)p + 0x30)) != 0) {
        r = XformPointInBoxSym_2e7950((void *)((s32)p + 0xC0), q,
                         *(f32 *)((s32)p + 0x108),
                         *(f32 *)((s32)p + 0x10C),
                         *(f32 *)((s32)p + 0x110));
        return r != 0;
    }
    return 0;
}
