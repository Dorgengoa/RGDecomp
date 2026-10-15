#include "types.h"

typedef struct {
    u8 pad0[0x4F0];
    s32 unk4F0;
    s32 unk4F4;
    u8 pad4F8[0x10];
    f32 unk508;
    f32 unk50C;
    s32 unk510;
    s32 unk514;
} Sub001b1190;

typedef struct {
    u8 pad0[4];
    Sub001b1190 *unk4;
} Self001b1190;

typedef struct {
    u8 pad0[0x28];
    s32 unk28;
    s32 unk2C;
} Arg001b1190;

extern s32 SoundNextPlayHandle_1b81c0(void);
extern void SoundPlayScaledVolPan_1b9680(s32, s32, s32, f32, f32);

s32 MotionEventFootSeFire_1b1190(Self001b1190 *self, Arg001b1190 *arg1)
{
    Sub001b1190 *sub;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 r;

    sub = self->unk4;
    if (sub == NULL) {
        return 0;
    }
    a = sub->unk4F0;
    b = sub->unk4F4;
    c = arg1->unk2C;
    if (c > 0) {
        b = c;
    }
    d = arg1->unk28 + b * 2;
    r = SoundNextPlayHandle_1b81c0();
    SoundPlayScaledVolPan_1b9680(a, d, r, self->unk4->unk508, self->unk4->unk50C);
    self->unk4->unk510 = 1;
    self->unk4->unk514 = arg1->unk28;
    return 1;
}
