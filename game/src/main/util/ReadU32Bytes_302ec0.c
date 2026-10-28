/* rgp:protos */
#define RGP_SELF_ReadU32Bytes_302ec0 1
#include "port/game_protos.h"
#line 1
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

u32 ReadU32Bytes_302ec0(C4 *p)
{
    U4 u __attribute__((aligned(16)));

    u.c.a = p->a;
    u.c.b = p->b;
    u.c.c = p->c;
    u.c.d = p->d;
    return u.v;
}
