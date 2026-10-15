#include "types.h"

extern void MemStackReturnToOwnerMaybe_14dad0(s32);
extern s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern s32 GetReadBuffHeap_2025e0(void);
extern s32 GetSystemMemStack_202600(void);
extern void DebugFontLoad_313130(s32, s32, s32);
extern void FontSystemLoadIfPak_313470(s32, s32, s32);
extern void SysFontHeapInit_3134e0(s32);

void FontResLoadAll_205540(void)
{
    s32 temp_18 = GetSystemMemStack_202600();
    s32 temp_2 = GetReadBuffHeap_2025e0();
    s32 temp_2_2 = MemStackHeapAlloc_14db10(temp_2, 2, 0, 0x40);

    if (temp_2_2 != 0) {
        SysFontHeapInit_3134e0(temp_18);
        FontSystemLoadIfPak_313470(1, temp_2_2, 0x338);
        DebugFontLoad_313130(temp_18, temp_2_2, 0x329);
        MemStackReturnToOwnerMaybe_14dad0(temp_2);
        MemStackHeapFree_14dcb0(temp_2, temp_2_2);
    }
}
