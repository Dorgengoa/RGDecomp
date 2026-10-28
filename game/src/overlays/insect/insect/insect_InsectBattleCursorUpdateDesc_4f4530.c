/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCursorUpdateDesc_4f4530 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F4530 -- 124 bytes.  Eleven words are copied into the frame and
 * then handed out one per argument; $4 is never re-materialised, so the first
 * parameter passes straight through. */

typedef struct Blk {
    s32 m[11];
} Blk;

/*rgp*/



void insect_InsectBattleCursorUpdateDesc_4f4530(s32 a, Blk *src, s32 c)
{
    Blk t __attribute__((aligned(16)));

    t = *src;
    insect_InsectBattleCursorUpdate_4f43a0(a, t.m[0], t.m[1], t.m[2], t.m[3], t.m[4], t.m[5],
                        t.m[6], c, t.m[7], t.m[8], t.m[9], t.m[10]);
}
