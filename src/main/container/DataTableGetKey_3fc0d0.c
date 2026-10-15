#include "types.h"

/* Bounds-checked array-element accessor: the element count is the s16 at
   +0x7C, the array base is the pointer at +0x8C, element stride 0x8.
   Retail materialises the compare into a GENERAL register and branches INTO
   the in-range arm with a b/nop for the out-of-range one -- that is a
   conditional EXPRESSION, not an if statement; every if/goto spelling comes
   out one to three words short. */

typedef struct Elem_func_003FC0D0 {
    s16 m00;                            /* +0x00 */
    u8 pad02[0x6];
} Elem_func_003FC0D0;                          /* 0x8 */

typedef struct Obj_func_003FC0D0 {
    u8 pad000[0x7C];
    s16 count;                          /* +0x7C */
    u8 pad07E[0xE];
    Elem_func_003FC0D0 *base;                   /* +0x8C */
} Obj_func_003FC0D0;

s16 DataTableGetKey_3fc0d0(Obj_func_003FC0D0 *o, s32 i)
{
    return ((i >= 0 && i < o->count) ? &o->base[i] : (Elem_func_003FC0D0 *)0)->m00;
}
