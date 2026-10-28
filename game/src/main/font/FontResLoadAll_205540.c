/* rgp:protos */
#define RGP_SELF_FontResLoadAll_205540 1
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

void FontResLoadAll_205540(void)
{
    s32 temp_18 = ((s32)GetSystemMemStack_202600());
    s32 temp_2 = ((s32)GetReadBuffHeap_2025e0());
    s32 temp_2_2 = ((s32)MemStackHeapAlloc_14db10(temp_2, 2, 0, 0x40));

    if (temp_2_2 != 0) {
        SysFontHeapInit_3134e0(temp_18);
        FontSystemLoadIfPak_313470(1, temp_2_2, 0x338);
        DebugFontLoad_313130(temp_18, temp_2_2, 0x329);
        MemStackReturnToOwnerMaybe_14dad0(temp_2);
        MemStackHeapFree_14dcb0(temp_2, temp_2_2);
    }
}
