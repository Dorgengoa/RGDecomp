#include "types.h"

extern s32 MotionPlayerAddEntryUnique_172850(s32, s32, s32, s32);

void MotionPlayerCopyEntries_1737b0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 node;
    s32 result;
    f32 *p10;
    s32 src;
    s32 dst;
    s32 count;

    if (arg2 == 0) {
        *(s32 *)(arg1 + 0x48) = *(s32 *)(arg0 + 0x48);
        return;
    }
    node = *(s32 *)(arg0 + 0x48);
    while (node != 0) {
        result = MotionPlayerAddEntryUnique_172850(arg1, *(s32 *)(node + 0xC), arg2, *(s32 *)(node + 8));
        if (result != 0) {
            p10 = (f32 *)(node + 0x10);
            dst = result + 0xC;
            count = 5;
            *(f32 *)(result + 0) = *p10;
            *(s32 *)(result + 4) = *(s32 *)(node + 0x14);
            *(s32 *)(result + 8) = *(s32 *)(node + 0x18);
            src = (s32)p10 + 0xC;
            do {
                count -= 1;
                *(s32 *)dst = *(s32 *)src;
                src += 4;
                dst += 4;
            } while (count > 0);
        }
        node = *(s32 *)(node + 0);
    }
}
