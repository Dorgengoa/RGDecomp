/* rgp:protos */
#define RGP_SELF_CharaGetDataEntryMaybe_1f03e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- an indexed read through a member pointer.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct S {
    u8  pad[0x8];
    s32 a[1];
} S;

typedef struct Obj {
    u8  pad[0x230];
    S  *s;
} Obj;

s32 CharaGetDataEntryMaybe_1f03e0(Obj *p, s32 i)
{
    return p->s->a[i];
}
