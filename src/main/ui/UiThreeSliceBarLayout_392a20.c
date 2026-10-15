#include "types.h"
#pragma opt_propagation off
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} TriF00392A20;

typedef struct {
    s16 s0;
    s16 s2;
    s16 s4;
    s16 s6;
    s16 s8;
    s16 sA;
    s16 sC;
    s16 sE;
    f32 f10;
    f32 f14;
    s16 s18;
    s16 s1A;
    u8 pad1C[4];
} Ent00392A20;

typedef struct {
    u8 pad0[0x20];
    Ent00392A20 *unk20;
} Obj00392A20;

extern TriF00392A20 D_0047FE60 __attribute__((section(".sdata")));
extern TriF00392A20 D_0047FEB0 __attribute__((section(".sdata")));
extern const s32 D_0047FE70 __attribute__((section(".sdata")));
extern const s32 D_0047FE80 __attribute__((section(".sdata")));
extern const s32 D_0047FE90 __attribute__((section(".sdata")));
extern const s32 D_0047FEA0 __attribute__((section(".sdata")));

void UiThreeSliceBarLayout_392a20(s32 pad0, Obj00392A20 *arg1, s32 arg2)
{
    s32 b[3];
    s32 a[3];
    Ent00392A20 *p;
    f32 z;
    s32 i;

    *(TriF00392A20 *)b = D_0047FE60;
    b[2] = arg2 - 0xE;
    *(TriF00392A20 *)a = D_0047FEB0;
    a[1] = arg2 - 0x1C;
    if (arg1 == NULL) {
        return;
    }
    p = arg1->unk20;
    if (p == NULL) {
        return;
    }
    z = (f32)(s16)(i = 0);
    do {
        p->s0 = b[i];
        p->s2 = 0;
        p->s4 = a[i];
        p->s6 = 0x1C;
        p->s8 = (&D_0047FE70)[i];
        p->sA = (&D_0047FE80)[i];
        p->sC = (&D_0047FE90)[i];
        p->sE = (&D_0047FEA0)[i];
        p->s1A = 0;
        p->s18 = 0;
        p->f14 = z;
        p->f10 = z;
        p++;
        i++;
    } while (i < 3);
}
