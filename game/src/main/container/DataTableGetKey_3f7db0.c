/* rgp:protos */
#define RGP_SELF_DataTableGetKey_3f7db0 1
#include "port/game_protos.h"
#line 1
/* DataTableGetKey_3f7db0 -- BYTE-IDENTICAL to merged DataTableGetKey_3fbd90 (64 B); source cloned
   by build/zz/s23_clonesrc.py, symbol renamed, nothing else
   changed.  Verified by sha1 over the retail bytes. */
#include "types.h"

/* Bounds-checked array-element accessor: the element count is the s16 at
   +0x7C, the array base is the pointer at +0x8C, element stride 0xA.
   Retail materialises the compare into a GENERAL register and branches INTO
   the in-range arm with a b/nop for the out-of-range one -- that is a
   conditional EXPRESSION, not an if statement; every if/goto spelling comes
   out one to three words short. */

typedef struct Elem_func_003FBD90 {
    s16 m00;                            /* +0x00 */
    u8 pad02[0x8];
} Elem_func_003FBD90;                          /* 0xA */

typedef struct Obj_func_003FBD90 {
    u8 pad000[0x7C];
    s16 count;                          /* +0x7C */
    u8 pad07E[0xE];
    Elem_func_003FBD90 *base;                   /* +0x8C */
} Obj_func_003FBD90;

s32 DataTableGetKey_3f7db0(Obj_func_003FBD90 *o, s32 i)
{
    return (s16)(((i >= 0 && i < o->count) ? &o->base[i] : (Elem_func_003FBD90 *)0)->m00);
}
