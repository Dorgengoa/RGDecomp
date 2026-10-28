/* rgp:protos */
#define RGP_SELF_AiSeparateFromOthers_2cd2d0 1
#include "port/game_protos.h"
#line 1
/* PARKED at triage (0 round trips): m2c's draft invents `unkspC4`/`unkspB4`
 * names (never declared) aliasing the sp90/spA0/spB0/spC0 s128 locals, plus
 * an adda.s/madd.s M2C_ERROR site and the same `(var_18*4)+sp` ambiguous
 * local-array pattern as AttackChainMarkersShow_382c40 -- three hard patterns stacked in one
 * unit. Deferred to preserve lane throughput. See asm/matchings/main/AiSeparateFromOthers_2cd2d0.s. */
/* s49m: len(ed=2,d=-1) */
#include "types.h"

typedef rg_u128 u128;
typedef struct { f32 x, y, z, w; } V4;

typedef struct Actor {
    u8 pad0[0x180];
    V4 pos;
    u8 pad190[0x4C8 - 0x190];
    f32 radius;
    f32 height;
} Actor;

extern f32 D_0047D240;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiSeparateFromOthers_2cd2d0(s32 arg0, s32 self, V4 *target)
{
    s32 ids[0x20] __attribute__((aligned(16)));
    V4 pos __attribute__((aligned(16)));
    V4 op __attribute__((aligned(16)));
    V4 d __attribute__((aligned(16)));
    V4 acc __attribute__((aligned(16)));
    s32 id;
    s32 n;
    Actor *me;

    s32 moved;
    s32 i;
    f32 h;
    f32 r;
    f32 dist;
    f32 dd;
    f32 or;
    f32 sum;
    Actor *o;
    n = AiCollectAllIds_2cd4d0(ids, 0x20);
    *(u128 *)&acc = 0;
    moved = 0;
    me = ((Actor *)ObjRecGetLiveObject_1c4a90(arg0, self));
    if (me == NULL) {
        return 0;
    }
    *(u128 *)&pos = *(u128 *)&me->pos;
    r = D_0047D240 * me->radius;
    h = D_0047D240 * me->height;
    dist = VecDistance_13d3d0(&pos, target);
    for (i = 0; i < n; i++) {
        id = *(s32 *)((u32)&ids[i]);
        if (self == id) {
            continue;
        }
        o = ((Actor *)ObjRecGetLiveObject_1c4a90(arg0, id));
        if (o == NULL) {
            continue;
        }
        *(u128 *)&op = *(u128 *)&o->pos;
        or = D_0047D240 * o->radius;
        if (!(pos.y <= op.y + D_0047D240 * o->height)) {
            continue;
        }
        if (pos.y + h < op.y) {
            continue;
        }
        dd = VecDistance_13d3d0(&pos, &op);
        sum = r + or;
        if (!(dd <= sum)) {
            continue;
        }
        VecSub_13be40(&d, &pos, &op);
        VecNormalize_13bd90(&d, &d);
        VecScale_13be00(&d, &d, sum - dd);
        VecAdd_13be20(&acc, &acc, &d);
        moved = 1;
    }
    if (moved != 0) {
        VecNormalize_13bd90(&acc, &acc);
        VecScale_13be00(&acc, &acc, dist);
        VecAdd_13be20(&pos, &pos, &acc);
        ModelSetPos_151110(me, &pos);
    }
    return moved;
}
