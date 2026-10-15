#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s32 id;
    void (*fn)(void);
} Cfg;

extern void NavCfgCmdGraphCreate_30aa20(void);
extern void FUN_0030aa10(void);
extern void NavCfgCmdAddNode_30a8b0(void);
extern void NavCfgCmdAddEdge_30a770(void);
extern void NavCfgCmdNodeFlags_30a6d0(void);
extern void NavCfgCmdEdgeFlags_30a630(void);
extern Cfg D_004523B0[7];
typedef struct { Cfg c[7]; } Tbl7;

typedef struct {
    f32 x, y, z, w;
} V4;

typedef struct {
    u8 b[0x830];
} Ctx;

extern void *FUN_001dcba0_dummy;
extern s32 MapAreaFindBlockNoByNavGraphId_1dcba0(void *, s32);
extern void *MapSlotsFindBlockById_1e49b0(void *, s32, s32);
extern void *MapFindAreaSlotById_1e4cb0(void *, s32);
extern void MapDataGetRotVec4_1e7720(void *, V4 *);
extern void MapDataGetPosVec4_1e7740(void *, V4 *);
extern void *GetMapMgr_201a90(void);
extern void NavGraphFinalize_30f700(void *);
extern void NavGraphSetHasXform_310db0(void *, s32);
extern void NavGraphSetXform_310dc0(void *, V4 *, V4 *);
extern void CfgVmRun_42fa20(Ctx *);
extern void CfgVmLoad_42fac0(Ctx *, s32, s32);
extern void CfgVmRegisterCmds_42fb00(Ctx *, Cfg *);
extern void CfgVmReset_42fc10(Ctx *);
extern void *D_0048296C;
extern s32 D_00482970;
extern s32 D_00482974;
extern s32 D_00482978;
extern s8 D_0048297C;

static inline void clear(u8 *q, u32 n)
{
    if (q) {
        for (; n != 0; n--) {
            *q++ = 0;
        }
    }
}

s32 NavGraphLoadCfg_30a420(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    Cfg cfg[7];
    Ctx ctx;
    V4 v80;
    V4 v70;
    V4 v60;
    V4 v50;
    void *mgr;
    void *obj;
    void *o2;
    s32 r;

    if (arg0 == 0) {
        goto fail;
    }
    if (arg1 <= 0) {
        goto fail;
    }
    if (arg2 == 0) {
        goto fail;
    }
    if (arg3 < 0) {
        goto fail;
    }
    if (arg4 < 0) {
fail:
        return 0;
    }
    *(Tbl7 *)cfg = *(Tbl7 *)D_004523B0;
    D_00482970 = arg2;
    D_0048297C = 1;
    D_0048296C = NULL;
    D_00482974 = arg3;
    D_00482978 = arg4;
    CfgVmReset_42fc10(&ctx);
    CfgVmRegisterCmds_42fb00(&ctx, cfg);
    CfgVmLoad_42fac0(&ctx, arg0, arg1);
    CfgVmRun_42fa20(&ctx);
    if (D_0048296C != NULL) {
    mgr = GetMapMgr_201a90();
    obj = MapFindAreaSlotById_1e4cb0(mgr, arg4);
    if (obj != NULL) {
        r = MapAreaFindBlockNoByNavGraphId_1dcba0(obj, arg3);
        if (r >= 0) {
            o2 = MapSlotsFindBlockById_1e49b0(mgr, r + 20000, 0);
            if (o2 != NULL) {
                clear((u8 *)&v80, sizeof(v80));
                MapDataGetPosVec4_1e7740(o2, &v70);
                NavGraphSetHasXform_310db0(D_0048296C, 1);
                NavGraphSetXform_310dc0(D_0048296C, &v80, &v70);
            }
        } else {
            if (arg3 / 100 / 100 == 1) {
                MapDataGetPosVec4_1e7740(obj, &v50);
                MapDataGetRotVec4_1e7720(obj, &v60);
                NavGraphSetHasXform_310db0(D_0048296C, 1);
                NavGraphSetXform_310dc0(D_0048296C, &v60, &v50);
            }
        }
    }
    NavGraphFinalize_30f700(D_0048296C);
    }
    return 1;
}
