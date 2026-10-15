#include "types.h"

typedef struct Obj0 {
    s32 unk0;
    u8 pad1[0x34 - 4];
    f32 unk34;
    f32 unk38;
} Obj0;

extern f32 D_0047D464;
extern f32 D_0047D5D0;
extern f32 D_0047DADC;
extern f32 D_0047DAE0;

void BladeLineUpdate_2d5e50(Obj0 *arg0) {
    f32 temp_f1;
    f32 dadc;

    if (arg0->unk0 == 0) {
        return;
    }
    if (arg0->unk0 == 1) {
        arg0->unk38 = arg0->unk38 + (dadc = D_0047DADC);
        temp_f1 = arg0->unk34 + dadc;
        arg0->unk34 = temp_f1;
        if (!(temp_f1 < 1.0f)) {
            arg0->unk34 = 1.0f;
            arg0->unk38 = 1.0f;
            arg0->unk0 = 3;
            return;
        }
    }
    if (arg0->unk0 == 2) {
        f32 d464;
        temp_f1 = arg0->unk38 + D_0047DAE0;
        d464 = D_0047D464;
        arg0->unk38 = temp_f1;
        if (!(temp_f1 < d464)) {
            arg0->unk38 = d464;
            arg0->unk0 = 3;
            return;
        }
    }
    if (arg0->unk0 == 3) {
        temp_f1 = arg0->unk38 - D_0047D5D0;
        arg0->unk38 = temp_f1;
        if (temp_f1 <= 0.0f) {
            arg0->unk0 = 0;
        }
    }
}
