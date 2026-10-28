/* rgp:protos */
#define RGP_SELF_UnitMeterGetMax_3bf110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- an s16 member widened to float.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct R {
    u8  pad[0x86];
    s16 h;
} R;

typedef struct Obj {
    u8  pad[0x234];
    R  *r;
} Obj;

f32 UnitMeterGetMax_3bf110(Obj *p)
{
    return p->r->h;
}
