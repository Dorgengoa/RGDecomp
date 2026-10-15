#include "types.h"

typedef struct Slot002d8ea0 {
    s32 unk0;
    u8 pad4[0x3C];
    s16 unk40;
    s16 unk42;
    u8 pad44[0xC];
} Slot002d8ea0;

extern void GuardWaveEffectReset_2d5660(Slot002d8ea0 *arg0);
extern void GuardWaveEffectStart_2d5ad0(Slot002d8ea0 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
extern Slot002d8ea0 D_004E34D0[0x10];

void GuardWaveEffectSpawnUnique_2d8ea0(s32 arg0, s32 arg1, s32 arg2, f32 fparg0)
{
    Slot002d8ea0 *p;
    s32 i;
    p = D_004E34D0;
    for (i = 0; i < 0x10; i++, p++) {
        if (p->unk0 != 0 && arg1 == p->unk40 && arg2 == p->unk42) {
            GuardWaveEffectReset_2d5660(p);
        }
    }
    p = D_004E34D0;
    for (i = 0; i < 0x10; i++, p++) {
        if (p->unk0 == 0) {
            break;
        }
    }
    if (i < 0x10) {
        GuardWaveEffectStart_2d5ad0(&D_004E34D0[i], arg0, arg1, arg2, fparg0);
    }
}
