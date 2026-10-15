#include "types.h"

extern s32 DebugMenuWidgetGetChild_209d90(void *, s32);
extern s32 DebugMenuWidgetIsDisabledMaybe_209e80(s32);

s32 DebugMenuWidgetCursorPrev_209ce0(void *arg0, s32 arg1) {
    u32 orig;
    s32 i;

    if (*(s32 *)((u8 *)arg0 + 0x18) == 0) {
        return -1;
    }
    if (arg1 < 0) {
        arg1 = 0;
    }
    i = arg1;
    for (;;) {
        i -= 1;
        if (i < 0) {
            i = *(s16 *)((u8 *)arg0 + 0x1C) - 1;
        }
        if (DebugMenuWidgetIsDisabledMaybe_209e80(DebugMenuWidgetGetChild_209d90(arg0, i)) == 0 || i == arg1) {
            break;
        }
    }
    return i;
}
