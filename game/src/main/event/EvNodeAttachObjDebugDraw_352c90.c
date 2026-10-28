/* rgp:protos */
#define RGP_SELF_EvNodeAttachObjDebugDraw_352c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { f32 w[4]; } SD4_0047F720;
extern SD4_0047F720 D_0047F720 __attribute__((section(".sdata")));

/*rgp*/
/*rgp*/

void EvNodeAttachObjDebugDraw_352c90(void *self, s32 arg1)
{
    u8 sp40[0x40] __attribute__((aligned(16)));
    f32 sp30[4] __attribute__((aligned(16)));
    s32 flags;
    s32 sub;

    flags = *(s32 *)((u8 *)self + 0xD0);
    if ((((flags & 0x80000000) != 0) ^ 1) && (flags & 0x02000000)) {
        sub = *(s32 *)((u8 *)self + 0xF0);
        if (sub != 0) {
            XformGetMatrix_2e7750((u8 *)self + 0x10, sp40);
            *(SD4_0047F720 *)sp30 = D_0047F720;
            EventVolumeRecDebugDraw_2e49b0(sub, arg1, sp40, sp30);
        }
    }
}
