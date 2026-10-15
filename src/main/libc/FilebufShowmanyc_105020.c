#include "types.h"

/* Pass 29 -- a difference of two s32 members returned as 64-bit
   (the dsll32/dsra32 pair is the widening, i.e. the RETURN TYPE).
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x8];
    s32 a;
    s32 b;
} Obj;

s64 FilebufShowmanyc_105020(Obj *p)
{
    return p->b - p->a;
}
