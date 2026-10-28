/* rgp:protos */
#define RGP_SELF_NodeRefObjCtor_318ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00471D00[];
/*rgp*/
/*rgp*/

u8 *NodeRefObjCtor_318ff0(u8 *p, short rgp_a1, short rgp_a2, int rgp_a3, float rgp_f0)
{
    s32 i;
    u8 *e;

    JudgeObjectCtor_3145a0(p, (short)rgp_a1, (short)rgp_a2, (int)rgp_a3, (float)rgp_f0);
    *(u8 **)(p + 0xB0) = D_00471D00;
    *(s16 *)(p + 0x682) = -1;
    *(s16 *)(p + 0x680) = 0;
    *(s16 *)(p + 0x884) = 0;
    *(s16 *)(p + 0x886) = 0;
    for (i = 0; i < 0x10; i++) {
        NodeRefReset_3193d0(p + i * 80 + 0x180);
    }
    for (i = 0; i < 0x10; i++) {
        e = p + i * 12;
        *(s32 *)(e + 0x684) = 0;
        *(s32 *)(e + 0x688) = 0;
        *(s16 *)(e + 0x68C) = -1;
        *(s16 *)(e + 0x68E) = 0;
    }
    for (i = 0; i < 0x10; i++) {
        e = p + i * 20;
        *(s32 *)(e + 0x744) = 0;
        *(s32 *)(e + 0x748) = 0;
        *(s16 *)(e + 0x74C) = -1;
        *(s16 *)(e + 0x74E) = -1;
        *(s32 *)(e + 0x750) = 0;
        *(f32 *)(e + 0x754) = 1.0f;
    }
    return p;
}
