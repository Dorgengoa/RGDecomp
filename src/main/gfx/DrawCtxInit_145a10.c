#include "types.h"

extern void memset(void *, s32, s32);
extern void CameraRecInit_156940(void *);
extern void PlaneShadowDescInit_156a70(void *);

struct Slot {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

void DrawCtxInit_145a10(u8 *p0)
{
    s32 i;
    s32 j;
    struct Slot *s;

    *(s32 *)(p0 + 0x3D20) = 0;
    *(s32 *)(p0 + 0x3D1C) = 0;
    *(s32 *)(p0 + 0x3D18) = 0;
    *(s32 *)(p0 + 0x3D14) = 0;
    *(s32 *)(p0 + 0x3D10) = 0;
    *(s32 *)(p0 + 0x0) = 0;
    *(s32 *)(p0 + 0x3BA0) = 0;
    *(s32 *)(p0 + 0xF18) = 0;
    *(s32 *)(p0 + 0xF1C) = 0;
    *(s32 *)(p0 + 0x3BA4) = 0;
    memset(p0 + 0x280, 0, 0xC80);
    *(u8 **)(p0 + 0x270) = p0 + 0x280;
    *(u8 **)(p0 + 0xF20) = p0 + 0xF30;
    CameraRecInit_156940(p0 + 0xF30);
    *(s32 *)(p0 + 0xF00) = 0;
    *(s32 *)(p0 + 0xF04) = 0;
    *(f32 *)(p0 + 0xF10) = 1.0f;
    *(s32 *)(p0 + 0xF14) = 0;
    *(s32 *)(p0 + 0x3C40) = 0;
    *(s32 *)(p0 + 0x3C44) = 0;
    for (i = 0; i < 0x20; i++) {
        *(s32 *)(p0 + 0x3C48 + i * 4) = 0;
    }
    *(u8 **)(p0 + 0x36B4) = p0 + 0x36D0;
    *(u8 **)(p0 + 0x36B8) = p0 + 0x3870;
    *(s32 *)(p0 + 0x36BC) = 0;
    *(s32 *)(p0 + 0x36C0) = 0;
    *(s32 *)(p0 + 0x36B0) = 0;
    *(s32 *)(p0 + 0x3890) = 0;
    PlaneShadowDescInit_156a70(p0 + 0x38A0);
    *(s32 *)(p0 + 0x3CC8) = 0;
    *(s32 *)(p0 + 0x3CCC) = 0;
    *(s32 *)(p0 + 0x3D2C) = 0;
    *(s32 *)(p0 + 0xF08) = 0;
    *(s32 *)(p0 + 0xF0C) = 0;
    for (j = 0; j < 4; j++) {
        s = (struct Slot *)(p0 + 0x3CD0 + j * 16);
        s->m00 = 1;
        s->m0C = -1;
    }
}
