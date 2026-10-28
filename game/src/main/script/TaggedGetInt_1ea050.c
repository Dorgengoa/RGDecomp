/* rgp:protos */
#define RGP_SELF_TaggedGetInt_1ea050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S1EA {
    s32 type;
    union {
        s32 i;
        f32 f;
    } u;
} S1EA;

s32 TaggedGetInt_1ea050(S1EA *p)
{
    s32 t;

    t = p->type;
    if (t == 1) goto flt;
    if (t == 0) goto int_;
    return 0;
int_:
    return p->u.i;
flt:
    return (s32)p->u.f;
}
