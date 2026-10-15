#include "types.h"


void *UiGetWidgetSubItem_28f2b0(s32 xa0, s32 xa1, s32);                            /* extern */

void UiSetSubItemFlags_28ef30(s32 pd0, s32 pd1, s64 arg2, s32 arg3, s32 arg4) {
    s32 u_0;
    s32 u_1;
    s32 var_3;
    void *temp_2;

    temp_2 = UiGetWidgetSubItem_28f2b0(pd0, pd1, arg4);
    if (temp_2 != NULL) {
        switch(arg3) {
        case 1: *(s16 *)((u8*)temp_2+0x1A) |= (s16)arg2; break;
        case 0: *(s16 *)((u8*)temp_2+0x1A) = arg2; break;
        case -1: *(s16 *)((u8*)temp_2+0x1A) &= (s16)~arg2; break;
        }
    }
}
