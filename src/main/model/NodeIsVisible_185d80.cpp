#include "types.h"

extern "C" s32 NodeIsVisible_185d80(void *a)
{
    s32 r;

    if (*(s16 *)((u8 *)a + 0x32) == 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)a + 0x50) != 0) {
        if (*(f32 *)((u8 *)a + 0x54) != 0.0f) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        r = *(s32 *)((u8 *)a + 0x3C) == 0;
        if (!r) {
            r = 0;
        } else {
            r = 1;
        }
    }
    return r;
}
