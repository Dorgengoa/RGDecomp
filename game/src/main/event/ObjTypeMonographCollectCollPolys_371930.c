/* rgp:protos */
#define RGP_SELF_ObjTypeMonographCollectCollPolys_371930 1
#define RGP_SELF_alive 1
#define RGP_SELF_dead 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/




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
    f32 sp80[4] __attribute__((aligned(16)));
    f32 sp70[4] __attribute__((aligned(16)));
    f32 sp60[4] __attribute__((aligned(16)));
    s32 h;
    s32 n;
    s32 i;
    s32 b;

    b = !((*(s32 *)(arg0 + 0xD0) & 0x40000000) != 0);
    if (b == 0) {
        return 0;
    }
    if (((short)TargetRefGetKind_2e7130(arg0 + 0xA0)) == 5 && arg4 == ((short)TargetRefGetId_2e7120(arg0 + 0xA0))) {
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
