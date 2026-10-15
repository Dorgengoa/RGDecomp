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

extern Sub *insect_InsectCursorSetGetCurPage_511e20(u8 *p);
extern void insect_InsectCmdMenuGetEntry_4efc50(u8 *p, s8 v);

void insect_InsectBattleGetSelectedCmd_50df20(Obj *o)
{
    insect_InsectCmdMenuGetEntry_4efc50(&o->m502C, insect_InsectCursorSetGetCurPage_511e20(&o->m4F90)->m9);
}
