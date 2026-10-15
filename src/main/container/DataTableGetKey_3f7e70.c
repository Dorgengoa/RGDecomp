/* DataTableGetKey_3f7e70 -- BYTE-IDENTICAL to merged DataTableGetKey_3f9b40 (64 B); source cloned
   by build/zz/s23_clonesrc.py, symbol renamed, nothing else
   changed.  Verified by sha1 over the retail bytes. */
#include "types.h"

/* Bounds-checked array-element accessor: the element count is the s16 at
   +0x7C, the array base is the pointer at +0x8C, element stride 0xC.
   Retail materialises the compare into a GENERAL register and branches INTO
   the in-range arm with a b/nop for the out-of-range one -- that is a
   conditional EXPRESSION, not an if statement; every if/goto spelling comes
   out one to three words short. */

typedef struct Elem_func_003F9B40 {
    s16 m00;                            /* +0x00 */
    u8 pad02[0xA];
} Elem_func_003F9B40;                          /* 0xC */

typedef struct Obj_func_003F9B40 {
    u8 pad000[0x7C];
    s16 count;                          /* +0x7C */
    u8 pad07E[0xE];
    Elem_func_003F9B40 *base;                   /* +0x8C */
} Obj_func_003F9B40;

s16 DataTableGetKey_3f7e70(Obj_func_003F9B40 *o, s32 i)
{
    return ((i >= 0 && i < o->count) ? &o->base[i] : (Elem_func_003F9B40 *)0)->m00;
}
