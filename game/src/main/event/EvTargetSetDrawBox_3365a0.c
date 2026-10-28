/* rgp:protos */
#define RGP_SELF_EvTargetSetDrawBox_3365a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"


/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047F5E0;
extern f32 D_0047F5E4;
extern f32 D_0047F5E8;
extern f32 D_0047F5EC;

void EvTargetSetDrawBox_3365a0(void *arg0, s32 arg1)
{
    u8 sp40[0x40] __attribute__((aligned(16)));
    f32 sp[4] __attribute__((aligned(16)));

    if (TargetRefGetObj_2e7110((u8 *)arg0 + 0x30) != 0) {
        XformGetScaledMatrix_2e76b0((u8 *)arg0 + 0xC0, sp40, *(f32 *)((u8 *)arg0 + 0x10C),
                     *(f32 *)((u8 *)arg0 + 0x110), *(f32 *)((u8 *)arg0 + 0x108));
        sp[0] = D_0047F5E0;
        sp[1] = D_0047F5E4;
        sp[2] = D_0047F5E8;
        sp[3] = D_0047F5EC;
        DrawWireCube_1cc1b0(arg1, sp40, (s32)&sp[0]);
    }
}
