#include "types.h"

/* Pass 29 -- a null-guarded two-step member read.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct T {
    u8  pad[0x10];
    s16 h;
} T;

typedef struct S {
    u8  pad[0xA8];
    T  *t;
} S;

typedef struct Obj {
    u8  pad[0x8];
    S  *s;
} Obj;

s32 ShopListGetRowCount_3e7e10(Obj *p)
{
    return p->s ? p->s->t->h : 0;
}
