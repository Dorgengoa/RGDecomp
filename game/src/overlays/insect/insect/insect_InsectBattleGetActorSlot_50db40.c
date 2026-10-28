/* rgp:protos */
#define RGP_SELF_insect_InsectBattleGetActorSlot_50db40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x50DB40 -- 16 B / 4 words.  `sll $2,$5,2 / addu $2,$2,$4 /
 * lw 0x5B20($2)`: a plain word-array subscript.  mwcc puts the SCALED INDEX in rs
 * and the base in rt whenever a non-zero displacement is folded into the load;
 * that falls out of `o->m5B20[i]`, it is not a source-order choice. */

typedef struct Obj {
    u8  pad00[0x5B20];
    s32 m5B20[4];              /* +0x5B20 */
} Obj;

s32 insect_InsectBattleGetActorSlot_50db40(Obj *o, s32 i)
{
    return o->m5B20[i];
}
