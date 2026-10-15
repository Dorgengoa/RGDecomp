#include "types.h"
/* insect 0x005228F0 -- 16 instructions.  A two-arm dispatch on `n < 5`; the
 * `bnez` jumps PAST the first arm, so this is an if/else and not a switch
 * ([[insect-dispatch-branch-polarity]]).  The modulo is a real `div` with no
 * zero-check trap, so divbyzerocheck stays at its default off. */

typedef struct Obj {
    u8  pad00[0x50];
    s32 m50;                        /* +0x50 */
    s32 m54;                        /* +0x54 */
} Obj;

extern void insect_InsectTeamGetPiece_5138d0(s32 a, s32 b);

void insect_InsectAiGetPiece_5228f0(Obj *p, s32 n)
{
    if (n >= 5) {
        insect_InsectTeamGetPiece_5138d0(p->m54, n % 5);
    } else {
        insect_InsectTeamGetPiece_5138d0(p->m50, n);
    }
}
