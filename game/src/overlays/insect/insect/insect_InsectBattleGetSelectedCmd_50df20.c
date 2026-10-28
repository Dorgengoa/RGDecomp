/* rgp:protos */
#define RGP_SELF_insect_InsectBattleGetSelectedCmd_50df20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050DF20 -- 52 bytes, 13 instructions, 2 calls.  Both sub-object
 * addresses are bare `addiu $4, $16, K`, i.e. member addresses off the same
 * base -- not a hoisted pointer. */

typedef struct Sub {
    u8 pad0[0x9];
    s8 m9;                          /* +0x09 */
} Sub;

typedef struct Obj {
    u8 pad0000[0x4F90];
    u8 m4F90;                       /* +0x4F90 */
    u8 pad4F91[0x502C - 0x4F91];
    u8 m502C;                       /* +0x502C */
} Obj;

/*rgp*/
/*rgp*/

void * insect_InsectBattleGetSelectedCmd_50df20(Obj *o)
{
    return insect_InsectCmdMenuGetEntry_4efc50(&o->m502C, ((Sub *)insect_InsectCursorSetGetCurPage_511e20(&o->m4F90))->m9);
}
