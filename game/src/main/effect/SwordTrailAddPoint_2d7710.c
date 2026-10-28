/* rgp:protos */
#define RGP_SELF_SwordTrailAddPoint_2d7710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
typedef struct { s16 type; s16 pad2; s32 base; s32 max; f32 fC; s32 idx; } A;

void SwordTrailAddPoint_2d7710(A *arg0, s32 arg1, s32 arg2) {
    s32 base;
    s32 idx;
    void *t;

    if (arg0->type == 1) {
        goto ok;
    }
    if (arg0->type != 2) {
        return;
    }
ok:
    base = arg0->base;
    if (base != 0) {
        idx = arg0->idx;
        if (idx < arg0->max) {
            t = (void *)(base + idx * 0x30);
            sceVu0CopyVector(t, arg1);
            sceVu0CopyVector((u8 *)t + 0x10, arg2);
            *(u32 *)((u8 *)t + 0x1C) = 0x3F800000;
            *(u32 *)((u8 *)t + 0xC) = 0x3F800000;
            *(f32 *)((u8 *)t + 0x20) = arg0->fC;
            arg0->idx = arg0->idx + 1;
        }
    }
}
