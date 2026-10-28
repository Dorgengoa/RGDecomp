/* rgp:protos */
#define RGP_SELF_insect_InsectSeqStateHistClear_4ea460 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EA460 -- 11 instructions.  Four-entry array at +0x04 set to -1;
 * the `sw $5, 0x4($3)` displacement is the member offset, so the array is a
 * struct member and not a bare pointer bias. */

typedef struct Obj {
    s32 m00;                        /* +0x00 */
    s32 m04[4];                     /* +0x04 */
} Obj;

void insect_InsectSeqStateHistClear_4ea460(Obj *o)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        o->m04[i] = -1;
    }
}
