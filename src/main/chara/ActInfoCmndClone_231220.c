#include "types.h"

/* Five disjuncts in ONE `||` chain with an early return; the last one is the
   null test on the interior pointer &s->pos (`addiu $2,$5,0x4 / bnel`), which
   mwcc cannot fold away.  The batched lwc1/lwc1/swc1/swc1 is ONE struct
   assignment of the two-float member. */

extern s32 StrPoolIntern_302fd0(s32, s32, s32);

typedef struct {
    f32 x;
    f32 y;
} V2;

struct Out {
    s32 m00;
    V2  pos;
};

struct Src {
    s32 m00;
    V2  pos;
};

s32 ActInfoCmndClone_231220(struct Out *out, struct Src *s, s32 c, s32 d)
{
    V2 *q;
    s32 v;
    s32 r;

    out->m00 = 0;
    out->pos.x = 0.0f;
    out->pos.y = 0.0f;
    if (c == 0 || d == 0 || s == 0 || (v = s->m00) == 0 || (q = &s->pos) == 0) {
        return 0;
    }
    out->m00 = v;
    out->pos = *q;
    r = StrPoolIntern_302fd0(d, s->m00, c);
    out->m00 = r;
    return r != 0;
}
