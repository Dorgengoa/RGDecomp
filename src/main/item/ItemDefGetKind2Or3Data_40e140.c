#include "types.h"

typedef struct Obj0040e140 {
    u8 pad0[0x20];
    s32 unk20;
} Obj0040e140;

extern s32 ItemDefIsKind3_40e350(void);
extern s32 ItemDefIsKind2_40e360(Obj0040e140 *self);

s32 ItemDefGetKind2Or3Data_40e140(Obj0040e140 *self)
{
    s32 result;

    if (ItemDefIsKind3_40e350() == 0) {
        result = (ItemDefIsKind2_40e360(self) != 0) ? self->unk20 : 0;
    } else {
        result = self->unk20;
    }
    return result;
}
