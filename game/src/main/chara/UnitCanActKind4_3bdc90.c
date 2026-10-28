/* rgp:protos */
#define RGP_SELF_UnitCanActKind4_3bdc90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- a null-guarded 1-bit bitfield read.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Q {
    u8  pad[0x81];
    u8  lo : 4;
    u8  b : 1;
    u8  hi : 3;
} Q;

typedef struct Obj {
    u8  pad[0x234];
    Q  *q;
} Obj;

s32 UnitCanActKind4_3bdc90(Obj *p)
{
    return p->q ? p->q->b : 0;
}
