/* rgp:protos */
#define RGP_SELF_DataTableAllocIndex_41ba70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Call the worker, remember its result at +0x90, and report
   success as a bool.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0041ba70 {
    u8 pad000[0x90];
    s32 m90;         /* +0x90 */
} Obj_FUN_0041ba70;

/*rgp*/

u32 DataTableAllocIndex_41ba70(Obj_FUN_0041ba70 *o)
{
    s32 r;
    u8 live;

    r = DataTableAllocIndex_368640(o);
    o->m90 = r;
    live = r != 0;
    return (u8)(live);
}
