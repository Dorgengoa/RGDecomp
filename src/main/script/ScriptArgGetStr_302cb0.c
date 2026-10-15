#include "types.h"

typedef struct C4 { u8 a; u8 b; u8 c; u8 d; } C4;
typedef union U4 { C4 c; u32 v; } U4;
typedef struct E00302CB0 { s8 tag; u8 b[4]; } E00302CB0;

u32 ScriptArgGetStr_302cb0(E00302CB0 *e)
{
    U4 u;

    if (e->tag == 2) {
        u.c.a = e->b[0];
        u.c.b = e->b[1];
        u.c.c = e->b[2];
        u.c.d = e->b[3];
        return u.v;
    }
    return 0;
}
