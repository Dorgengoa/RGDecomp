/* rgp:protos */
#define RGP_SELF_insect_InsectAiGetEnemySide_521f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00521F10 -- 4 instructions.  `xor $2,$2,$0` + `sltiu $2,$2,1` is a
 * plain `== 0` on a signed byte member. */

typedef struct Obj {
    u8 pad000[0x930];
    s8 m930;                        /* +0x930 */
} Obj;

s32 insect_InsectAiGetEnemySide_521f10(Obj *o)
{
    return o->m930 == 0;
}
