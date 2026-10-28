/* rgp:protos */
#define RGP_SELF_DataTableGetKey_424190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Bounds-checked array-element accessor: the element count is the s16 at
   +0x7C, the array base is the pointer at +0x8C, element stride 0x8.
   Retail materialises the compare into a GENERAL register and branches INTO
   the in-range arm with a b/nop for the out-of-range one -- that is a
   conditional EXPRESSION, not an if statement; every if/goto spelling comes
   out one to three words short. */

typedef struct Elem_func_00424190 {
    s16 m00;                            /* +0x00 */
    u8 pad02[0x6];
} Elem_func_00424190;                          /* 0x8 */

typedef struct Obj_func_00424190 {
    u8 pad000[0x7C];
    s16 count;                          /* +0x7C */
    u8 pad07E[0xE];
    Elem_func_00424190 *base;                   /* +0x8C */
} Obj_func_00424190;

s32 DataTableGetKey_424190(Obj_func_00424190 *o, s32 i)
{
    return (s16)(((i >= 0 && i < o->count) ? &o->base[i] : (Elem_func_00424190 *)0)->m00);
}
