/* rgp:protos */
#define RGP_SELF_insect_InsectAbilityTableCollect_51cef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051CEF0 -- 88 bytes, 22 instructions.  Clear the eight-slot cell
 * array at +0x6C and refill it; the fifth parameter is both the guard and the
 * fifth argument of the callee, and the array address is the return value. */

typedef struct Cell { u8 raw[4]; } Cell;

typedef struct Grid {
    u8    pad00[0x6C];
    Cell *f6C[8];                   /* +0x6C */
    s32   f8C;                      /* +0x8C */
} Grid;

/*rgp*/

Cell **insect_InsectAbilityTableCollect_51cef0(Grid *m, s32 a, s32 b, s32 c, s32 n)
{
    s32 i;

    if (n != 0) {
        for (i = 0; i < 8; i++) {
            m->f6C[i] = 0;
        }
        m->f8C = insect_InsectAbilityTableFilter_51d020(m, a, b, c, m->f6C);
    }
    return m->f6C;
}
