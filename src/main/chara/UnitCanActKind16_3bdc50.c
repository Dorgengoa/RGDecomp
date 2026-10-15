#include "types.h"

/* Pass 29 -- a null-guarded 1-bit bitfield read.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Q {
    u8  pad[0x81];
    u8  lo : 6;
    u8  b : 1;
    u8  hi : 1;
} Q;

typedef struct Obj {
    u8  pad[0x234];
    Q  *q;
} Obj;

s32 UnitCanActKind16_3bdc50(Obj *p)
{
    return p->q ? p->q->b : 0;
}
