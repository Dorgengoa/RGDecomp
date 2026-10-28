/* rgp:protos */
#define RGP_SELF_ResGroupListFindElemById_42a2e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem0042a2e0 {
    u16 unk0;
    u8 pad2[0x94 - 0x2];
} Elem0042a2e0;

typedef struct Obj0042a2e0 {
    u8 pad0[0x4];
    Elem0042a2e0 *unk4;
    u16 a;
    __extension__ unsigned short lo : 2;
    unsigned short cnt : 14;
} __attribute__((aligned(2))) Obj0042a2e0;


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
