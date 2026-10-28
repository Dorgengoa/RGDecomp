/* rgp:protos */
#define RGP_SELF_DataTableInitFinishDisableSort_421c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- a BITFIELD INSERT of zero.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x7A];
    u8  b : 1;
    u8  hi : 7;
    u8  gap[0x19];
    s32 x;
} Obj;

s32 DataTableInitFinishDisableSort_421c50(Obj *p)
{
    p->x = 0;
    p->b = 0;
    return 1;
}
