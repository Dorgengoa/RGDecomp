/* rgp:protos */
#define RGP_SELF_PartySnapToGroundMaybe_2f10e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

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
extern f32 D_0045B080[];

void PartySnapToGroundMaybe_2f10e0(f32 *arg0)
{
    f32 t;
    u8 buf[0x3000] __attribute__((aligned(16)));
    V4 c __attribute__((aligned(16)));
    V4 b __attribute__((aligned(16)));
    s32 g;
    s32 lst;
    s32 wrl;
    s32 ctx;
    f32 k;
    f32 h;
    s32 n;
    s32 i;
    s32 e;
    s32 cnt;
    s32 w;
    s32 id;

    g = (s32)GetGameData_1fede0();
    lst = ((s32)GetActionMgr_1fdb50());
    wrl = ((s32)GetMapMgr_201a90());
    ctx = GetCurrentScene_1f5be0();
    k = D_0045B080[0];
    h = 5.0f * k;
    arg0[0] += k;
    arg0[1] += h;
    arg0[2] += k;
    arg0[4] -= k;
    arg0[5] -= h;
    arg0[6] -= k;
    VecLerpPoint_1cbac0(&c, arg0, arg0 + 4, 0.5f);
    n = CollTriListCompact_1ca3e0(buf, MapEvCollectCollTrisNearMaybe_1ff130(buf, 0x80, arg0, &c, -1, h));
    cnt = PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1);
    cnt = (s32)(u32)cnt;
    for (i = 0; i < cnt; i++) {
        e = ((s32)ActionMgrFindById_233b50(lst, ((short)PartyGetMemberId_3c2490(*(s32 *)(g + 0x18), i))));
        if (e == 0) {
            continue;
        }
        CharaGetPos_2388a0(e, &b);
        w = MapFindBlockAtPos_1e3a00(wrl, &b, 0.0f);
        if (w != 0 && ((unsigned char)MapDataIsLoaded_1e79d0(w)) != 0) {
            b.y += k;
            {
                V4 a __attribute__((aligned(16))) = {0};
                t = 0.0f;
                a.y = -3.0f * k;
                if (CollRaycastNearestFiltered_1c8500(buf, n, ((short)CharaGetCollIgnoreMask_238950(e)), &b, &a, &t, 0.5f, 1.0f) >= 0) {
                    b.y = 0.0f + b.y + a.y * t;
                    CharaSetPos_213a40(e, &b);
                }
            }
        }
    }
    TaskCharaBegin_1fb140();
    TaskCharaAction_1fa5c0();
    TaskCharaMove_1f9790();
    TaskCharaEnd_1fae60();
    for (i = 0; i < cnt; i++) {
        id = ((short)PartyGetMemberId_3c2490(*(s32 *)(g + 0x18), i));
        e = ((s32)ActionMgrFindById_233b50(lst, id));
        if (e != 0) {
            CharaResetBattleStateMaybe_212f20(e, 1);
            ParamTableSetAlpha_1cfb10(ctx, id, 1.0f);
        }
    }
}
