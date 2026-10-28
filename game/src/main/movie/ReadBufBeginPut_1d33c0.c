/* rgp:protos */
#define RGP_SELF_ReadBufBeginPut_1d33c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj001d33c0 {
    u8 pad0[0x14000];
    s32 unk14000;
    s32 unk14004;
    s32 unk14008;
} Obj001d33c0;

s32 ReadBufBeginPut_1d33c0(Obj001d33c0 *self, void **out)
{
    s32 d;

    d = self->unk14008 - self->unk14004;
    if (d != 0) {
        *out = (u8 *) self + self->unk14000;
    }
    return d;
}
