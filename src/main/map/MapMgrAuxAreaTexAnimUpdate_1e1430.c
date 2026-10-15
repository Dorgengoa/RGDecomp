#include "types.h"

extern void TexGroupUpdateAnim_157ca0(s32, s32, f32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern f32 GameSceneGetTimeStep_1ceba0(s32);
extern void MapDataAnimStep_1e6600(s32, f32);
extern s32 MapDataGetTexGroupCount_1e78a0(s32);
extern s32 MapDataGetTexGroupBase_1e78e0(s32);
extern s32 MapDataIsLoadedOrUnloading_1e7980(s32);
extern s32 GetCurrentScene_1f5be0(void);

void MapMgrAuxAreaTexAnimUpdate_1e1430(s32 arg0)
{
    f32 temp_f0;
    s32 temp_16;
    s32 temp_17;
    s32 temp_19;
    s32 var_18;

    temp_f0 = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    MapDataAnimStep_1e6600(arg0 + 0x2058, temp_f0);
    if (MapDataIsLoadedOrUnloading_1e7980(arg0 + 0x2058) != 0) {
        temp_19 = GetDrawCtxNameTable_15de40();
        temp_17 = MapDataGetTexGroupBase_1e78e0(arg0 + 0x2058);
        temp_16 = MapDataGetTexGroupCount_1e78a0(arg0 + 0x2058);
        for (var_18 = 0; var_18 < temp_16; var_18++) {
            TexGroupUpdateAnim_157ca0(temp_19, temp_17 + var_18, temp_f0);
        }
    }
}
