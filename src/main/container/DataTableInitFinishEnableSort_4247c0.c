#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, BITFIELD template.
   The missing word is a BITFIELD INSERT: mwcc materialises the value with
   `daddiu` and ORs it in, where a hand-written `| 1` folds to `ori`.
   The struct is a STAND-IN -- offset and 1-bit width are read off the listing. */

typedef struct Obj {
    u8  pad[0x7A];
    u8  b0 : 1;
    u8  rest : 7;
    u8  gap[0x21];
    s16 h;
} Obj;

s32 DataTableInitFinishEnableSort_4247c0(Obj *p)
{
    p->b0 = 1;
    p->h = -1;
    return 1;
}
