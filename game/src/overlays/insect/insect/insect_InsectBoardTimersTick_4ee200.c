/* rgp:protos */
#define RGP_SELF_insect_InsectBoardTimersTick_4ee200 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EE200 -- 288 bytes.  Two planes x 7 x 5 of packed nibble
 * counters; each cell's two nibbles are decremented (floored at 0 by a signed
 * `- 1 >= 0` test) and handed to the same reporter with a 0/1 selector. */

typedef struct Own {
    u8 pad0000[0x1A4];
    u8 f1A4[2][7][5];               /* +0x1A4 */
} Own;

/*rgp*/

void insect_InsectBoardTimersTick_4ee200(Own *o)
{
    u8 (*pl)[5];
    s32 p;
    s32 y;
    s32 x;
    s32 lo;
    s32 hi;
    u8  c;

    for (p = 0; p < 2; p++) {
        pl = o->f1A4[p];
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 5; x++) {
                c = pl[y][x];
                hi = (u8)((c & 0xF0) >> 4);
                lo = c & 0xF;
                if ((u8)hi - 1 >= 0) {
                    hi = (u8)(hi - 1);
                }
                if ((u8)lo - 1 >= 0) {
                    lo = (u8)(lo - 1);
                }
                insect_InsectBoardTimerSet_4ee320(o, p, x, y, hi, 1);
                insect_InsectBoardTimerSet_4ee320(o, p, x, y, lo, 0);
            }
        }
    }
}
