#include "types.h"

extern void *MapFindAreaSlotById_1e4cb0(void *, s32);
extern s32 MapDataIsLoaded_1e79d0(void *);
extern s32 MapAreaGetBaseFrameRotPos_1da9a0(s32, void *, void *, s32);
extern void MapAreaPlace_1da680(void *, void *, f32);

void MapAlignAreaToAreaNode_1e3fb0(void *arg0, s32 arg1)
{
    s32 sp50[4];
    s32 sp40[4];
    void *temp_2;
    void *temp_2_2;
    s16 key2;

    temp_2 = MapFindAreaSlotById_1e4cb0(arg0, *(s16 *)((u8 *)arg0 + 2));
    if (temp_2 == NULL || MapDataIsLoaded_1e79d0(temp_2) == 0) {
        return;
    }
    key2 = *(s16 *)((u8 *)arg0 + 4);
    temp_2_2 = MapFindAreaSlotById_1e4cb0(arg0, key2);
    if (temp_2_2 == NULL || MapDataIsLoaded_1e79d0(temp_2_2) == 0) {
        return;
    }
    if (MapAreaGetBaseFrameRotPos_1da9a0((s32)temp_2, sp50, sp40, arg1) != 0) {
        MapAreaPlace_1da680(temp_2_2, sp40, *(f32 *)&sp50[1]);
    }
}
