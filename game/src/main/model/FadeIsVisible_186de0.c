/* rgp:protos */
#define RGP_SELF_FadeIsVisible_186de0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj00186de0 {
    s32 unk0;
    u8 pad4[0x14 - 0x4];
    s32 unk14;
    f32 unk18;
} Obj00186de0;

s32 FadeIsVisible_186de0(Obj00186de0 *self)
{
    s32 var;
    u8 eq;

    if (self->unk14 != 0) {
        var = 1;
        if (self->unk18 == 0.0f) {
            var = 0;
        }
        return var & 0xFF;
    }
    eq = self->unk0 == 0;
    return eq != 0;
}
