/* rgp:protos */
#define RGP_SELF_ScreenFadeBlockStep_177f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00177f90 {
    u8 pad0[0xC];
    f32 unkC;   /* +0xC */
    s32 unk10;  /* +0x10 */
    s32 unk14;  /* +0x14 */
    f32 unk18;  /* +0x18 */
    f32 unk1C;  /* +0x1C */
    s32 unk20;  /* +0x20 */
    s32 unk24;  /* +0x24 */
    u8 pad4[0x30 - 0x28];
    s32 unk30;  /* +0x30 */
    u8 pad5[0x3C - 0x34];
    f32 unk3C;  /* +0x3C */
} S00177f90;

extern f32 D_0047D894;

s32 ScreenFadeBlockStep_177f90(S00177f90 *self)
{
    f32 f;

    if (self->unk1C > 0.0f) {
        f = self->unk1C - 1.0f;
        self->unk1C = f;
        if (f < 0.0f) {
            self->unk1C = 0.0f;
        }
        return 1;
    }

    if (self->unk30 != 0) {
        if (!(self->unk3C <= 1.0f)) {
            self->unk3C = self->unk3C + D_0047D894;
        }
    }
    if (self->unk10 == 0) {
        return 1;
    }
    if (self->unk10 > 0) {
        self->unkC = self->unkC - self->unk18;
        if (self->unkC <= 0.0f) {
            self->unkC = 0.0f;
            self->unk10 = 0;
            self->unk14 = 1;
        }
    } else {
        self->unkC = self->unkC + self->unk18;
        if (!(self->unkC < 128.0f)) {
            self->unkC = 128.0f;
            self->unk14 = 1;
        }
    }
    if ((self->unk14 != 0) && (self->unk24 != 0) && (self->unk20 == 1)) {
        self->unkC = 0.0f;
    }
    return self->unk14;
}
