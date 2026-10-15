#include "types.h"
#include "vec.h"

extern void *ArrayGetChecked_152e40(s32, s32);

s32 ModelGetFrameMeshBounds_151f60(s32 arg0, void *arg1, s32 arg2, void *arg3)
{
    void *self;
    void *node;
    u8 *sub;
    s32 idx;
    void *rec;

    self = arg3;
    if (self == NULL) {
        self = (void *)(arg0 + 0x120);
    }
    if (self == NULL) {
        rec = NULL;
    } else {
        for (node = *(void **)((u8 *)self + 0x44); node != NULL; node = *(void **)node) {
            sub = (u8 *)node + 0x10;
            if (*(s32 *)((u8 *)node + 0x14) == arg2) {
                idx = *(s32 *)(sub + 0x8);
                goto found;
            }
        }
        idx = -1;
    found:
        rec = (*(s32 *)((u8 *)self + 0x0) != 0) ? ArrayGetChecked_152e40(*(s32 *)((u8 *)self + 0xC), idx) : NULL;
    }
    if (rec == NULL) {
        return 0;
    }
    *(u128 *)((u8 *)arg1 + 0x0) = *(u128 *)((u8 *)rec + 0x20);
    *(u128 *)((u8 *)arg1 + 0x10) = *(u128 *)((u8 *)rec + 0x30);
    return 1;
}
