#include "types.h"

s32 GetDrawCtxNameTable_15de40();
void TexGroupUpdateAnim_157ca0(s32, s32, f32);
f32 GameSceneGetTimeStep_1ceba0(u8 *);
void MapAreaTreeAnimStep_1d9970(u8 *, f32);
void MapApplyAreaEnv_1e2bc0(u8 *, s32, s32);
s32 MapCollectActiveAll_1e3f10(u8 *, s32 *, s32);
s32 MapGetActiveArea_1e56e0();
s32 MapGetAreaSlot2_1e5740(u8 *);
void MapEnvSlotsStep_1e5cc0(u8 *);
void MapSkyStepStub_1e6010(u8 *);
s32 MapDataGetObjRecSlot_1e7860(s32);
s32 MapDataGetTexGroupCount_1e78a0(s32);
s32 MapDataGetTexGroupBase_1e78e0(s32);
s32 MapDataIsLoaded_1e79d0(s32);
s32 MapDataGetId_1e7bd0(s32);
u8 *GetCurrentScene_1f5be0();

void MapTickAnims_1e1ac0(u8 *self)
{
    u8 *q;
    s32 buf[0x14];
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
    p = MapGetActiveArea_1e56e0();
    if (p != 0 || MapDataIsLoaded_1e79d0(p) != 0) {
        v = MapDataGetObjRecSlot_1e7860(p);
    }
    *(s32 *)(GetCurrentScene_1f5be0() + 0x434C) = v;
    p = MapGetAreaSlot2_1e5740(self);
    if (p != 0 && MapDataIsLoaded_1e79d0(p) != 0) {
        MapApplyAreaEnv_1e2bc0(self, MapDataGetId_1e7bd0(p), 1);
    }
    MapEnvSlotsStep_1e5cc0(self + 0x68);
    f = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    MapSkyStepStub_1e6010(self + 0xE0);
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
