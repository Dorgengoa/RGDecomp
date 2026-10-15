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

typedef struct E00302E00 {
    s8 tag;                   /* +0x0 */
    u8 b[4];                  /* +0x1 */
} E00302E00;

void VariantSetString_302e00(E00302E00 *e, u32 v)
{
    U4 u;

    e->tag = 2;
    u.v = v;
    e->b[0] = u.c.a;
    e->b[1] = u.c.b;
    e->b[2] = u.c.c;
    e->b[3] = u.c.d;
}
