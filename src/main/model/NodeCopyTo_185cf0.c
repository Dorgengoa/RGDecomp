#include "types.h"

/* Two mwcc block-copy loops.  s32 element type => lw/sw; a u8 array gives
   lb/sb and the wrong trip count.  +0x00 is 8-aligned (2-word unroll, 6
   trips); +0x3C is not (1-word, 9 trips). */

typedef struct { s32 d[12]; } Blk30;
typedef struct { s32 d[9]; } Blk24;

typedef struct {
    Blk30 a;    /* +0x00 */
    s16 b;      /* +0x30 */
    s16 c;      /* +0x32 */
    s32 d;      /* +0x34 */
    s32 e;      /* +0x38 */
    Blk24 f;    /* +0x3C */
    f32 g;      /* +0x60 */
    f32 h;      /* +0x64 */
} Obj_185CF0;

void NodeCopyTo_185cf0(Obj_185CF0 *s, Obj_185CF0 *d)
{
    d->a = s->a;
    d->b = s->b;
    d->c = s->c;
    d->d = s->d;
    d->e = s->e;
    d->f = s->f;
    d->g = s->g;
    d->h = s->h;
}
