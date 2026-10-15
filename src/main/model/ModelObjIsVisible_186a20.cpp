#include "types.h"
class C00186a20 {
public:
    u8 pad0[0x1B0];
    virtual void v0();
    virtual void v1();
    virtual f32 v10();
    u8 pad1b4[0x1C0 - 0x1B4];
    s32 unk1C0;
    u8 pad1c4[0x1C8 - 0x1C4];
    s32 unk1C8;
    s32 unk1CC;
    u8 pad1d0[0x1D4 - 0x1D0];
    f32 unk1D4;
    f32 unk1D8;
    s32 unk1DC;
    f32 unk1E0;
};

extern "C" s32 ModelObjIsVisible_186a20(C00186a20 *o)
{
    f32 f;
    s32 r;

    f = o->v10();
    if (o->unk1C0 == 0) {
        return 0;
    }
    if (o->unk1DC != 0) {
        if (o->unk1E0 != 0.0f) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        r = o->unk1C8 == 0;
        if (!r) {
            r = 0;
        } else {
        if (o->unk1CC == 0) {
            r = 1;
        } else if (!(o->unk1D4 <= 0.0f) && !(f <= o->unk1D4)) {
            r = 0;
        } else if (!(o->unk1D8 <= 0.0f) && f < o->unk1D8) {
            r = 0;
        } else {
            r = 1;
        }
            if (r == 0) {
                r = 0;
            } else {
                r = 1;
            }
        }
    }
    return r;
}
