#include "types.h"

/* The guard's load and the first store's base must be the SAME expression
   (typed pointer member) or mwcc reloads it and the unit is a word long.
   The flag survives only as an else-if chain; && folds it into the
   condition value.  The (s32) cast on the read is what emits retail's
   andi $3,$6,0xFF. */

typedef struct {
    s32 s00;
    s32 s04;
    u8 pad08[8];
    f32 s10;
    f32 s14;
    f32 s18;
    u8 pad1C[0x38];
    s32 s54;
} Sub_1850f0;

typedef struct {
    Sub_1850f0 *m00;
    s32 m04;
    s32 m08;
    u8 pad0C[0x54];
    f32 m60;
    f32 m64;
    f32 m68;
} Obj_1850f0;

extern void VertsPackQuantized_164bb0(s32 a, s32 b, s32 c, s32 d, void *e);

void ClothWriteMeshVerts_1850f0(Obj_1850f0 *p)
{
    u8 ok = 0;

    if (p->m00 == 0) {
    } else if (p->m04 <= 0) {
    } else {
        ok = 1;
    }
    if ((s32)ok != 0) {
        Sub_1850f0 *q;
        p->m00->s10 = p->m60;
        p->m00->s14 = p->m64;
        p->m00->s18 = p->m68;
        q = p->m00;
        VertsPackQuantized_164bb0(q->s54, p->m08, p->m04, q->s04, &q->s10);
    }
}
