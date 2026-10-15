#include "types.h"

typedef struct T1b0780 {
    u8  pad000[0x504];
    s32 f504;
    u8  pad508[0x520 - 0x508];
    f32 f520;
    f32 f524;
    f32 f528;
    f32 f52C;
    f32 f530;
} T1b0780;

extern void ObjGetAttachNodePos_1adec0(T1b0780 *, s32, void *);
extern void SoundCalcDistVolPan_1b7de0(f32 *, f32 *, void *, f32, f32);

void ModelObjExCalcSoundVolPan_1b0780(T1b0780 *self, f32 *pf, f32 *pi)
{
    u8 loc[16];

    *pf = self->f530;
    *pi = 0.0f;
    if (*pf < 0.0f) {
        *pf = 0.0f;
    }
    if (*pf > 1.0f) {
        *pf = 1.0f;
    }
    if (self->f504 != 0) {
        ObjGetAttachNodePos_1adec0(self, 0, loc);
        SoundCalcDistVolPan_1b7de0(pf, pi, loc, self->f520, self->f524);
        *pf = *pf * self->f530;
        if (*pf < self->f528) {
            *pf = self->f528;
        }
        if (*pf > self->f52C) {
            *pf = self->f52C;
        }
    }
}
