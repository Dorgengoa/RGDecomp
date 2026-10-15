#include "types.h"

extern void MemStackHeapReinit_14de90(s32);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void MapSkyResetModels_17f8a0(void *);
extern void ObjRecTableResetSlot_1c3a50(void *, s32);
extern void LoaderReleaseHandle_1ccb70(void *);
extern s32 MapSkyGetHeap_1e6330(void *);
extern void *GetCurrentScene_1f5be0(void);

void MapSkyUnload_1e6190(void *arg0)
{
    s32 temp_18;
    s32 temp_2;
    s32 i;
    void *temp_2_2;

    LoaderReleaseHandle_1ccb70((u8 *)arg0 + 0x17B0);
    temp_18 = GetDrawCtxNameTable_15de40();
    i = 0;
    do {
        NameTableFreeGroup_158ac0(temp_18, i);
        i += 1;
    } while (i < 4);
    temp_2 = MapSkyGetHeap_1e6330(arg0);
    if (temp_2 != 0) {
        MemStackHeapReinit_14de90(temp_2);
    }
    temp_2_2 = GetCurrentScene_1f5be0();
    ObjRecTableResetSlot_1c3a50(temp_2_2, 0);
    *(s32 *)((u8 *)temp_2_2 + 0x4380) = -1;
    MapSkyResetModels_17f8a0(arg0);
    *(s16 *)((u8 *)arg0 + 0x17C0) = -1;
    *(s16 *)((u8 *)arg0 + 0x17C2) = -1;
    *(s16 *)((u8 *)arg0 + 0x17C6) = 0;
}
