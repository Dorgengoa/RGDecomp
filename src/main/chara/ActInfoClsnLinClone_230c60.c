#include "types.h"

/* Interleaved lwc1/swc1 pairs are four SEPARATE member assignments, not a
   struct copy.  m14 is initialised to the literal 1.0f (lui 0x3F80 + sw). */

extern s32 StrPoolIntern_302fd0(s32, s32, s32);

struct Node {
    f32 m00;
    f32 m04;
    s32 m08;
    s32 m0C;
    f32 m10;
    f32 m14;
};

s32 ActInfoClsnLinClone_230c60(struct Node *out, struct Node *s, s32 c, s32 d)
{
    s32 r;

    out->m00 = 0.0f;
    out->m04 = 0.0f;
    out->m08 = 0;
    out->m0C = 0;
    out->m10 = 0.0f;
    out->m14 = 1.0f;
    if (c == 0 || d == 0 || s == 0) {
        return 0;
    }
    out->m00 = s->m00;
    out->m04 = s->m04;
    out->m10 = s->m10;
    out->m14 = s->m14;
    r = StrPoolIntern_302fd0(d, s->m08, c);
    out->m08 = r;
    if (r == 0) {
        return 0;
    }
    r = StrPoolIntern_302fd0(d, s->m0C, c);
    out->m0C = r;
    return r != 0;
}
