#include "types.h"
/* insect 0x004F1410 -- 36 bytes, 9 instructions.  A pure argument-shuffling
 * tail call: a0 passes through, a2 becomes a1, and four record fields fill
 * a2..a5.  `lhu` + `sra 7` is a u16 member promoted to int, so the shift is
 * arithmetic. */

typedef struct Rec {
    s16 f00;                        /* +0x00 */
    s16 f02;                        /* +0x02 */
    u8  pad04[0x08 - 0x04];
    u16 f08;                        /* +0x08 */
    s8  f0A;                        /* +0x0A */
} Rec;

extern void insect_InsectBattleDrawText_4f0db0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);

void insect_InsectBattleDrawTextRec_4f1410(s32 a, Rec *r, s32 b)
{
    insect_InsectBattleDrawText_4f0db0(a, b, r->f00, r->f02, (r->f08 >> 7) & 0x3FF, r->f0A);
}
