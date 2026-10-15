#include "types.h"

/* Pass 29 -- a null-guarded 1-bit bitfield read.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Q {
    u8  pad[0x24];
    u8  lo : 1;
    u8  b : 1;
    u8  hi : 6;
} Q;

typedef struct Obj {
    u8  pad[0x238];
    Q  *q;
} Obj;

s32 CharaSysStateFlag24Bit1Related_3a38a0(Obj *p)
{
    return p->q ? p->q->b : 0;
}
