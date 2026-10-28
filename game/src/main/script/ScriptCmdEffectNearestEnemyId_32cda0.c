/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectNearestEnemyId_32cda0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004826E0;

s32 ScriptCmdEffectNearestEnemyId_32cda0(s32 arg0, s32 arg1)
{
    s32 idx;
    s32 ctx;
    s32 i;
    f32 d;
    idx = ScriptSlotGetInt_3348b0(arg0 + 8);
    ctx = GetCurrentScene_1f5be0();
    {
        f32 pos[4] __attribute__((aligned(16))) = {0.0f, 0.0f, 0.0f, 1.0f};
        f32 tmp[4] __attribute__((aligned(16)));
        if (arg1 != 2) {
            return 0;
        }
        if (idx >= 2) {
            return 0;
        }
        {
            s32 id[2] = {-1, -1};
            f32 dist[2] = {50000.0f, 50000.0f};
            if (D_004826E0 != 0) {
                EffectInstanceGetPos_2dd540(D_004826E0, pos);
                for (i = 0x80; i < 0x90; i++) {
                    if (ObjIsTargetableById_32d010(i) != 0) {
                        if (SceneObjGetPosById_32cf00(ctx, i, tmp) != 0) {
                            d = VecDistance_13d3d0(pos, tmp);
                            if (dist[0] > d) {
                                dist[1] = dist[0];
                                dist[0] = d;
                                id[1] = id[0];
                                id[0] = i;
                            } else if (!(dist[1] <= d)) {
                                dist[1] = d;
                                id[1] = i;
                            }
                        }
                    }
                }
            }
            ScriptSlotStoreIntRef_3347f0(arg0, id[idx]);
            return 1;
        }
    }
}
