#include "types.h"

extern void *UiGetWidgetText_28f620(void *unused0, void *unused1, s32 arg3);
extern void strcpy(void *dst, const char *src);

void UiSetTextStringCopy_28f4b0(void *unused0, void *unused1, s32 arg2, s32 arg3) {
    void *p;

    p = UiGetWidgetText_28f620(unused0, unused1, arg3);
    if (p != NULL) {
        if (*(s32 *)((u8 *)p + 4) != 0) {
            if (arg2 != 0) {
                goto copy;
            }
        }
    }
    return;
copy:
    strcpy(*(void **)((u8 *)p + 4), (const char *)arg2);
}
