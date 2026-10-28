/* rgp:protos */
#define RGP_SELF_UnitGetAttachNodeName_3bdde0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- a null-guarded member read.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct S {
    u8  pad[0x14];
    s32 v;
} S;

typedef struct Obj {
    u8  pad[0x234];
    S  *s;
} Obj;

s32 UnitGetAttachNodeName_3bdde0(Obj *p)
{
    return p->s ? p->s->v : 0;
}
