#include "types.h"

typedef struct S001d6e40 {
    u8 pad0[0x80];
    s16 unk80;
    u8 pad82[0x98 - 0x82];
    s32 unk98;
    s32 unk9C;
    s16 unkA0;
    s16 unkA2;
    s32 unkA4;
} S001d6e40;

extern s32 MemStackAllocQw_14d950(s32 arg0, s64 arg1);
extern s16 SoundStreamSlotAlloc_1bd560(s32 arg0, s32 arg1, s32 arg2);
extern void StreamChanSetFillThreshold_1d6b10(S001d6e40 *arg0, f32 arg1);
extern void StreamChanReset_1d75d0(void);

s32 StreamChanOpen_1d6e40(S001d6e40 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u32 t;
    s32 n;
    s32 size;
    s32 r;
    s16 h;

    StreamChanReset_1d75d0();
    if (arg4 == 0) {
        return 0;
    }
    if (arg1 <= 0 || arg2 <= 0 || arg3 < 0) {
        return 0;
    }

    t = arg1 * (arg2 + 2) * 0x7000 + 0x800;
    if (!(t & 0xF)) {
        n = t >> 4;
    } else {
        n = (t >> 4) + 1;
    }

    size = n << 4;
    r = MemStackAllocQw_14d950(arg4, (s64)(size >> 4));
    arg0->unk98 = r;
    if (r == 0) {
        return 0;
    }
    h = SoundStreamSlotAlloc_1bd560(arg1, r, size);
    arg0->unk80 = h;
    if (h < 0) {
        return 0;
    }
    arg0->unkA0 = arg1;
    arg0->unkA2 = arg2;
    arg0->unkA4 = arg3;
    arg0->unk9C = size;
    StreamChanSetFillThreshold_1d6b10(arg0, 0.5f);
    return 1;
}
