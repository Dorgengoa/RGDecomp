/* rgp:protos */
#define RGP_SELF_RegisterGlobalObject_100dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct N00100dc0 {
    struct N00100dc0 *next;   /* +0x0 */
    s32 b;                    /* +0x4 */
    s32 a;                    /* +0x8 */
} N00100dc0;

extern struct { N00100dc0 *v; s32 pad[3]; } D_004853D0;

s32 RegisterGlobalObject_100dc0(s32 a, s32 b, N00100dc0 *n)
{
    n->next = D_004853D0.v;
    n->b = b;
    n->a = a;
    *(N00100dc0 **)0x004853D0 = n;
    return a;
}
