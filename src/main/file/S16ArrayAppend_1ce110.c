#include "types.h"

typedef struct Obj001ce110 {
    s16 *unk0;
    s16 unk4;
    s16 unk6;
} Obj001ce110;

s32 S16ArrayAppend_1ce110(Obj001ce110 *self, s16 val)
{
    s16 *buf; s16 idx; s16 next;
    buf = self->unk0;
    if (buf != NULL) {
        idx = self->unk6;
        if (self->unk4 > idx) goto ok;
    }
    return -1;
ok:
    buf[idx] = val;
    next = self->unk6 + 1;
    self->unk6 = next;
    return (s32) next - 1;
}
