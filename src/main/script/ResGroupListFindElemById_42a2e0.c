#include "types.h"

typedef struct Elem0042a2e0 {
    u16 unk0;
    u8 pad2[0x94 - 0x2];
} Elem0042a2e0;

typedef struct Obj0042a2e0 {
    u8 pad0[0x4];
    Elem0042a2e0 *unk4;
    u16 a;
    u16 lo : 2;
    u16 cnt : 14;
} Obj0042a2e0;


Elem0042a2e0 *ResGroupListFindElemById_42a2e0(Obj0042a2e0 *self, s32 val)
{
    s32 i;
    Elem0042a2e0 *e;

    e = self->unk4;
    for (i = 0; i < self->cnt; i++) {
        if (e->unk0 == val) {
            return e;
        }
        e++;
    }
    return NULL;
}
