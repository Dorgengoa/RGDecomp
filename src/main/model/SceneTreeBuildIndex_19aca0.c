#include "types.h"
#pragma opt_common_subs off

extern s32 MemStackNew_14e1b0(s32, s32);
extern void *TreeIterNext_19ad60(void *);

s32 SceneTreeBuildIndex_19aca0(void *arg0, s32 arg1)
{
    s32 i;

    i = 0;
    *(s32 *)((u8 *)arg0 + 0x98) = *(s32 *)((u8 *)arg0 + 0x94);
    while (TreeIterNext_19ad60(arg0) != NULL) {
        i += 1;
    }
    *(s32 *)((u8 *)arg0 + 0x98) = 0;
    *(s32 *)((u8 *)arg0 + 0x9C) = i;
    *(s32 *)((u8 *)arg0 + 0xA0) = MemStackNew_14e1b0(i * 4, arg1);
    if (*(s32 *)((u8 *)arg0 + 0xA0) == 0) {
        return 0;
    }
    i = 0;
    *(s32 *)((u8 *)arg0 + 0x98) = *(s32 *)((u8 *)arg0 + 0x94);
    {
    void *p2;
    while ((p2 = TreeIterNext_19ad60(arg0)) != NULL) {
        *(s32 *)((u8 *)p2 + 0x14) = i;
        *(void **)(*(u8 **)((u8 *)arg0 + 0xA0) + i * 4) = p2;
        i += 1;
    }
    }
    *(s32 *)((u8 *)arg0 + 0x98) = 0;
    return *(s32 *)((u8 *)arg0 + 0x9C);
}
