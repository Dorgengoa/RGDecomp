/* rgp:protos */
#define RGP_SELF_insect_InsectSeqCmdQueueClear_4ea710 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EA710 -- 40 bytes, 10 instructions, leaf.  Clear the 0x40-word
 * ring at +0x5C and the count word past its end; the trailing `sw $0,
 * 0x15C($4)` rides the `jr $31` delay slot. */

typedef struct Obj {
    u8  pad00[0x5C];
    s32 f5C[0x40];                  /* +0x5C */
    s32 f15C;                       /* +0x15C */
} Obj;

void insect_InsectSeqCmdQueueClear_4ea710(Obj *o)
{
    s32 i;

    for (i = 0; i < 0x40; i++) {
        o->f5C[i] = 0;
    }
    o->f15C = 0;
}
