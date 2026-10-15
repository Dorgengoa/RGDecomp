#include "types.h"

typedef struct Obj00173ab0 {
    u8 pad0[0x4];
    s32 unk4;
    s32 unk8;
} Obj00173ab0;

s32 NamedRecGet_173ab0(Obj00173ab0 *self, s32 idx)
{
    s32 base;
    s32 ok;

    base = self->unk8;
    if (base == 0) {
        ok = 0;
    } else {
        if (idx >= 0) {
            if (idx >= self->unk4) {
                ok = 0;
            } else {
                ok = 1;
            }
        } else {
            ok = 0;
        }
    }
    if (ok) {
        return base + idx * 0x30;
    }
    return 0;
}
