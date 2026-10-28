/* rgp:protos */
#define RGP_SELF_CharaSysStateFlag24Bit2Related_3a3880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- a null-guarded 1-bit bitfield read.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Q {
    u8  pad[0x24];
    u8  lo : 2;
    u8  b : 1;
    u8  hi : 5;
} Q;

typedef struct Obj {
    u8  pad[0x238];
    Q  *q;
} Obj;

s32 CharaSysStateFlag24Bit2Related_3a3880(Obj *p)
{
    return p->q ? p->q->b : 0;
}
