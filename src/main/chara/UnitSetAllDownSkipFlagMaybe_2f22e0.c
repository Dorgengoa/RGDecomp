#include "types.h"

/* Pass 29 -- a BITFIELD INSERT of a parameter.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x408];
    u8  lo : 7;
    u8  b : 1;
} Obj;

void UnitSetAllDownSkipFlagMaybe_2f22e0(Obj *p, s32 v)
{
    p->b = v;
}
