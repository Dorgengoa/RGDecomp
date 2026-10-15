#include "types.h"
#pragma opt_propagation off


extern void FrameSetScale_14a2c0(s32, f32 *);
extern void FrameSetRot_14a390(s32, f32 *);
extern void FrameSetPos_14a450(s32, f32 *);
extern s32 CollFrameTreeCollectTrisFwd_16c180(s32, u8 *, s32, s32);
extern s32 GetMonographyCollObj_1fdad0(void);
extern s32 TargetRefGetId_2e7120(u8 *);
extern s32 TargetRefGetKind_2e7130(u8 *);
extern void EventObjGetPos_2e7640(u8 *, f32 *);
extern void EventObjGetRot_2e7670(u8 *, f32 *);
extern void EventObjGetScale_2e7690(u8 *, f32 *);




 static inline s32 dead(u8 *p)
{
    return (*(s32 *)(p + 0xD0) & 0x40000000) != 0;
}

static inline s32 alive(u8 *p)
{
    return !dead(p);
}

s32 ObjTypeMonographCollectCollPolys_371930(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    f32 sp80[4];
    f32 sp70[4];
    f32 sp60[4];
    s32 h;
    s32 n;
    s32 i;
    s32 b;

    b = !((*(s32 *)(arg0 + 0xD0) & 0x40000000) != 0);
    if (b == 0) {
        return 0;
    }
    if (TargetRefGetKind_2e7130(arg0 + 0xA0) == 5 && arg4 == TargetRefGetId_2e7120(arg0 + 0xA0)) {
        return 0;
    }
    h = GetMonographyCollObj_1fdad0();
    if (h == 0) {
        return 0;
    }
    EventObjGetPos_2e7640(arg0 + 0x10, sp80);
    EventObjGetRot_2e7670(arg0 + 0x10, sp70);
    EventObjGetScale_2e7690(arg0 + 0x10, sp60);
    FrameSetPos_14a450(h, sp80);
    FrameSetRot_14a390(h, sp70);
    FrameSetScale_14a2c0(h, sp60);
    n = CollFrameTreeCollectTrisFwd_16c180(h, arg1, arg3, arg2);
    for (i = 0; i < n; i++) {
        *(s16 *)(arg1 + 0x46) |= 0x1000;
        arg1 += 0x60;
    }
    return n;
}
