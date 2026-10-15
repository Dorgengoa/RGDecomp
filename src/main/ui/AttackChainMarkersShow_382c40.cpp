#include "types.h"
extern "C" {
typedef struct { f32 v; s16 f; } Ent;
typedef struct { f32 x; u8 pad[0x220]; } Elem;
typedef struct {
    Elem *list;
    s16 n4;
    s16 pad6;
    s16 pad8;
    s16 nA;
    u8 padC[0x14 - 0xC];
    f32 f14;
    f32 f18;
} Obj;
extern u8 D_00527020[];
extern void func_4F68D0(void *, Ent *, s32);

void AttackChainMarkersShow_382c40(Obj *arg0)
{
    Ent buf[10];
    s32 i;
    if (arg0->list != 0) {
        for (i = 0; i < arg0->n4; i++) {
            buf[i].v = arg0->f14 * (arg0->f18 - arg0->list[i].x);
            buf[i].f = (u8)((i < arg0->nA) ^ 1);
        }
        func_4F68D0(D_00527020, buf, arg0->nA);
    }
}

}
