/* rgp:protos */
#define RGP_SELF_insect_InsectModelMemFindIndex_512870 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512870 -- 56 bytes, 14 instructions, leaf.  A 0x1C-entry linear
 * search over the s16 table at +0x400; the hit returns the index and the
 * fall-out returns -1. */

typedef struct Tbl {
    u8  pad000[0x400];
    s16 f400[0x1C];                 /* +0x400 */
} Tbl;

s32 insect_InsectModelMemFindIndex_512870(Tbl *t, s32 v)
{
    s32 i;

    for (i = 0; i < 0x1C; i++) {
        if (v == t->f400[i]) {
            return i;
        }
    }
    return -1;
}
