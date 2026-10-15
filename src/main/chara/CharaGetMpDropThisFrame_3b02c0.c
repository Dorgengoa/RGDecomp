#include "types.h"

/* Pass 29 -- a difference of two u16 members.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x18];
    u16 a;
    u8  gap[0x18A];
    u16 b;
} Obj;

s32 CharaGetMpDropThisFrame_3b02c0(Obj *p)
{
    return p->b - p->a;
}
