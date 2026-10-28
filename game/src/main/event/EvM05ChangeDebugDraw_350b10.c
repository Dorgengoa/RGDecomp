/* rgp:protos */
#define RGP_SELF_EvM05ChangeDebugDraw_350b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

extern f32 D_0047F790;
extern f32 D_0047F794;
extern f32 D_0047F798;
extern f32 D_0047F79C;

void EvM05ChangeDebugDraw_350b10(void *arg0, s32 arg1)
{
    f32 sp[4] __attribute__((aligned(16)));
    s32 temp4;
    s32 var17;
    s32 var16;
    s32 cond1;

    temp4 = *(s32 *)((u8 *)arg0 + 0xD0);
    cond1 = !(temp4 & 0x80000000);
    if (cond1 && (temp4 & 0x02000000) && (u8 *)arg0 + 0xE0 != NULL) {
        sp[0] = D_0047F790;
        sp[1] = D_0047F794;
        sp[2] = D_0047F798;
        sp[3] = D_0047F79C;
        var17 = *(s32 *)((u8 *)arg0 + 0xE8);
        var16 = 0;
        while (var16 < *(s32 *)((u8 *)arg0 + 0xEC)) {
            EvTargetDebugDraw_352440(var17, arg1, *(s32 *)((u8 *)arg0 + (var16 & 1) * 4 + 0xE0), sp);
            var16 += 1;
            var17 += 0x140;
        }
    }
}
