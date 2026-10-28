/* rgp:protos */
#define RGP_SELF_AreaBoxPlace_1e94a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 mn[3];
    f32 mx[3];
    f32 vol;
    f32 h[3];
    f32 c[3];
    f32 m[4];
    f32 up;
    f32 dn;
} Box;

/*rgp*/
/*rgp*/
/*rgp*/

void AreaBoxPlace_1e94a0(Box *b, s32 arg1, float rgp_f0)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(f32[12])]; char m1[0x30 + sizeof(u8[0x10])]; char m2[0x40]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(f32[12]) <= (0x30) && (0x0) >= 0 ? 1 : -1];
    
    f32 o[4] __attribute__((aligned(16)));
    f32 d;
    f32 e;

    MatRotY_1cb200((*(f32 (*)[12])(rgp_blk1 + 0x0)), (float)rgp_f0);
    VecCopy_1cbe30((*(u8 (*)[0x10])(rgp_blk1 + 0x30)), arg1);
    d = b->mx[0] - b->mn[0];
    if (d < 0.0f) {
        e = -d;
    } else {
        e = d;
    }
    b->h[0] = 0.5f * e;
    d = b->mx[1] - b->mn[1];
    if (d < 0.0f) {
        e = -d;
    } else {
        e = d;
    }
    b->h[1] = 0.5f * e;
    d = b->mx[2] - b->mn[2];
    if (d < 0.0f) {
        e = -d;
    } else {
        e = d;
    }
    b->h[2] = 0.5f * e;
    b->m[0] = (*(f32 (*)[12])(rgp_blk1 + 0x0))[0];
    b->m[1] = (*(f32 (*)[12])(rgp_blk1 + 0x0))[2];
    b->m[2] = (*(f32 (*)[12])(rgp_blk1 + 0x0))[8];
    b->m[3] = (*(f32 (*)[12])(rgp_blk1 + 0x0))[10];
    MatMulVec4Args_1cb7f0(o, (*(f32 (*)[12])(rgp_blk1 + 0x0)), 0.5f * (b->mx[0] + b->mn[0]), 0.5f * (b->mx[1] + b->mn[1]), 0.5f * (b->mx[2] + b->mn[2]), 1.0f);
    b->c[0] = o[0];
    b->c[1] = o[1];
    b->c[2] = o[2];
    b->vol = 8.0f * b->h[0] * b->h[1] * b->h[2];
    b->up = b->c[1] + b->h[1];
    b->dn = b->c[1] - b->h[1];
}
