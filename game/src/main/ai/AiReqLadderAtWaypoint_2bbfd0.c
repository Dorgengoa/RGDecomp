/* rgp:protos */
#define RGP_SELF_AiReqLadderAtWaypoint_2bbfd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

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

s32 AiReqLadderAtWaypoint_2bbfd0(u8 *self, s32 target, s32 other, Vec *pos, Vec *pos2, s32 idx) {
    Vec posT __attribute__((aligned(16)));
    Vec posO __attribute__((aligned(16)));
    Vec v __attribute__((aligned(16)));
    s8 flag;
    f32 dist;
    f32 dy;
    f32 ty;
    f32 oy;
    Vec *home;
    s32 key;
    s32 it;
    s8 blocked;
    s32 cur;


    if (target == 0) {
        return 0;
    }
    CharaGetPos_2388a0(target, &posT);
    flag = 0;
    if (other != 0 && ((short)CharaGetActionMode_213850(other)) == 7) {
        flag = 1;
    }
    blocked = 0;
    it = DListGetHead_42ea60(((s32)ActionMgrGetCharaList_233b40(((s32)GetActionMgr_1fdb50()))));
    while (it != 0) {
        cur = it + 0x10;
        it = DListGetNext_42eb30(it);
        key = ((short)CharaGetId_214a80(cur));
        if (key == ((short)CharaGetId_214a80(target))) {
            continue;
        }
        CharaGetPos_2388a0(cur, &posO);
        dist = VecDistSqXZ_1cb390(&posT, &posO);
        if (((short)CharaGetActionMode_213850(cur)) == 7) {
            ty = posT.y;
            oy = posO.y;
            dy = oy - ty;
            if ((dy > 0.0f && dy < 80.0f) || ((dy = ty - oy) >= 0.0f && dy < 140.0f)) {
                if (dist < 3600.0f) {
                    blocked = 1;
                    break;
                }
            }
        }
        if (((short)CharaGetActionMode_213850(cur)) == 7) {
            continue;
        }
        if (!(CharaGetFlags_2124b0(cur) & 0x80020) && !(CharaGetFlags_2124b0(cur) & 0x80040)) {
            continue;
        }
        blocked = 1;
        break;
    }
    if ((s8)blocked == 0) {
        home = (Vec *)(self + idx * 32 + 0x1C0);
        if (VecDistSqXZ_1cb390(home, &posT) < 500.0f) {
            if (AiWarpToWaypointOffscreenMaybe_2bc6c0(self, target, pos, *(s8 *)(self + 0x251)) != 0) {
                return 1;
            }
            if (*(s8 *)(self + 0x250) < 2) {
                VecCopy_1cbe30(&v, pos);
            } else {
                VecCopy_1cbe30(&v, home);
            }
            if (v.y > 5.0f + posT.y) {
                if (flag == 0 || *(s8 *)(self + 0x250) >= 2 || !(pos->y < pos2->y)) {
                    CharaAddFlags_212460(target, (long long)(0x80020));
                }
            } else {
                if (flag == 0 || *(s8 *)(self + 0x250) >= 2 || pos->y <= pos2->y) {
                    CharaAddFlags_212460(target, (long long)(0x80040));
                }
            }
            return 1;
        }
        return 2;
    }
    return 0;
}
