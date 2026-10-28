/* rgp:protos */
#define RGP_SELF_MtxStore3x4_186390 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Pack the xyz of four Vec4 rows into twelve consecutive floats, and raise
   the halfword flag at +0x30 first. Twelve `lwc1`/`swc1` pairs through $f0 --
   nothing here moves a qword, which is what the 4-to-3 stride costs. */

typedef struct Packed00186390 {
    f32 m[12];         /* +0x00 */
    s16 unk30;         /* +0x30 */
} Packed00186390;

void MtxStore3x4_186390(Packed00186390 *d, const Mtx4 *s)
{
    d->unk30 = 1;
    d->m[0] = s->r[0].x;
    d->m[1] = s->r[0].y;
    d->m[2] = s->r[0].z;
    d->m[3] = s->r[1].x;
    d->m[4] = s->r[1].y;
    d->m[5] = s->r[1].z;
    d->m[6] = s->r[2].x;
    d->m[7] = s->r[2].y;
    d->m[8] = s->r[2].z;
    d->m[9] = s->r[3].x;
    d->m[10] = s->r[3].y;
    d->m[11] = s->r[3].z;
}
