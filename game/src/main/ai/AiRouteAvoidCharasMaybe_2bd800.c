/* rgp:protos */
#define RGP_SELF_AiRouteAvoidCharasMaybe_2bd800 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct { f32 x, y, z, w; } V4;
typedef struct { u8 a; u8 b; } OK2;

typedef struct {
    V4 pos;
    f32 t;
    f32 rad;
    f32 d;
    s32 id;
} Hit;

typedef struct {
    u8 pad0[0x1B0];
    V4 f1B0;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D404;
extern V4 D_0047ED80 __attribute__((section(".sdata")));
extern u8 D_0047ED90[2];
extern V4 D_0047EDA0 __attribute__((section(".sdata")));
extern V4 D_0047EDB0 __attribute__((section(".sdata")));

f32 AiRouteAvoidCharasMaybe_2bd800(Obj *self, s32 *pp, V4 *outPos, V4 *outDir, V4 *tgt, f32 r, f32 dist) {
    u8 b1;
    volatile u8 ok[2];
    V4 cur __attribute__((aligned(16)));
    V4 me __attribute__((aligned(16)));
    V4 op __attribute__((aligned(16)));
    Hit hits[2] __attribute__((aligned(16)));
    V4 tmp __attribute__((aligned(16)));
    V4 up __attribute__((aligned(16)));
    Hit hits2[2] __attribute__((aligned(16)));
    V4 up2 __attribute__((aligned(16)));
    V4 e __attribute__((aligned(16)));
    V4 dd __attribute__((aligned(16)));
    V4 up3 __attribute__((aligned(16)));
    s32 mine;
    f32 myRad;
    s32 mgr;
    f32 reach;
    s32 node;
    s32 o;
    s32 other;
    f32 rad;
    f32 t;
    f32 d;
    f32 ad;
    s32 side;
    f32 sc;
    s32 *pid;
    f32 q;
    s32 i;
    f32 acc;
    f32 f;
    f32 ang;

    VecCopy_1cbe30(&cur, tgt);
    mine = *pp;
    CharaGetPos_2388a0(mine, &me);
    myRad = CharaGetCollRadius_2386a0(mine);
    if (dist < 0.0f) {
        dist = VecDistXZ_1cb3f0(&cur, &me);
    }
    mgr = ((s32)GetActionMgr_1fdb50());
    reach = myRad + AiGetApproachMarginMaybe_2c0fc0(self);
    ActionMgrFindById_233b50(mgr, AiGetTargetCharaId_2c0fd0(self));
    if (dist <= r + myRad + AiGetStopDistance_2c0fb0(self)) {
        VecCopy_1cbe30(outPos, &cur);
        VecSub_1cbd00(outDir, &cur, &me);
        outDir->y = 0.0f;
        return r;
    }
    hits[0].id = -1;
    hits[1].id = -1;
    if (!(dist <= AiGetStopDistance_2c0fb0(self))) {
        node = DListGetHead_42ea60(((s32)ActionMgrGetCharaList_233b40(mgr)));
        while (node != 0) {
            o = node + 0x10;
            node = DListGetNext_42eb30(node);
            if (((short)CharaGetId_214a80(mine)) == ((short)CharaGetId_214a80(o))) {
                continue;
            }
            other = ((s32)CharaGetAi_214a10(o));
            if (AiGetTargetMode_2c10b0(self) != AiGetTargetMode_2c10b0((Obj *)other)) {
                continue;
            }
            switch (AiGetTargetMode_2c10b0(self)) {
            case 2:
                if (AiGetTargetCharaId_2c0fd0(self) == ((short)CharaGetId_214a80(o))) {
                    continue;
                }
                if (AiGetTargetCharaId_2c0fd0(self) != AiGetTargetCharaId_2c0fd0((Obj *)other)) {
                    continue;
                }
                break;
            case 1:
                AiGetTargetPoint_2c0fe0(other, &tmp);
                if (!(VecDistSq_1cb3c0(&self->f1B0, &tmp) < 1.0f)) {
                    continue;
                }
                break;
            default:
                continue;
            }
            CharaGetPos_2388a0(o, &op);
            rad = CharaGetCollRadius_2386a0(o);
            t = SegmentProjectTXZ_1ca2a0(&op, &me, &cur);
            if (t <= 0.0f) {
                continue;
            }
            if (1.0f <= t) {
                continue;
            }
            *(V4 *)&up = D_0047ED80;
            d = TriNormalDot_1cb600(&cur, &me, &op, &up);
            ad = (d < 0.0f) ? -d : d;
            if (ad <= dist * (myRad + rad)) {
                side = (u8)!(d <= 0.0f);
                if (d < 0.0f) {
                    d = -d;
                }
                sc = t * (d - dist * rad);
                pid = &hits[side].id;
                if (*pid < 0 || !(hits[side].d <= sc)) {
                    VecCopy_1cbe30(&hits[side].pos, &op);
                    *pid = ((short)CharaGetId_214a80(o));
                    hits[side].rad = rad;
                    hits[side].t = t;
                    hits[side].d = sc;
                }
            }
        }
        if (hits[0].id >= 0 && hits[1].id >= 0) {
            *(OK2 *)ok = *(OK2 *)&D_0047ED90;
            q = hits[0].rad + reach;
            if (VecDistSqXZ_1cb390(&me, &hits[0].pos) <= q * q) {
                ok[0] = 0;
            }
            q = hits[1].rad + reach;
            if (VecDistSqXZ_1cb390(&me, &hits[1].pos) <= q * q) {
                ok[1] = 0;
            }
            if (ok[0] == 0 && ok[1] == 0) {
                ok[0] = 1;
                ok[1] = 1;
            }
            if (ok[0] == 0) {
                hits[0].id = -1;
            }
            b1 = ok[1];
            if (b1 == 0) {
                hits[1].id = -1;
            }
            if (ok[0] != 0 && b1 != 0) {
                f = VecDistXZ_1cb3f0(&hits[0].pos, &hits[1].pos);
                VecLerpPoint_1cbac0(&cur, &hits[1].pos, &hits[0].pos, hits[1].t / (hits[0].t + hits[1].t) * ((f + hits[0].rad - hits[1].rad) / f));
                q = (hits[0].rad * hits[0].t + hits[1].rad * hits[1].t) / (hits[0].t + hits[1].t);
                r = q + AiGetApproachMarginMaybe_2c0fc0(self);
            } else {
                if (ok[0] != 0) {
                    VecCopy_1cbe30(&cur, &hits[0].pos);
                    r = hits[0].rad + AiGetApproachMarginMaybe_2c0fc0(self);
                }
                if (b1 != 0) {
                    VecCopy_1cbe30(&cur, &hits[1].pos);
                    r = hits[1].rad + AiGetApproachMarginMaybe_2c0fc0(self);
                }
            }
            if (ok[0] != 0 || b1 != 0) {
                dist = VecDistXZ_1cb3f0(&cur, &me);
            }
        } else {
            hits[0].id = -1;
            hits[1].id = -1;
        }
    }
    if (dist <= r + myRad + AiGetStopDistance_2c0fb0(self)) {
        VecCopy_1cbe30(outPos, &cur);
        VecSub_1cbd00(outDir, &cur, &me);
        outDir->y = 0.0f;
        return r;
    }
    hits2[0].id = -1;
    hits2[1].id = -1;
    node = DListGetHead_42ea60(((s32)ActionMgrGetCharaList_233b40(mgr)));
    while (node != 0) {
        o = node + 0x10;
        node = DListGetNext_42eb30(node);
        if (((short)CharaGetId_214a80(o)) == ((short)CharaGetId_214a80(mine))) {
            continue;
        }
        if (hits[0].id == ((short)CharaGetId_214a80(o))) {
            continue;
        }
        if (hits[1].id == ((short)CharaGetId_214a80(o))) {
            continue;
        }
        if (AiGetTargetMode_2c10b0(self) == 2) {
            if (((short)CharaGetId_214a80(o)) == AiGetTargetCharaId_2c0fd0(self)) {
                continue;
            }
        }
        CharaGetPos_2388a0(o, &op);
        rad = CharaGetCollRadius_2386a0(o);
        t = SegmentProjectTXZ_1ca2a0(&op, &me, &cur);
        if (t <= 0.0f) {
            continue;
        }
        if (1.0f <= t) {
            continue;
        }
        *(V4 *)&up2 = D_0047EDA0;
        d = TriNormalDot_1cb600(&cur, &me, &op, &up2);
        side = (u8)!(d <= 0.0f);
        if (d < 0.0f) {
            d = -d;
        }
        sc = t * (d - dist * rad);
        pid = &hits2[side].id;
        if (*pid < 0 || !(hits2[side].d <= sc)) {
            VecCopy_1cbe30(&hits2[side].pos, &op);
            *pid = ((short)CharaGetId_214a80(o));
            hits2[side].rad = rad;
            hits2[side].t = t;
            hits2[side].d = sc;
        }
    }
    acc = 0.0f;
    for (i = 0; i < 2; i++) {
        if (hits2[i].id < 0) {
            continue;
        }
        *(V4 *)&up3 = D_0047EDB0;
        VecLerp_1cbb20(&e, &cur, &me, hits2[i].t);
        VecSub_1cbd00(&dd, &e, &hits2[i].pos);
        dd.y = 0.0f;
        q = reach + hits2[i].rad - VecLengthXZ_1cb490(&dd);
        if (q < 1.0f) {
            continue;
        }
        f = q / (dist * hits2[i].t);
        if (TriNormalDot_1cb600(&cur, &me, &hits2[i].pos, &up3) < 0.0f) {
            acc -= f;
        } else {
            acc += f;
        }
    }
    if (!(((acc < 0.0f) ? -acc : acc) <= D_0047D404)) {
        if (acc < 0.0f) {
            acc = -D_0047D404;
        } else {
            acc = D_0047D404;
        }
    }
    ang = AngleWrap_1cbf30(acc + Atan2f_1291a8(cur.x - me.x, cur.z - me.z));
    outDir->x = Sinf_128fd0(ang);
    outDir->y = 0.0f;
    outDir->z = Cosf_128d30(ang);
    outDir->w = 0.0f;
    VecCopy_1cbe30(outPos, &cur);
    return r;
}
