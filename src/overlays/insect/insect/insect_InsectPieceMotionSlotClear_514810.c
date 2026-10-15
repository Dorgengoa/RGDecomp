#include "types.h"
/* insect 0x00514810 -- 68 bytes.  A constructor: memset of the 0x14-byte
 * block at +0xC, then four field initialisers in LISTING order (+0x0, +0x4,
 * +0x8, +0x1).  The 1.0f goes out as `lui 0x3F80` / `sw`, i.e. a float
 * constant materialised in a GPR, not through the FPU. */
typedef struct S {
    s8  f0;                         /* +0x00 */
    s8  f1;                         /* +0x01 */
    u8  pad02[2];
    s32 f4;                         /* +0x04 */
    f32 f8;                         /* +0x08 */
    u8  mC[0x14];                   /* +0x0C */
} S;

extern void func_131B60(void *dst, s32 c, s32 n);

void insect_InsectPieceMotionSlotClear_514810(S *s)
{
    func_131B60(s->mC, 0, 0x14);
    s->f0 = 0;
    s->f4 = 0;
    s->f8 = 1.0f;
    s->f1 = 0;
}
