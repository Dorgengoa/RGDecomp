/* rgp:protos */
#define RGP_SELF_NavGraphLoadCfg_30a420 1
#define RGP_SELF_clear 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s32 id;
    void (*fn)(void);
} Cfg;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Cfg D_004523B0[7];
typedef struct { Cfg c[7]; } Tbl7;

typedef struct {
    f32 x, y, z, w;
} V4;

typedef struct {
    u8 b[0x830];
} Ctx;

extern void *FUN_001dcba0_dummy;
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
    Cfg cfg[7] __attribute__((aligned(16)));
    Ctx ctx __attribute__((aligned(16)));
    V4 v80 __attribute__((aligned(16)));
    V4 v70 __attribute__((aligned(16)));
    V4 v60 __attribute__((aligned(16)));
    V4 v50 __attribute__((aligned(16)));
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
