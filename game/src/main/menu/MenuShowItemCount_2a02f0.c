/* rgp:protos */
#define RGP_SELF_MenuShowItemCount_2a02f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 MenuShowItemCount_2a02f0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_16;
    void *temp_2;

    if (*(s32 *)((u8 *)arg0 + 0x20) == *(s8 *)((u8 *)arg0 + 0x11)) {
        temp_16 = *(s32 *)((u8 *)arg0 + 0x28);
        if (temp_16 > 0) {
                    if (temp_16 > 1) {
            temp_2 = UiGetWidgetSubItem_28f2b0(*(s32 *)((u8 *)arg0 + 0x0), arg3, arg4);
            if (temp_2 == NULL) {
                return 0;
            }
            *(s64 *)((u8 *)temp_2 + 0x8) = (s64)temp_16;
            *(s16 *)((u8 *)temp_2 + 0x1C) = 0xA;
            *(s16 *)((u8 *)temp_2 + 0x1E) = 0x10;
        }
        } else {
            UiSetSpriteSizeUvSize_28f670(*(s32 *)((u8 *)arg0 + 0x0), arg1, 0, 0, 0, 0, arg4);
            UiSetSpriteSizeUvSize_28f670(*(s32 *)((u8 *)arg0 + 0x0), arg2, 0, 0, 0, 0, arg4);
        }
    }
    return 1;
}
