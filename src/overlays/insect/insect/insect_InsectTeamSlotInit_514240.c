#include "types.h"
/* insect 0x00514240 -- 64 B / 16 words.  Leaf, no frame.
 *
 * `addu $7, $4, $8` with byte stores at +0, +5, +0xA, +0xF and a trip count of
 * 5 is FOUR five-byte arrays laid end to end, one loop body.
 * $6 = -1 and $5 = 0xFF are two DIFFERENT registers, so 0xFF is not the same
 * constant as -1 here: per the pass-33 u8/s8 rule the 0xA array is unsigned
 * and the other three are signed. */

typedef struct Row {
    s8  a[5];                   /* +0x00 */
    s8  b[5];                   /* +0x05 */
    u8  c[5];                   /* +0x0A */
    s8  d[5];                   /* +0x0F */
    s16 m14;                    /* +0x14 */
    s16 m16;                    /* +0x16 */
    s16 m18;                    /* +0x18 */
    u8  pad1A[2];
    s32 m1C;                    /* +0x1C */
} Row;

void insect_InsectTeamSlotInit_514240(Row *p)
{
    s32 i;

    for (i = 0; i < 5; i++) {
        p->a[i] = -1;
        p->b[i] = -1;
        p->c[i] = 0xFF;
        p->d[i] = -1;
    }
    p->m14 = -1;
    p->m16 = -1;
    p->m18 = -1;
    p->m1C = 0;
}
