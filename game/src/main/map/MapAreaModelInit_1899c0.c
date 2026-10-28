/* rgp:protos */
#define RGP_SELF_MapAreaModelInit_1899c0 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
#include "vec.h"
#pragma vu0_mmi_reg_binding on
typedef rg_s128 __attribute__((aligned(4))) rgvb_vz1899c0_t; /* rg:vu0bind vf0 */
#define vz1899c0 RG_VU0_BIND_VF(0, rgvb_vz1899c0_t)


/*rgp*/
/*rgp*/
extern void *memset(void *, s32, s32);

void MapAreaModelInit_1899c0(void *arg0)
{ RG_VU0_FRAME;
    s32 temp_2;
    s32 var_16;
    s32 var_4;
    s32 var_4_2;
    s32 var_4_3;
    s32 var_4_4;
    s32 var_4_5;
    void *temp_3;
    void *temp_3_4;
    void *temp_3_5;

    NodeInit_185f60((void *)arg0);
    var_4 = 0;
    do {
        *(s32 *)((u8 *)arg0 + (var_4 * 4) + 0x284) = 0;
        temp_3 = (u8 *)arg0 + (var_4 * 0xC);
        var_4 += 1;
        *(s32 *)((u8 *)temp_3 + 0x4B0) = 0;
        *(s32 *)((u8 *)temp_3 + 0x4B4) = 0;
        *(s32 *)((u8 *)temp_3 + 0x4B8) = 0;
    } while (var_4 < 7);
    var_4_2 = 0;
    do {
        temp_3 = (u8 *)arg0 + (var_4_2 * 8);
        var_4_2 += 1;
        *(s32 *)((u8 *)temp_3 + 0x504) = 0;
        *(s32 *)((u8 *)temp_3 + 0x508) = 0;
    } while (var_4_2 < 0xA);
    var_4_3 = 0;
    do {
        temp_3 = (u8 *)arg0 + (var_4_3 * 4);
        var_4_3 += 1;
        *(s32 *)((u8 *)temp_3 + 0x580) = 0;
        *(s32 *)((u8 *)temp_3 + 0x58C) = 0;
    } while (var_4_3 < 3);
    *(s32 *)((u8 *)arg0 + 0x2A0) = 0;
    *(s32 *)((u8 *)arg0 + 0x2A4) = 0;
    var_4_4 = 0;
    *(s32 *)((u8 *)arg0 + 0x280) = 0;
    *(s32 *)((u8 *)arg0 + 0x1630) = 0;
    *(s32 *)((u8 *)arg0 + 0x1634) = 0;
    *(s32 *)((u8 *)arg0 + 0x598) = 0x18;
    do {
        temp_2 = var_4_4 * 0x30;
        var_4_4 += 1;
        temp_3_4 = (u8 *)arg0 + temp_2;
        *(s32 *)((u8 *)temp_3_4 + 0x5C4) = 0;
        *(s32 *)((u8 *)temp_3_4 + 0x5C0) = 0;
        *(s32 *)((u8 *)temp_3_4 + 0x5C8) = 0;
    } while (var_4_4 < 0x18);
    var_4_5 = 0;
    *(s32 *)((u8 *)arg0 + 0x2A8) = 0x20;
    do {
        temp_3_5 = (u8 *)arg0 + (var_4_5 * 0x10);
        var_4_5 += 1;
        *(s32 *)((u8 *)temp_3_5 + 0x2AC) = 0;
        *(s32 *)((u8 *)temp_3_5 + 0x2B4) = 0;
        *(s32 *)((u8 *)temp_3_5 + 0x2B0) = 0;
        *(s32 *)((u8 *)temp_3_5 + 0x2B8) = 0;
    } while (var_4_5 < 0x20);
    *(s32 *)((u8 *)arg0 + 0x1660) = 0;
    FuncDataTableInit_18fc00((u8 *)arg0 + 0x1664);
    *(s32 *)((u8 *)arg0 + 0x1640) = 0;
    *(s32 *)((u8 *)arg0 + 0x1644) = 0;
    var_16 = 0;
    *(s32 *)((u8 *)arg0 + 0x164C) = 0;
    *(s32 *)((u8 *)arg0 + 0x1650) = 0;
    *(s32 *)((u8 *)arg0 + 0x1648) = -1;
    *(s32 *)((u8 *)arg0 + 0x1654) = 0;
    *(s32 *)((u8 *)arg0 + 0x4AC) = 0;
    *(s32 *)((u8 *)arg0 + 0x163C) = 0;
    *(s32 *)((u8 *)arg0 + 0x167C) = 0;
    *(s32 *)((u8 *)arg0 + 0x1674) = 0;
    *(s32 *)((u8 *)arg0 + 0x1678) = 0;
    *(s32 *)((u8 *)arg0 + 0xA20) = 0;
    do {
        memset((u8 *)arg0 + (var_16 * 0xC0) + 0xA30, 0, 0xC0);
        var_16 += 1;
    } while (var_16 < 0x10);
    *(s32 *)((u8 *)arg0 + 0x554) = 0;
    if (arg0) { arg0 = (void *)(s32)(u32)arg0; }
    *(rg_s128 *)((u8 *)arg0 + 0x560) = vz1899c0;
    *(rg_s128 *)((u8 *)arg0 + 0x570) = vz1899c0;
    if (arg0) { arg0 = (void *)(s32)(u32)arg0; }
    *(u32 *)((u8 *)arg0 + 0x165C) = 0x3F800000;
    *(s8 *)((u8 *)arg0 + 0x1638) = 0;
}
