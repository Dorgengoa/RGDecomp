#include "types.h"

/* As ActInfoCmndClone_231220 with one extra integer member; note m04 is NOT zeroed on
   entry - only m00 and the two floats of pos. */

extern s32 StrPoolIntern_302fd0(s32, s32, s32);

typedef struct {
    f32 x;
    f32 y;
} V2;

struct Out {
    s32 m00;
    s32 m04;
    V2  pos;
};

struct Src {
    s32 m00;
    s32 m04;
    V2  pos;
};

s32 ActInfoCallClone_2310e0(struct Out *out, struct Src *s, s32 c, s32 d)
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
    out->m04 = s->m04;
    out->pos = *q;
    r = StrPoolIntern_302fd0(d, s->m00, c);
    out->m00 = r;
    return r != 0;
}
