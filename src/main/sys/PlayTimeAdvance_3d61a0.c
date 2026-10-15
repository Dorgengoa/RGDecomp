#include "types.h"

typedef struct Obj003d61a0 {
    u8 pad0[0x8];
    s64 unk8;
} Obj003d61a0;

extern s32 fptodp(void);
extern s64 dpadd(s64, s32);
extern void DoubleToU64_13ab28(s64);

void PlayTimeAdvance_3d61a0(Obj003d61a0 *self)
{
    s64 temp;

    temp = self->unk8;
    self->unk8 = dpadd(temp, fptodp());
    DoubleToU64_13ab28(self->unk8);
}
