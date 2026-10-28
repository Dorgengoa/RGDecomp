/* rgp:protos */
#define RGP_SELF_NodeRefObjAddClsnPnt_318ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 a, b; s16 c, d; } E_00318ca0;
typedef struct { u8 pad[0x884]; s16 count; } T_00318ca0;

s32 NodeRefObjAddClsnPnt_318ca0(T_00318ca0 *p, s32 i, s32 j, f32 x, f32 y)
{
    s32 n;
    s32 o;
    E_00318ca0 *e;

    n = p->count;
    if (n >= 0x10) return 0;
    if (i < 0) return 0;
    o = n * 12;
    e = (E_00318ca0 *)((s32)p - (0 - o) + 0x684);
    e->a = x;
    e->b = y;
    e->c = i;
    e->d = j;
    p->count = p->count + 1;
    return 1;
}
