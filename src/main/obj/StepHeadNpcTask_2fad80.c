#include "types.h"
#include "vec.h"

extern void *ObjRecGetLiveObject_1c4a90(s32, s16);
extern s32 GetStaticScene_1c6c70(void);
extern void *GetGameData_1fede0(void);
extern void NpcObjHeadLookUpdate_2fc3f0(void *);
extern void sceVu0CopyVector(void *, u128 *);
extern f32 D_0047D5D0;

void StepHeadNpcTask_2fad80(void *arg0)
{
    u128 sp40;
    s32 temp_17;
    void *temp_2;
    u8 *var_18;
    s32 i;

    if (!(*(s16 *)((u8 *)arg0 + 0x220) & 4)) {
        temp_17 = GetStaticScene_1c6c70();
        temp_2 = ObjRecGetLiveObject_1c4a90(temp_17, *(s16 *)((u8 *)(*(void **)((u8 *)GetGameData_1fede0() + 0x18)) + 0x18E));
        if (temp_2 != NULL) {
            sp40 = *(u128 *)((u8 *)temp_2 + 0x180);
            *(f32 *)((u8 *)&sp40 + 4) = *(f32 *)((u8 *)&sp40 + 4) +
                                         D_0047D5D0 * *(f32 *)((u8 *)temp_2 + 0x4CC);
        }
        var_18 = *(u8 **)((u8 *)arg0 + 0x4);
        i = 0;
        while (i < *(s16 *)((u8 *)arg0 + 0x8)) {
            if (*(s8 *)(var_18 + 0xD1) == 0) {
                sceVu0CopyVector(var_18 + 0x90, &sp40);
                NpcObjHeadLookUpdate_2fc3f0(var_18);
            }
            var_18 += 0xE0;
            i += 1;
        }
    }
}
