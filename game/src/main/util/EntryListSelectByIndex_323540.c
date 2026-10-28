/* rgp:protos */
#define RGP_SELF_EntryListSelectByIndex_323540 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

typedef struct O3540 {
    u8 pad0[0x8];
    s32 unk8;
    s32 unkC;
    u8 pad10[0x8];
    s16 unk18;
} O3540;

s32 EntryListSelectByIndex_323540(O3540 *self, s32 idx)
{
    s32 base;

    base = self->unk8;
    if (base == 0 || !(idx >= 0 && idx < self->unk18)) {
        self->unkC = 0;
        EntryListSetCurIndex_3238c0(self, -1);
    } else {
        self->unkC = base + idx * 0x78;
        EntryListSetCurIndex_3238c0(self, idx);
    }
    return self->unkC;
}
