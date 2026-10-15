#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off

struct S {
    /* 0x00 */ s32 f0;
    /* 0x04 */ void *f4;
    /* 0x08 */ s16 f8;
    /* 0x0A */ u16 kind : 2;
    /* 0x0A */ u16 count : 14;
};

struct P {
    /* 0x000 */ u8 pad0[0x164];
    /* 0x164 */ u16 f164;
    /* 0x166 */ u16 pad166;
    /* 0x168 */ u8 f168[4];
};

extern void *ArenaNewChecked_42c9a0(u32 size, void *pool, s32 a, s32 b);
extern void memset(void *p, s32 c, s32 n);

s32 ResGroupListInit_42a190(struct S *p0, struct P *p1, s16 b, s32 n, struct S **out, s32 v)
{
    s32 k;
    void *q;
    s32 e;

    if (p1 != 0) {
        p0->kind = p1->f164;
    } else {
        p0->kind = 3;
    }
    p0->f0 = v;
    p0->f8 = b;
    p0->count = n;
    if (out != 0) {
        *out = p0;
    }
    if (n <= 0) {
        p0->f4 = 0;
        return 0;
    }
    k = n + 1;
    e = 4;
    q = ArenaNewChecked_42c9a0(k * 32, p1->f168, e, e);
    p0->f4 = q;
    if (q != 0) {
        memset(q, 0, k * 32);
        *(s16 *)((u8 *)p0->f4 + n * 32) = -1;
    } else {
        p0->count = 0;
        return 0;
    }
    return 1;
}
