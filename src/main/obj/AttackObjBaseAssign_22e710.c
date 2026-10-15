#include "types.h"
#pragma opt_propagation off

typedef struct { s16 a; s16 b; } P16_0022e710;
typedef struct { s8 a; s8 b; } P8_0022e710;
typedef struct { f32 x; f32 y; f32 z; f32 w; } V4_0022e710;

extern void JudgeObjectAssignBase_2289d0(void);

void *AttackObjBaseAssign_22e710(void *arg0, void *arg1)
{
    u8 *b;
    u8 *a;
    u8 *var_6_2;
    u8 *var_6;
    u8 *var_5_2;
    u8 *var_5;
    s8 temp_2_2;
    s32 var_4_2;
    s32 var_4;
    s16 temp_2;

    a = (u8 *) arg0;
    b = (u8 *) arg1;
    JudgeObjectAssignBase_2289d0();
    var_6 = b + 0xD0;
    var_5 = a + 0xD0;
    var_4 = 0x14;
    *(s16 *) (a + 0xB4) = *(s16 *) (b + 0xB4);
    *(s16 *) (a + 0xB6) = *(s16 *) (b + 0xB6);
    *(s16 *) (a + 0xB8) = *(s16 *) (b + 0xB8);
    *(s16 *) (a + 0xBA) = *(s16 *) (b + 0xBA);
    *(s16 *) (a + 0xBC) = *(s16 *) (b + 0xBC);
    *(u16 *) (a + 0xBE) = *(u16 *) (b + 0xBE);
    *(s16 *) (a + 0xC0) = *(s16 *) (b + 0xC0);
    *(f32 *) (a + 0xC4) = *(f32 *) (b + 0xC4);
    *(f32 *) (a + 0xC8) = *(f32 *) (b + 0xC8);
    *(f32 *) (a + 0xCC) = *(f32 *) (b + 0xCC);
    do {
        var_4 -= 1;
        *(P16_0022e710 *) var_5 = *(P16_0022e710 *) var_6;
        var_6 += 4;
        var_5 += 4;
    } while (var_4 > 0);
    var_6_2 = b + 0x120;
    var_5_2 = a + 0x120;
    var_4_2 = 0x14;
    do {
        var_4_2 -= 1;
        {
        s8 x = ((P8_0022e710 *) var_6_2)->a;
        s8 y = ((P8_0022e710 *) var_6_2)->b;
        ((P8_0022e710 *) var_5_2)->a = x;
        ((P8_0022e710 *) var_5_2)->b = y;
        }
        var_6_2 += 2;
        var_5_2 += 2;
    } while (var_4_2 > 0);
    *(V4_0022e710 *) (a + 0x150) = *(V4_0022e710 *) (b + 0x150);
    *(V4_0022e710 *) (a + 0x160) = *(V4_0022e710 *) (b + 0x160);
    *(V4_0022e710 *) (a + 0x170) = *(V4_0022e710 *) (b + 0x170);
    *(V4_0022e710 *) (a + 0x180) = *(V4_0022e710 *) (b + 0x180);
    *(f32 *) (a + 0x190) = *(f32 *) (b + 0x190);
    return arg0;
}
