/* rgp:protos */
#define RGP_SELF_insect_InsectPieceMotionSlotCopy_514790 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514790 -- 40 bytes.  A field copy in SOURCE order (+0x4, +0x8,
 * +0x0, +0x1) followed by a TAIL call: the `addiu $5,$5,0xC` in the `j`'s
 * delay slot is `&s->mC`, the 0x14-byte block insect_InsectPieceMotionSlotSetName_5147c0 copies.
 * The element type is the same 0x20-byte record insect_InsectPieceMotionSlotClear_514810 builds. */

typedef struct S {
    u8  f0;                         /* +0x00 */
    s8  f1;                         /* +0x01 */
    u8  pad02[2];
    f32 f4;                         /* +0x04 */
    f32 f8;                         /* +0x08 */
    u8  mC[0x14];                   /* +0x0C */
} S;

/*rgp*/

void insect_InsectPieceMotionSlotCopy_514790(S *d, S *s)
{
    d->f4 = s->f4;
    d->f8 = s->f8;
    d->f0 = s->f0;
    d->f1 = s->f1;
    insect_InsectPieceMotionSlotSetName_5147c0(d, s->mC);
}
