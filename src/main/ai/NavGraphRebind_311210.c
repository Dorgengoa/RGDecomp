#include "types.h"

/* Four repeats of one adjust block (0x10/0x14, 0x20/0x24, 0x30/0x34,
   0x40/0x44).  Blocks 1 and 2 carry an OUTER `if (m != 0)` guard as well as
   the adjust's own test -- that is why those two emit two beql $3,$0 in a
   row; blocks 3 and 4 have only the adjust.  The `lw $18,0x10` duplicated
   into a beql delay slot is the ordinary branch-likely duplication. */

typedef struct S {
    u8  pad0[0x10];
    u8 *m10;
    u8  f14;
    u8  pad15[3];
    u16 n18;
    u8  pad1a[6];
    u8 *m20;
    u8  f24;
    u8  pad25[0xB];
    u8 *m30;
    u8  f34;
    u8  pad35[0xB];
    u8 *m40;
    u8  f44;
} S;

extern s32 HeapBlockRefGetBlock_42e0d0(S *s);
extern void NavNodePtrsToOffsets_3117f0(u8 *p, s32 d);
extern void NavNodePtrsFromOffsets_3117c0(u8 *p, s32 d);
extern void HeapBlockRefRebind_42e150(S *s, void *a, void *b, void *c);

s32 NavGraphRebind_311210(S *s, void *a, void *b, void *c)
{
    s32 d;
    u8 *p;
    u32 i;
    u8 *p2;
    u32 i2;
    s32 d2;

    d = HeapBlockRefGetBlock_42e0d0(s);
    p = s->m10;
    if (p != 0) {
        for (i = 0; i < s->n18; i++, p += 0x24) {
            NavNodePtrsToOffsets_3117f0(p, d);
        }
        if (s->m10 != 0 && d != 0 && s->f14 == 0) {
            s->f14 = 1;
            s->m10 -= d;
        } else {
            s->f14 = 0;
        }
    }
    d = HeapBlockRefGetBlock_42e0d0(s);
    if (s->m20 != 0) {
        if (s->m20 != 0 && d != 0 && s->f24 == 0) {
            s->f24 = 1;
            s->m20 -= d;
        } else {
            s->f24 = 0;
        }
    }
    d = HeapBlockRefGetBlock_42e0d0(s);
    if (s->m30 != 0 && d != 0 && s->f34 == 0) {
        s->f34 = 1;
        s->m30 -= d;
    } else {
        s->f34 = 0;
    }
    d = HeapBlockRefGetBlock_42e0d0(s);
    if (s->m40 != 0 && d != 0 && s->f44 == 0) {
        s->f44 = 1;
        s->m40 -= d;
    } else {
        s->f44 = 0;
    }
    HeapBlockRefRebind_42e150(s, a, b, c);
    d2 = HeapBlockRefGetBlock_42e0d0(s);
    if (s->f14 != 0) {
        s->m10 = (u8 *)(d2 + (s32)s->m10);
        s->f14 = 0;
    }
    p2 = s->m10;
    for (i2 = 0; i2 < s->n18; i2++, p2 += 0x24) {
        NavNodePtrsFromOffsets_3117c0(p2, d2);
    }
    d2 = HeapBlockRefGetBlock_42e0d0(s);
    if (s->f24 != 0) {
        s->m20 = (u8 *)(d2 + (s32)s->m20);
        s->f24 = 0;
    }
    d2 = HeapBlockRefGetBlock_42e0d0(s);
    if (s->f34 != 0) {
        s->m30 = (u8 *)(d2 + (s32)s->m30);
        s->f34 = 0;
    }
    d2 = HeapBlockRefGetBlock_42e0d0(s);
    if (s->f44 != 0) {
        s->m40 = (u8 *)(d2 + (s32)s->m40);
        s->f44 = 0;
    }
    return 1;
}
