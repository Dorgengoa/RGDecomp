#include "types.h"

/* Pass 29, the ONE-WORD-SHORT class (memory/levers.d/main-one-word-short.md).
   The missing word is a BITFIELD INSERT, not a constant spelling: mwcc
   materialises the inserted value with `daddiu` and ORs it in, where any
   hand-written `| 1` folds to an `ori` immediate and comes out one word
   short.  Measured on DataTableInitFinishEnableSort_3f4680 (build/w1p29/probe1.c v4); the retail
   bytes of this function are identical to that one's.

   ⚠ The struct is a STAND-IN for the real class: this is a virtual method
   (its only reference is a vtable slot), and the field offset and the
   1-bit width are read off the listing, not off a header. */

typedef struct Obj {
    u8  pad[0x7A];
    u8  b0 : 1;
    u8  rest : 7;
} Obj;

s32 DataTableInitFinishEnableSort_4215d0(Obj *p)
{
    p->b0 = 1;
    return 1;
}
