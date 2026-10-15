#include "types.h"
/* insect 0x00523490 -- 164 bytes.  A cursor cache: try the remembered index
 * first, and only on a miss walk the table from the top.  The cursor advance
 * sits in the `for` INCREMENT after `i++`, which is the order retail puts in
 * the loop-test delay slot. */

typedef struct Ent {
    u8  pad00[0x2C];
    s32 f2C;                        /* +0x2C */
} Ent;

typedef struct Tbl {
    Ent *f00;                       /* +0x00 */
    u8   pad04[0x08 - 0x04];
    s32  f08;                       /* +0x08 */
    s32  f0C;                       /* +0x0C */
} Tbl;

extern s32 func_134950(s32 k, s32 v);

s32 insect_InsectLiveTalkTableFind_523490(Tbl *t, s32 k)
{
    Ent *p;
    s32 i;
    Ent *q;

    p = t->f00;
    q = &p[t->f0C];
    if (func_134950(k, q->f2C) == 0) {
        return t->f0C;
    }
    for (i = 0; i < t->f08; i++, p++) {
        if (func_134950(k, p->f2C) == 0) {
            t->f0C = i;
            return i;
        }
    }
    return -1;
}
