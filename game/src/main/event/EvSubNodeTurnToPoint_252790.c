/* rgp:protos */
#define RGP_SELF_EvSubNodeTurnToPoint_252790 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: m2c draft references unresolved pseudo-variables (`sp58`,
 * `unksp44`) it could not name, plus an s128 local; 0 round trips spent.
 * Needs asm/matchings/main/EvSubNodeTurnToPoint_252790.s read by hand -- sp58 is likely
 * the second word of a Vec2 whose first word is the named `sp50`. Not
 * attempted. */
/* s49m: 12 */
#include "types.h"
#pragma opt_propagation off

typedef rg_u128 u128;

typedef struct {
    f32 x, y, z, w;
} Vec4;

typedef struct {
    u8 pad0[0x10];
    Vec4 rot;
    s32 count;
} A;

typedef struct {
    u8 pad0[0x44];
    s32 step;
    u8 pad48[0x28];
    Vec4 pos;
    Vec4 rot;
    u8 pad90[0x14];
    f32 speed;
} B;

extern f32 D_0047D1FC;
extern f32 D_0047DB80;
extern f32 D_0047DB84;
extern f32 D_0047DB88;
extern f32 D_0047DB8C;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvSubNodeTurnToPoint_252790(A *a, B *b)
{
    Vec4 d __attribute__((aligned(16)));
    Vec4 r __attribute__((aligned(16)));
    f32 ang;
    f32 diff;

    if (b->step >= a->count) {
        if (a->count > 0) {
            sceVu0CopyVector(&b->rot, &a->rot);
        }
        b->step = 0;
        return 0;
    }
    if (b->step <= 0) {
        ang = 0.0f;
        *(u128 *)&r = 0;
        VecSub_13be40(&d, &b->pos, &a->rot);
        d.w = 0.0f;
        d.y = 0.0f;
        VecNormalize_13bd90(&d, &d);
        if (d.x != 0.0f || d.z != 0.0f) {
            ang = Atan2f_1291a8(-d.x, -d.z);
        }
        r.y = ang;
        sceVu0CopyVector(&a->rot, &r);
        diff = a->rot.y - b->rot.y;
        if (diff > D_0047D1FC) {
            diff -= D_0047DB84;
        } else if (diff <= D_0047DB80) {
            diff += D_0047DB84;
        }
        b->speed = diff / a->count;
    } else {
        {
            f32 s = b->speed;
            f32 y = b->rot.y + s;
            f32 l = D_0047D1FC;
            b->rot.y = y;
            if (y > l) {
                b->rot.y = y - D_0047DB84;
            } else if (y <= D_0047DB88) {
                b->rot.y = y + D_0047DB8C;
            }
        }
    }
    b->step++;
    return 1;
}
