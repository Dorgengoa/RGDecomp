#include "types.h"
#pragma optimization_level 2

typedef struct Obj0042ce80 {
    s32 *unk0;
    s32 unk4;
} Obj0042ce80;

#pragma optimization_level 3
void BitArrayFillAll_42ce80(Obj0042ce80 *self, u32 arg1)
{
    s32 *p;
    s32 val;
    u32 i;

    p = self->unk0;
    if (p != NULL) {
        if (arg1 != 0) {
            arg1 = -1;
        } else {
            arg1 = 0;
        }
        i = 0;
        while (i < (u32)self->unk4) {
            *p = arg1;
            i++;
            p++;
        }
    }
}
