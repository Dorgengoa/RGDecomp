/* rgp:protos */
#define RGP_SELF_insect_InsectBoardClear_4efb00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFB00 -- 108 bytes.  The board reset: two s32 7x5 grids at
 * +0x000 / +0x08C (0x8C = 7*5*4) and six u8 7x5 grids 0x23 = 7*5 apart from
 * +0x118.  Row stride 5 for the byte grids, 20 for the word grids; the OUTER
 * counter is declared first (ixa05 lever 3). */

typedef struct Board {
    s32 w0[7][5];                   /* +0x0000 */
    s32 w1[7][5];                   /* +0x008C */
    u8  a[7][5];                    /* +0x0118 */
    u8  b[7][5];                    /* +0x013B */
    u8  c[7][5];                    /* +0x015E */
    u8  d[7][5];                    /* +0x0181 */
    u8  e[7][5];                    /* +0x01A4 */
    u8  f[7][5];                    /* +0x01C7 */
} Board;

void insect_InsectBoardClear_4efb00(Board *t)
{
    s32 j;
    s32 i;

    for (j = 0; j < 7; j++) {
        for (i = 0; i < 5; i++) {
            t->w0[j][i] = 0;
            t->w1[j][i] = 0;
            t->a[j][i] = 0;
            t->b[j][i] = 0;
            t->c[j][i] = 0;
            t->d[j][i] = 0;
            t->e[j][i] = 0;
            t->f[j][i] = 0;
        }
    }
}
