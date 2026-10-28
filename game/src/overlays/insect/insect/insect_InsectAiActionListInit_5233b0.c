/* rgp:protos */
#define RGP_SELF_insect_InsectAiActionListInit_5233b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005233B0 -- 44 bytes, 11 instructions.  Clears a 0x201-entry table
 * and its own head word; the last slot is cleared FIRST and the head word LAST,
 * both outside the loop. */

typedef struct Tbl {
    s32 f00;                        /* +0x00 */
    s32 f04[0x201];                 /* +0x04 */
} Tbl;

void insect_InsectAiActionListInit_5233b0(Tbl *t)
{
    s32 i;

    t->f04[0x200] = 0;
    for (i = 0; i < 0x200; i++) {
        t->f04[i] = 0;
    }
    t->f00 = 0;
}
