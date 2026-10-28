/* rgp:protos */
#define RGP_SELF_EffObjSetVertexSelectMode_1a9750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(s32, void *);

extern u8 D_0045A820[];
extern u8 D_0045A828[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x48];
    u8 m48;
};

s32 EffObjSetVertexSelectMode_1a9750(struct Obj0 *p0, s32 p1)
{
    s32 v;
    s32 r;

    v = 1;
    r = strcmp(p1, D_0045A820);
    if (r == 0) {
        v = 2;
    } else {
        r = strcmp(p1, D_0045A828);
        if (r == 0) {
            v = 3;
        }
    }
    p0->m48 = v;
    return r;
}
