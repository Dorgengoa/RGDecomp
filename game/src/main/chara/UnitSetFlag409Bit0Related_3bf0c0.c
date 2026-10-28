/* rgp:protos */
#define RGP_SELF_UnitSetFlag409Bit0Related_3bf0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- a BITFIELD INSERT of a parameter.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x409];
    u8  b : 1;
    u8  hi : 7;
} Obj;

void UnitSetFlag409Bit0Related_3bf0c0(Obj *p, s32 v)
{
    p->b = v;
}
