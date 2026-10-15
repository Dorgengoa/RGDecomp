#include "types.h"

typedef struct C4 {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} C4;

typedef union U4 {
    C4 c;
    u32 v;
} U4;

void ClearU32Bytes_302f20(C4 *p)
{
    U4 u;

    u.v = 0;
    p->a = u.c.a;
    p->b = u.c.b;
    p->c = u.c.c;
    p->d = u.c.d;
}
