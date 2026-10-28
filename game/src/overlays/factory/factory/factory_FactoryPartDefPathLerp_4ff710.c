/* rgp:protos */
#define RGP_SELF_factory_FactoryPartDefPathLerp_4ff710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Key {
    s16 f00;
    s16 f02;
    s16 f04;
} Key;                                          /* 6 */

typedef struct Node { u8 pad00[0x10]; } Node;

typedef struct Anim {
    u8   pad00[0xC];
    Key *f0C;
    s16  f10;
    s16  f12;
} Anim;

/*rgp*/
/*rgp*/

s32 factory_FactoryPartDefPathLerp_4ff710(Anim *a, void *h, s32 c, s32 d, Node *tbl)
{
    Key *k;
    s32  acc;
    s32  j;
    s32  t;
    s32  x;

    if (c < 0 || d < c) {
        return 0;
    }
    acc = 0;
    j = 0;
    k = a->f0C;
    x = c * a->f12;
    for (; j < a->f10; j++, k += 1) {
        t = acc + d * k->f04;
        if (acc <= x && x < t) {
            VecLerpPoint_1cbac0(h, &tbl[k->f02], &tbl[k->f00], (f32)(x - acc) / (f32)(t - acc));
            return 1;
        }
        acc = t;
    }
    VecCopyAsPoint_1cbe10(h, &tbl[a->f0C[a->f10 - 1].f02]);
    return 1;
}
