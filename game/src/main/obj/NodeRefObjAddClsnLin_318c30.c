/* rgp:protos */
#define RGP_SELF_NodeRefObjAddClsnLin_318c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 a, b; s16 c, d; f32 e, f; } E_00318c30;
typedef struct { u8 pad[0x886]; s16 count; } T_00318c30;

s32 NodeRefObjAddClsnLin_318c30(T_00318c30 *p, s32 i, s32 j, f32 a, f32 b, f32 c, f32 d)
{
    s32 n;
    s32 o;
    E_00318c30 *e;

    n = p->count;
    if (n >= 0x10) return 0;
    if (i >= 0) {
        if (j >= 0) goto ok;
    }
    return 0;
ok:
    o = n * 20;
    e = (E_00318c30 *)((s32)p - (0 - o) + 0x744);
    e->a = a;
    e->b = b;
    e->c = i;
    e->d = j;
    e->e = c;
    e->f = d;
    p->count = p->count + 1;
    return 1;
}
