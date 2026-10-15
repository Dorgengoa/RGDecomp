#include "types.h"

typedef struct S {
    s32 unk0;
    u8 unk4[0x18];
    s32 unk1C;
    u8 pad20[4];
    u8 b0 : 1;
    u8 b1 : 7;
    u8 unk25;
    u8 pad26[0xE];
    s32 unk34;
} S;

extern void UiEntryListAlloc_28e0c0(void *arg0, s32 arg1, s32 arg2);
extern void UiEntryListLoad_28eb70(void *arg0, s32 arg1, s32 arg2);
extern void UiEntryListReset_28ec80(void *arg0);

s32 UiPageEntryListReload_289b70(S *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v;

    v = arg3;
    if (arg3 <= 0) {
        v = 0x80;
    }
    UiEntryListReset_28ec80(arg0->unk4);
    UiEntryListAlloc_28e0c0(arg0->unk4, arg0->unk34, v);
    UiEntryListLoad_28eb70(arg0->unk4, arg1, arg0->unk0);
    arg0->unk1C = arg2;
    arg0->b0 = 0;
    arg0->unk25 = 0;
    return 1;
}
