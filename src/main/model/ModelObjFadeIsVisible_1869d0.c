#include "types.h"

typedef struct Obj001869D0 {
    u8 pad0[0x1C8];
    s32 unk1C8;
    u8 pad1CC[0x1DC - 0x1CC];
    s32 unk1DC;
    f32 unk1E0;
} Obj001869D0;


s32 ModelObjFadeIsVisible_1869d0(Obj001869D0 *self)
{
    s32 r;

    if (self->unk1DC != 0) {
        if (self->unk1E0 != 0.0f) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        r = self->unk1C8 == 0;
        if (!r) {
            r = 0;
        } else {
            r = 1;
        }
    }
    return r;
}
