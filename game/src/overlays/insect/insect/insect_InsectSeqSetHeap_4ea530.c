/* rgp:protos */
#define RGP_SELF_insect_InsectSeqSetHeap_4ea530 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x4EA530 -- 20 B / 5 words.  `beqz $5, L / nop / sw $5, 0x0($4)`:
 * a guarded setter.  The guard is a plain `beqz` with a NOP in the delay slot,
 * not a `bnel` with the store in it, so it is a straight `if (v != 0) { ... }`
 * whose body mwcc did not sink. */

typedef struct Obj {
    s32 m00;                 /* +0x0 */
} Obj;

void insect_InsectSeqSetHeap_4ea530(Obj *o, s32 v)
{
    if (v != 0) {
        o->m00 = v;
    }
}
