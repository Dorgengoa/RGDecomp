/* rgp:protos */
#define RGP_SELF_MapTickAnims_1e1ac0 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapTickAnims_1e1ac0(u8 *self)
{
    u8 *q;
    s32 buf[0x14] __attribute__((aligned(16)));
    s32 i;
    f32 f;
    s32 cnt;
    s32 h;
    s32 n;
    s32 base;
    s32 v;
    s32 k;
    s32 p;
    s32 j;

    v = -1;
    p = MapGetActiveArea_1e56e0((int)self);
    if (p != 0 || ((unsigned char)MapDataIsLoaded_1e79d0(p)) != 0) {
        v = MapDataGetObjRecSlot_1e7860(p);
    }
    *(s32 *)(((u8 *)GetCurrentScene_1f5be0()) + 0x434C) = v;
    p = MapGetAreaSlot2_1e5740(self);
    if (p != 0 && ((unsigned char)MapDataIsLoaded_1e79d0(p)) != 0) {
        MapApplyAreaEnv_1e2bc0(self, ((short)MapDataGetId_1e7bd0(p)), 1);
    }
    MapEnvSlotsStep_1e5cc0(self + 0x68);
    f = GameSceneGetTimeStep_1ceba0(((u8 *)GetCurrentScene_1f5be0()));
    MapSkyStepStub_1e6010();
    q = self + 0x1928;
    for (i = 0; i < 4; i++) {
        MapAreaTreeAnimStep_1d9970(q, f);
        q += 0x1CC;
    }
    n = MapCollectActiveAll_1e3f10(self, buf, 0x14);
    h = GetDrawCtxNameTable_15de40();
    for (k = 0; k < n; k++) {
        base = MapDataGetTexGroupBase_1e78e0(buf[k]);
        cnt = MapDataGetTexGroupCount_1e78a0(buf[k]);
        for (j = 0; j < cnt; j++) {
            TexGroupUpdateAnim_157ca0(h, base + j, f);
        }
    }
}
