#include "types.h"

extern void MotResRelocateBlockList_14bbc0(void **arg0, void *arg1);
extern s32 memcmp(void *arg0, const void *arg1, s32 arg2);
extern u8 D_00458AF0[0x400];

s32 MotResRelocate_14bd50(void **arg0, void *arg1)
{
    u8 *t;
    u8 *p;
    s32 i;
    s32 n;

    *arg0 = arg1;
    if (memcmp(arg1, D_00458AF0, 4) != 0) {
        *arg0 = NULL;
        return 0;
    }
    t = *(u8 **)((u8 *)*arg0 + 0xC);
    if (t != NULL) {
        *(u8 **)((u8 *)*arg0 + 0xC) = (u8 *)arg1 + (s32)t;
    }
    t = *(u8 **)((u8 *)*arg0 + 0x14);
    if (t != NULL) {
        *(u8 **)((u8 *)*arg0 + 0x14) = (u8 *)arg1 + (s32)t;
    }
    t = *(u8 **)((u8 *)*arg0 + 0x20);
    if (t != NULL) {
        *(u8 **)((u8 *)*arg0 + 0x20) = (u8 *)arg1 + (s32)t;
    }
    if (*(s32 *)((u8 *)*arg0 + 0x1C) == 0) {
        *(void **)((u8 *)*arg0 + 0x20) = NULL;
    }
    t = *(u8 **)((u8 *)*arg0 + 0x28);
    if (t != NULL) {
        *(u8 **)((u8 *)*arg0 + 0x28) = (u8 *)arg1 + (s32)t;
    }
    if (*(s32 *)((u8 *)*arg0 + 0x24) == 0) {
        *(void **)((u8 *)*arg0 + 0x28) = NULL;
    }
    MotResRelocateBlockList_14bbc0(arg0, *(void **)((u8 *)*arg0 + 0x20));
    MotResRelocateBlockList_14bbc0(arg0, *(void **)((u8 *)*arg0 + 0x28));
    n = *(s32 *)((u8 *)*arg0 + 0x2C);
    if (n > 0) {
        *(u8 **)((u8 *)*arg0 + 0x30) = (u8 *)arg1 + *(s32 *)((u8 *)*arg0 + 0x30);
        p = *(u8 **)((u8 *)*arg0 + 0x30);
        for (i = 0; i < n; i++) {
            t = *(u8 **)(p + 0xC);
            if (t != NULL && *(s32 *)(p + 0x8) != 0) {
                *(u8 **)(p + 0xC) = (u8 *)arg1 + (s32)t;
                MotResRelocateBlockList_14bbc0(arg0, (u8 *)arg1 + (s32)t);
            }
            t = *(u8 **)p;
            if (t == NULL) {
                break;
            }
            t = p + (s32)t;
            *(u8 **)p = t;
            p = t;
        }
    }
    return 1;
}
