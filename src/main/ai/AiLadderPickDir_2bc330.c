#include "types.h"
#pragma opt_propagation off
#pragma opt_loop_invariants off

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

f32 VecDistSqXZ_1cb390(Vec *, Vec *);
s32 GetActionMgr_1fdb50(void);
void CharaAddFlags_212460(s32, s32);
s32 CharaGetActionMode_213850(s32);
s32 CharaGetId_214a80(s32);
s32 ActionMgrGetCharaList_233b40(s32);
void CharaGetPos_2388a0(s32, Vec *);
s32 AiWarpToWaypointOffscreenMaybe_2bc6c0(u8 *, s32, Vec *, s32);
s32 DListGetHead_42ea60(s32);
s32 DListGetNext_42eb30(s32);

void AiLadderPickDir_2bc330(u8 *self, s32 unit, s32 target, Vec *pA_, Vec *pB_, s32 idx) {
    Vec *pA;
    Vec *pB;
    Vec posA;
    s32 down;
    s32 up;
    s8 count;
    s32 it;
    s32 extra;
    Vec posB;
    s32 u;
    s8 lvl;
    f32 d;

    pA = pA_;
    pB = pB_;
    if (unit == 0) {
        return;
    }
    if (AiWarpToWaypointOffscreenMaybe_2bc6c0(self, unit, pA_, idx) != 0) {
        return;
    }
    CharaGetPos_2388a0(unit, &posA);
    up = 1;
    count = 0;
    down = up;
    it = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(GetActionMgr_1fdb50()));
    while (it != 0) {
        pA = pA_;
        pB = pB_;
        u = it + 0x10;
        it = DListGetNext_42eb30(it);
        if (CharaGetId_214a80(u) == CharaGetId_214a80(unit)) {
            continue;
        }
        CharaGetPos_2388a0(u, &posB);
        extra = 0;
        if (target == u && CharaGetActionMode_213850(target) != 7) {
            extra = 10;
        }
        if (CharaGetActionMode_213850(u) != 7 && target != u) {
            continue;
        }
        d = posB.y - posA.y;
        if (d < 0.0f) {
            d = -d;
        }
        if (!(d < 70.0f + (f32)extra)) {
            continue;
        }
        if (!(VecDistSqXZ_1cb390(&posA, &posB) < (f32)625)) {
            continue;
        }
        if (!(posB.y <= 5.0f + posA.y)) {
            up = 0;
            if (posB.y - posA.y < 50.0f + (f32)extra) {
                count--;
            }
        } else {
            down = 0;
            if (posA.y - posB.y < 50.0f + (f32)extra) {
                count++;
            }
        }
    }
    lvl = *(s8 *)(self + 0x250);
    if (lvl < 3) {
        if (!(pA->y <= 5.0f + posA.y)) {
            if (pA->y < pB->y) {
                count = -1;
            } else if (up) {
                count++;
            }
        } else if (!(pA->y <= pB->y)) {
            count = 1;
        } else if (down) {
            count--;
        }
    }
    if (count > 0) {
        CharaAddFlags_212460(unit, 0x80020);
        return;
    }
    if (count < 0) {
        CharaAddFlags_212460(unit, 0x80040);
        return;
    }
    if (lvl >= 2) {
        if (!(((f32 *)(self + 0x1C4))[idx * 8] <= 5.0f + posA.y)) {
            if (up) {
                CharaAddFlags_212460(unit, 0x80020);
            }
        } else if (down) {
            CharaAddFlags_212460(unit, 0x80040);
        }
    }
}
