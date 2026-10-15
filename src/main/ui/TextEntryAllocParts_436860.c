#include "types.h"

extern void *MemStackNew_14e230(s32 arg0, s32 arg1);
extern void UiEntryListReset_28ec80(void *arg0);
extern void UiWidgetListReset_2912e0(void *arg0);

s32 TextEntryAllocParts_436860(void **arg0, s32 arg1, s32 arg2)
{
    void *p;

    if (arg1 == 0) {
        return 1;
    }
    p = MemStackNew_14e230(0x14, arg1);
    arg0[0] = p;
    if (p != NULL) {
        UiWidgetListReset_2912e0(p);
    } else {
        return 2;
    }
    p = MemStackNew_14e230(0x24, arg1);
    arg0[1] = p;
    if (p != NULL) {
        UiEntryListReset_28ec80(p);
    } else {
        return 3;
    }
    p = MemStackNew_14e230(0xC, arg1);
    arg0[2] = p;
    if (p != NULL) {
        *(s32 *)((u8 *)p + 0x4) = 0;
        *(s32 *)((u8 *)p + 0x8) = 0;
        *(u16 *)((u8 *)p + 0x0) = 0;
        *(s32 *)((u8 *)arg0[2] + 0x8) = arg2;
    } else {
        return 4;
    }
    *(u16 *)((u8 *)arg0 + 0xE6) = 0;
    return 0;
}
