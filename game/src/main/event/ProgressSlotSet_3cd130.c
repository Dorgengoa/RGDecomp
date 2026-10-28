/* rgp:protos */
#define RGP_SELF_ProgressSlotSet_3cd130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_003cd130 {
    u8 pad0[4];
    s32 f4;
    u8 pad8[2];
    s16 arrA[1];
} S_003cd130;

extern s32 D_004838C0;
/*rgp*/
/*rgp*/

s32 ProgressSlotSet_3cd130(S_003cd130 *self, s32 p1, s32 p2, s32 idx, s32 val, s32 flag, s32 flag2)
{
    s32 old;
    if (self->f4 == 0) return 0;
    if (idx < 0) goto zero;
    if (idx < 15) goto ok;
zero:
    return 0;
ok:
    if (flag != 0) {
        ProgressSetChapter_3cd480((void *)self, (int)p1, (int)p2, (int)idx);
    }
    old = self->arrA[idx];
    self->arrA[idx] = val;
    if (flag2 != 0) {
        WorldOnProgressChanged_3edb70(D_004838C0, p1, p2, val);
    }
    return 1;
}
