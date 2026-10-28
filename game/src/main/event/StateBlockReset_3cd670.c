/* rgp:protos */
#define RGP_SELF_StateBlockReset_3cd670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *arg0, s32 arg1, s32 arg2);

void StateBlockReset_3cd670(void *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 temp_4;
    s32 var_4;
    s32 var_4_2;
    s32 var_4_3;
    s32 var_6;
    void *temp_2;

    temp_4 = *(s32 *)((u8 *)arg0 + 0x4);
    if (temp_4 != 0) {
        StateTablesRelease_421240(temp_4, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    }
    *(s16 *)((u8 *)arg0 + 0x8) = 1;
    *(s16 *)((u8 *)arg0 + 0xA) = 0xA;
    *(s16 *)((u8 *)arg0 + 0xC) = 0xA;
    *(s16 *)((u8 *)arg0 + 0xE) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x10) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x12) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x14) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x16) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x18) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x1A) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x1C) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x1E) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x20) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x22) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x24) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x26) = 0xA;
    Bitset2048Ctor_3cdf50((u8 *)arg0 + 0x28);
    memset((u8 *)arg0 + 0x128, 0, 0x100);
    Bitset2048Ctor_3cdf50((u8 *)arg0 + 0x228);
    Bitset256Ctor_3cdf80((u8 *)arg0 + 0x328);
    *(s16 *)((u8 *)arg0 + 0x348) = 0;
    var_4 = 0;
    do {
        temp_2 = (u8 *)arg0 + (var_4 * 4);
        var_4 += 1;
        *(s32 *)((u8 *)temp_2 + 0x34C) = -1;
    } while (var_4 < 4);
    Bitset1280Ctor_3cdfb0((u8 *)arg0 + 0x360);
    var_4_2 = 0;
    do {
        *(s8*)((u8 *)arg0 + var_4_2 + 0x400) = -1;
        var_4_2 += 1;
    } while (var_4_2 < 0x40);
    var_4_3 = 0;
    do {
        *(s8*)((u8 *)arg0 + var_4_3 + 0x440) = -1;
        var_4_3 += 1;
    } while (var_4_3 < 0x400);
    var_6 = 0;
    do {
        *(s8*)((u8 *)arg0 + var_6 + 0x840) = -1;
        *(f64*)((u8 *)arg0 + (var_6 * 8) + 0x880) = -1.0;
        var_6 += 1;
    } while (var_6 < 0x40);
    memset((u8 *)arg0 + 0xA80, 0, 0x20);
    memset((u8 *)arg0 + 0xAA0, 0, 0xC00);
    *(s16 *)((u8 *)arg0 + 0x16A0) = 0;
    memset((u8 *)arg0 + 0x16A2, 0, 0xC80);
}
