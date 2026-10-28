/* rgp:protos */
#define RGP_SELF_GsPktSetGouraud_13e3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- a BITFIELD INSERT of a parameter.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x70];
    u8  lo : 3;
    u8  b : 1;
    u8  hi : 4;
} Obj;

void GsPktSetGouraud_13e3b0(Obj *p, s32 v)
{
    p->b = v;
}
