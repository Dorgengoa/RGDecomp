#include "types.h"

typedef struct Item002d5260 {
    f32 v0[4];
    f32 v1[4];
    f32 unk20;
    f32 unk24;
    u8 pad28[8];
} Item002d5260;

typedef struct S002d5260 {
    u8 pad0[0x20];
    Item002d5260 items[16];
    u8 pad320[0];
} S002d5260;

typedef struct T002d5260 {
    u8 pad0[0x320];
    s32 unk320;
    u8 pad324[4];
    f32 unk328;
    f32 unk32C;
    s32 unk330;
    s32 unk334;
} T002d5260;

extern s32 DoubleLessEqual_100280(f64 arg0, s32 arg1);
extern void GuardEffectInitStreak_2d54c0(T002d5260 *arg0, s32 arg1);
extern void sceVu0AddVector(void *arg0, void *arg1, void *arg2);
extern void sceVu0Normalize(void *arg0, void *arg1);
extern void sceVu0ScaleVector(void *arg0, void *arg1, f32 arg2);
extern f32 D_0047DA44;
extern f32 D_0047DA28;

void GuardEffectStepMaybe_2d5260(T002d5260 *__restrict arg0)
{
    s32 t;
    Item002d5260 *p;
    f32 sp40[4];
    s32 i;
    f32 a;
    f32 c;

    if (arg0->unk334 != 0) {
        p = (Item002d5260 *)((u8 *)arg0 + 0x20);
        for (i = 0; i < 0x10; i++, p++) {
            if (!(p->unk20 <= 0.0f) && !(p->unk24 <= 0.0f)) {
                p->v1[1] = p->v1[1] - D_0047DA44 * arg0->unk32C;
                p->unk24 = p->unk24 - D_0047DA28 * arg0->unk32C;
                sceVu0Normalize(p->v1, p->v1);
                sceVu0ScaleVector(sp40, p->v1, p->unk20);
                sceVu0AddVector(p->v0, p->v0, sp40);
            }
        }
        if (arg0->unk330 < arg0->unk320) {
            GuardEffectInitStreak_2d54c0(arg0, arg0->unk330++);
        }
        if (arg0->unk330 < arg0->unk320) {
            GuardEffectInitStreak_2d54c0(arg0, arg0->unk330++);
        }
        if (arg0->unk330 < arg0->unk320) {
            GuardEffectInitStreak_2d54c0(arg0, arg0->unk330++);
        }

        arg0->unk328 = arg0->unk328 - 1.0f;
        if (DoubleLessEqual_100280(arg0->unk328, 0) != 0) {
            arg0->unk334 = 0;
        }
    }
}
