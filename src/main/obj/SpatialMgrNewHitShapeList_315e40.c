#include "types.h"

/* MemStackNew_14e230 takes TWO arguments: the size and `self + 4` -- the
   `addiu $5,$18,4` in the branch-likely delay slot is the second argument,
   not scheduling noise (the sibling SpatialMgrQuadTreeInit_3162f0 sets it the same way).
   Retail RECOMPUTES that address; writing it the same way twice lets mwcc CSE
   it into a callee-saved register, which both costs a word and shifts every
   other callee-saved allocation, so the second use is spelled through an
   integer cast instead. */

extern void *MemStackNew_14e1b0(s32 size, void *pool);
extern void *ConstructNewArray_100710(void *a, void *b, s32 c, s32 d, s32 e);
extern void *MemStackNew_14e230(s32 size, void *pool);
extern void HitShapeCtor_315f00(void);

typedef struct Rec00315e40 {
    s32   m00;
    s32   m04;
    s32   m08;
    s32   m0C;
    s32   m10;
    s32   m14;
    void *m18;
    s32   m1C;
    u8    pad20[0x14];
    s32   m34;
    s32   m38;
    s8    m3C;
} Rec00315e40;

void *SpatialMgrNewHitShapeList_315e40(void *self, s32 n)
{
    void *m;
    Rec00315e40 *r;

    m = MemStackNew_14e1b0(n * 48 + 0x10, (u8 *)self + 4);
    m = ConstructNewArray_100710(m, (void *)HitShapeCtor_315f00, 0, 0x30, n);
    if (m == 0) {
        return 0;
    }
    r = MemStackNew_14e230(0x40, (void *)((s32)self + 4));
    if (r != 0) {
        r->m00 = -1;
        r->m04 = 0;
        r->m08 = -1;
        r->m0C = -1;
        r->m10 = -1;
        r->m1C = 0;
        r->m18 = m;
        r->m14 = n;
        r->m34 = -1;
        r->m38 = -1;
        r->m3C = 0;
    }
    return r;
}
