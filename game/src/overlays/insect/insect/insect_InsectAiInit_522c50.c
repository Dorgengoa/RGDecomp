/* rgp:protos */
#define RGP_SELF_insect_InsectAiInit_522c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00522C50 -- 60 B / 15 words.  Three word clears through the
 * INCOMING $4 (so they precede the call in source -- mwcc cannot hoist a store
 * across a call), then insect_InsectAiBeginTurn_522ba0(o), then three more through the
 * saved $16.  0x5C is written LAST, after the two 0x8Dx stores, which is the
 * source order and not ascending offset.
 *
 * insect_InsectAiBeginTurn_522ba0 takes ONE argument: this call site marshals only $4 and
 * the callee's own listing reads $4 and never $5. */
typedef struct Ins {
    u8  pad00[0x50];
    s32 f50;                       /* +0x50 */
    s32 f54;                       /* +0x54 */
    s32 f58;                       /* +0x58 */
    s32 f5C;                       /* +0x5C */
    u8  pad60[0x8D0 - 0x60];
    s32 f8D0;                      /* +0x8D0 */
    s32 f8D4;                      /* +0x8D4 */
} Ins;

/*rgp*/

void insect_InsectAiInit_522c50(Ins *o)
{
    o->f50 = 0;
    o->f54 = 0;
    o->f58 = 0;
    insect_InsectAiBeginTurn_522ba0(o);
    o->f8D0 = 0;
    o->f8D4 = 0;
    o->f5C = 0;
}
