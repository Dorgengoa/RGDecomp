/* rgp:protos */
#define RGP_SELF_InsectRecGetMsgEntry_3cee80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_003cee80 { u8 b[128]; } E_003cee80;

typedef struct P_003cee80 {
    u8 pad22[0x22];
    s16 f22;
    u8 pad24[0x28];
    E_003cee80 arr[1];
} P_003cee80;

typedef struct S_003cee80 {
    u8 pad18[0x18];
    P_003cee80 *f18;
} S_003cee80;

E_003cee80 *InsectRecGetMsgEntry_3cee80(S_003cee80 *self, s32 i)
{
    P_003cee80 *p = self->f18;
    if (p != 0) goto g1;
    return 0;
g1:
    if (i < 0) goto zero;
    if (i < p->f22) goto ok;
zero:
    return 0;
ok:
    return &p->arr[i];
}
