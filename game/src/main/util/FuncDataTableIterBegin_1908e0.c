/* rgp:protos */
#define RGP_SELF_FuncDataTableIterBegin_1908e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj001908e0 {
    u8 pad0[0x4];
    s32 *unk4;
    s32 unk8;
} Obj001908e0;

void FuncDataTableIterBegin_1908e0(Obj001908e0 *self, s32 idx)
{
    s32 *arr;

    self->unk8 = 0;
    arr = self->unk4;
    if (arr == 0) {
        return;
    }
    if (idx < 0 || idx >= 0xB) {
        return;
    }
    self->unk8 = arr[idx];
}
