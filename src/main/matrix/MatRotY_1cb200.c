#include "types.h"

extern void VecSinCos_1cbfb0(f32 *angle, f32 *out);

void MatRotY_1cb200(u8 *a0, f32 angle)
{
    f32 buf[4];
    u8 *p = (u8 *)buf;
    s32 count = 0x10;

    if (p != 0) {
        do {
            *p = 0;
            p++;
        } while (--count != 0);
    }

    buf[0] = angle;
    VecSinCos_1cbfb0(buf, buf);

    *(f32 *)(a0 + 0x00) = buf[1];
    *(s32 *)(a0 + 0x04) = 0;
    *(f32 *)(a0 + 0x08) = -buf[0];
    *(s32 *)(a0 + 0x0C) = 0;
    *(s32 *)(a0 + 0x10) = 0;
    *(f32 *)(a0 + 0x14) = 1.0f;
    *(s32 *)(a0 + 0x18) = 0;
    *(s32 *)(a0 + 0x1C) = 0;
    *(f32 *)(a0 + 0x20) = buf[0];
    *(s32 *)(a0 + 0x24) = 0;
    *(f32 *)(a0 + 0x28) = buf[1];
    *(s32 *)(a0 + 0x2C) = 0;
    *(s32 *)(a0 + 0x30) = 0;
    *(s32 *)(a0 + 0x34) = 0;
    *(s32 *)(a0 + 0x38) = 0;
    *(f32 *)(a0 + 0x3C) = 1.0f;
}
