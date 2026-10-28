/* rgp:protos */
#define RGP_SELF_insect_InsectBattleAllActed_4f4600 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F4600 -- 112 bytes, 28 instructions, 1 call.  The element
 * stride 0x994 is not a power of two, so the index arrives through `mult`;
 * the flag byte is `lbu`, i.e. u8. */

typedef struct Ent {
    u8 pad[0x994];
} Ent;

typedef struct Obj {
    u8  pad0000[0x35F8];
    Ent ents[2];                    /* +0x35F8 */
    u8  pad4920[0x5EF1 - 0x4920];
    u8  m5EF1;                      /* +0x5EF1 */
} Obj;

/*rgp*/

s32 insect_InsectBattleAllActed_4f4600(Obj *o)
{
    s32 i;
    u8  v;

    v = o->m5EF1;
    for (i = 0; i < 2; i++) {
        if (insect_InsectTeamAllActed_513690(&o->ents[i], v) == 0) {
            return 0;
        }
    }
    return 1;
}
